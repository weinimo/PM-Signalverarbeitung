/*****************************************************************************
 *  Rohde&Schwarz RTO Digital Oscilloscope instrument driver
 *  Callbacks
 *
 *  Original Release: December 2010
 *  By: Jiri Kominek
 *
 *  Should you have any technical questions please contact the hotline of
 *  Rohde & Schwarz Vertriebs-GmbH Rohde & Schwarz Support Center
 *
 *  e-mail: CustomerSupport@rohde-schwarz.com
 *

 *****************************************************************************/

#include "rsscope.h"
#include "rsscope_utility.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

#pragma warning (disable:4100) // unreferenced formal parameter


ViStatus rsscope_doubleQuotedString_ReadCallback (ViSession io, ViConstString repCapName, ViAttr attributeId, ViInt32 bufSize, void *value);
ViStatus rsscope_doubleQuotedString_WriteCallback (ViSession io, ViConstString repCapName, ViAttr attributeId, void *value);

/*****************************************************************************
 * Function: Rs_CheckStatusCallback
 * Purpose:  This function queries the instrument to determine if it has
 *           encountered an error. If the instrument has encountered an
 *           error, this function returns the RS_ERROR_INSTRUMENT_SPECIFIC
 *           error code. This function is called by the
 *           Rs_CheckStatus utility function. The
 *           Rs_SetAttribute and Rs_GetAttribute functions invoke this
 *           function when the optionFlags parameter includes the
 *           RS_VAL_DIRECT_USER_CALL flag.
 *
 *           The user can disable calls to this function by setting the
 *           RSSPECAN_QUERY_INSTRUMENT_STATUS attribute to VI_FALSE.  The driver can
 *           disable the check status callback for a particular attribute by
 *           setting the RS_VAL_DONT_CHECK_STATUS flag.
 *
 *****************************************************************************/
ViStatus rsscope_CheckStatusCallback (ViSession instrSession)
{
    ViStatus    error   = VI_SUCCESS;
    ViInt16     esr     = 0;

    viCheckErr (viQueryf (instrSession, "*STB?\n", "%hd", &esr));

    if ((esr & IEEE_488_2_ERROR_MASK) != 0)
    {
        viCheckErr (RS_ERROR_INSTR_SPECIFIC);
    }

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_WaitForOPCCallback
 * Purpose:  This function waits until the instrument has finished processing
 *           all pending operations. This function is called by the
 *           Rs_WaitForOPC utility function. The RS engine invokes
 *           this function in the following two cases:
 *           - Before invoking the read callback for attributes for which the
 *             RS_VAL_WAIT_FOR_OPC_BEFORE_READS flag is set.
 *           - After invoking the write callback for attributes for which the
 *             RS_VAL_WAIT_FOR_OPC_AFTER_WRITES flag is set.
 *
 *****************************************************************************/
ViStatus rsscope_WaitForOPCCallback (ViSession instrSession)
{
    ViStatus    error = VI_SUCCESS;
    ViUInt16    response    = 0;
    ViInt32     counter     = 0;
    ViUInt16    intfc   = VI_INTF_GPIB;
    ViInt32     opcTimeout = 0;
    
    checkErr( Rs_GetAttribute (instrSession, VI_NULL, RS_ATTR_OPC_TIMEOUT, 0,
        (ViInt32) sizeof (opcTimeout), &opcTimeout));

    viCheckErr( viGetAttribute (instrSession, VI_ATTR_INTF_TYPE, &intfc));

    /* intfc specific operations */
    switch (intfc)
        {
        case VI_INTF_ASRL: /* Serial intfc */

            /* Not supported */

        break;
        default: /* Default case */

            /* Check STB for errors. */
            do
            {
                error = viReadSTB (instrSession, &response);

                Rs_Delay (0.001);
                counter++;

                if (counter >= opcTimeout)
                    return RSSCOPE_ERROR_MAX_TIME_EXCEEDED;

                /* Wait while STB is non zero value. Only Error/Event Queue
                   and ESB bits are taken into consideration. */
            
            } while ((response & 0x24) == 0);
            /* (check Error(Event) Queue bit in STB) */
            return ((response & 0x4) != 0) ? RS_ERROR_INSTRUMENT_STATUS : error;
        }

Error:

    return error;
}

 /*****************************************************************************
 *- Write Callbacks ---------------------------------------------------------*
 *****************************************************************************/

 

/*****************************************************************************
 * Function: rsscope_quotedInt_WriteCallback
 * Purpose:  This function overrides standard calback funtion. Writes int 
 *           with apostrophes
 *****************************************************************************/
ViStatus rsscope_quotedInt_WriteCallback(ViSession instrSession, ViConstString repCapName, ViAttr attributeId, void *value)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error               = VI_SUCCESS;
    ViInt32     idx                 = 0;
    ViChar      *cmd                = VI_NULL;

    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* If no command available, exit the function */
    if (sessionProperties -> attr[idx].command == VI_NULL)
        return VI_SUCCESS;

    /* Check if attribute uses repeated capabilities */
    if (sessionProperties -> attr[idx].usercaps == VI_TRUE)
        {
        if (!repCapName)
            viCheckErr (RS_ERROR_INVALID_REPEATED_CAPABILITY_NAME);

        if (strlen (repCapName) == 0)
            viCheckErr (RS_ERROR_INVALID_REPEATED_CAPABILITY_NAME);
        }

    /* Build the command string */
    viCheckErr (Rs_BuildCommandString (instrSession, attributeId, idx, repCapName, &cmd));  

    /* --- If the range table for the attribute exists, pass 'command string' or
       'discreteOrMinValue' instead of attribute value. --- */
    /* Range Table Callback */
    if (sessionProperties -> attr[idx].rangeTableCallback)
    {                                                          
        viCheckErr ((sessionProperties -> attr[idx].rangeTableCallback)(instrSession, repCapName, attributeId, &(sessionProperties -> attr[idx].rangeTable)));
    }
    
    if (sessionProperties -> attr[idx].rangeTable)
        if (sessionProperties -> attr[idx].rangeTable -> type == RS_VAL_DISCRETE)
            {
            ViUInt16    i = 0;
            ViChar      *p2string;
            ViReal64    *p2discrete;
            ViInt32     data_type = sessionProperties -> attr[idx].dataType;
            ViReal64    precision = sessionProperties -> attr[idx].comparePrecision;

            precision = (precision < DBL_MIN) ? DBL_MIN : precision;

            /* Allowed data types are only ViInt32 or ViReal64 */
            switch (data_type)
                {
                case RS_VAL_INT32:
                case RS_VAL_REAL64:
                    /* Valid data types */
                    break;
                case RS_VAL_STRING:
                case RS_VAL_BOOLEAN:
                case RS_VAL_EVENT:
                case RS_VAL_ADDR:
                case RS_VAL_SESSION:
                case RS_VAL_UNKNOWN_TYPE:
                default:
                    viCheckErr (RS_ERROR_INVALID_TYPE);
                }

            /* Go over range table values and find appropriate command string for passed
               attribute value. For floating point values use predefined attribute precision. */
            do
                {
                p2discrete = &sessionProperties -> attr[idx].rangeTable -> rangeValues[i].discreteOrMinValue;
                p2string = sessionProperties -> attr[idx].rangeTable -> rangeValues[i].cmdString;

                if (sessionProperties -> attr[idx].rangeTable -> rangeValues[i].cmdString == RS_RANGE_TABLE_END_STRING)
                    return RS_ERROR_INVALID_VALUE;

                if (data_type == RS_VAL_INT32)
                    if (fabs(*p2discrete - *(ViInt32 *)value) <= DBL_MIN)
                        {
                        viCheckErr (viPrintf(instrSession, "%s \'%s\'\n", cmd, p2string));
                        break;
                        }

                if (data_type == RS_VAL_REAL64)
                    if (fabs(*p2discrete - *(ViReal64 *)value) <= precision)
                        {
                        viCheckErr (viPrintf(instrSession, "%s \'%s\'\n", cmd, p2string));
                        break;
                        }

                i++;

                } while (i);

            goto Error; /* Exit the function */
            }

    /* --- Attribute data type is used for VISA I/O --- */
    switch (sessionProperties -> attr[idx].dataType)
        {
        case RS_VAL_INT32:
            viCheckErr (viPrintf(instrSession, "%s %ld\n", cmd, *(ViInt32 *)value));
            break;
        case RS_VAL_REAL64:
            viCheckErr (viPrintf(instrSession, "%s %.12f\n", cmd, *(ViReal64 *)value));
            break;
        case RS_VAL_STRING:
            viCheckErr (viPrintf(instrSession, "%s \'%s\'\n", cmd, value));
            break;
        case RS_VAL_BOOLEAN:
            viCheckErr (viPrintf(instrSession, "%s %s\n", cmd, (*(ViBoolean *)value == VI_FALSE) ? "OFF" : "ON"));
            break;
        case RS_VAL_EVENT:
            viCheckErr (viPrintf(instrSession, "%s\n", cmd));
            break;
        case RS_VAL_ADDR:
        case RS_VAL_SESSION:
        case RS_VAL_UNKNOWN_TYPE:
        default:
            viCheckErr (RS_ERROR_INVALID_TYPE);
        }

Error:

    if (cmd)
        free (cmd);

    return error;
}
