/*****************************************************************************
 *------------------------ Utility  -----------------------------------------*
 *****************************************************************************/
#include <float.h>
#include <math.h>
#include "rsscope.h"

/*****************************************************************************
 *- Callback Declarations ---------------------------------------------------*
 *****************************************************************************/

ViStatus rsscope_CheckStatusCallback (ViSession io);

/*****************************************************************************
 *- Common Callback Declarations --------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: rsscope_InitAttributes
 * Purpose:  This function inits attributes to the desired values if needed.
 *****************************************************************************/
ViStatus rsscope_InitAttributes (ViSession instrSession)
{
    ViStatus    error           = VI_SUCCESS;
    ViInt32     p2value         = 0;
    void        *p2void;
    ViChar      buffer[RS_MAX_MESSAGE_BUF_SIZE],
                revision[RS_MAX_MESSAGE_BUF_SIZE],
                manufacturer[RS_MAX_MESSAGE_BUF_SIZE],
                model[RS_MAX_MESSAGE_BUF_SIZE],
                tmp_model[RS_MAX_MESSAGE_BUF_SIZE],
                idQ[RS_MAX_MESSAGE_BUF_SIZE],
                options_list[RS_MAX_MESSAGE_BUF_SIZE];

    buffer[RS_MAX_MESSAGE_BUF_SIZE -1] = 0;

    /*- Misc -*/

    if (!Rs_Simulating(instrSession))
        {
        /* Instrument identification */
        viCheckErr (viQueryf (instrSession, "*IDN?\n", "%[^\r\n]", idQ));
        idQ[RS_MAX_MESSAGE_BUF_SIZE - 1] = 0;
        checkErr (Rs_SetAttribute (instrSession, "", RSSCOPE_ATTR_ID_QUERY_RESPONSE, 0, idQ));
        
        /* Option(s) string */
        viCheckErr (viQueryf (instrSession, "*OPT?\n", "%[^\r\n]", options_list));
        options_list[RS_MAX_MESSAGE_BUF_SIZE - 1] = 0;
        }
    else /* Simulating */
        {
        /* Instrument identification */
        strncpy (idQ, RSSCOPE_SIMULATION_ID_QUERY, RS_MAX_MESSAGE_BUF_SIZE - 1);
        checkErr (Rs_SetAttribute (instrSession, "", RSSCOPE_ATTR_ID_QUERY_RESPONSE, 0, idQ));
        
        /* Option(s) string */
        strncpy (options_list, RSSCOPE_SIMULATION_OPT_QUERY, RS_MAX_MESSAGE_BUF_SIZE - 1);
        }

    /*- Inherent Instrument Specific Attributes ----------------------------*/

    /*- User Options -*/

    /*
    RS_ATTR_RANGE_CHECK             ... Rs_SpecificDriverNew
    RS_ATTR_QUERY_INSTRUMENT_STATUS ... Rs_SpecificDriverNew
    RS_ATTR_CACHE                   ... Rs_SpecificDriverNew
    RS_ATTR_SIMULATE                ... Rs_SpecificDriverNew
    RS_ATTR_RECORD_COERCIONS        ... not supported
    RS_ATTR_INTERCHANGE_CHECK       ... not supported
    RS_ATTR_SPY                     ... not supported
    RS_ATTR_USE_SPECIFIC_SIMULATION ... not supported
    */

    /*- Class Driver Identification -*/

    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_DESCRIPTION, 0, RSSCOPE_CLASS_DRIVER_DESCRIPTION));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_PREFIX, 0, RSSCOPE_CLASS_DRIVER_PREFIX));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_VENDOR, 0, RSSCOPE_CLASS_DRIVER_VENDOR));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_REVISION, 0, RSSCOPE_CLASS_DRIVER_REVISION));
    p2value = RSSCOPE_CLASS_SPEC_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION, 0, &p2value));
    p2value = RSSCOPE_CLASS_SPEC_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION, 0, &p2value));

    /*- Driver Identification -*/
                                                        
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION, 0, RSSCOPE_SPECIFIC_DRIVER_DESCRIPTION));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_PREFIX, 0, RSSCOPE_SPECIFIC_DRIVER_PREFIX));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_LOCATOR, 0, RSSCOPE_SPECIFIC_DRIVER_LOCATOR));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_VENDOR, 0, RSSCOPE_SPECIFIC_DRIVER_VENDOR));

    sprintf (buffer, 
             "Driver: %s %d.%d.%d, Compiler: %s %3.2f, "
             "Components: RSEngine %.2f, VISA-Spec %.2f",
             RSSCOPE_SPECIFIC_DRIVER_PREFIX,
             RSSCOPE_MAJOR_VERSION, RSSCOPE_MINOR_VERSION, RSSCOPE_MINOR_MINOR_VERSION,
             RS_COMPILER_NAME, RS_COMPILER_VER_NUM, 
             RS_ENGINE_MAJOR_VERSION + RS_ENGINE_MINOR_VERSION/10.0, 
             Rs_ConvertVISAVer(VI_SPEC_VERSION));

    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_REVISION, 0, buffer));
    p2value = RSSCOPE_CLASS_SPEC_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION, 0, &p2value));
    p2value = RSSCOPE_CLASS_SPEC_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION, 0, &p2value));

    /*- Driver Capabilities -*/
                                   
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SUPPORTED_INSTRUMENT_MODELS, 0, RSSCOPE_SUPPORTED_INSTRUMENT_MODELS));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_GROUP_CAPABILITIES, 0, RSSCOPE_GROUP_CAPABILITIES));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_FUNCTION_CAPABILITIES, 0, RSSCOPE_FUNCTION_CAPABILITIES));
    /* RS_ATTR_CHANNEL_COUNT        ... Rs_BuildRepCapTable */

    /*- Driver Setup -*/

    /* RS_ATTR_DRIVER_SETUP         ... Rs_SpecificDriverNew */

    /*- Instrument Identification -*/

    checkErr (Rs_GetAttribute (instrSession, "", RSSCOPE_ATTR_ID_QUERY_RESPONSE, 0, RSSCOPE_IO_BUFFER_SIZE, idQ));
    sscanf (idQ, "%[^,], %[^,],%*[^,], %256[^\n]", manufacturer, tmp_model, revision); // added 2 spaces in the parsing string
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_INSTRUMENT_MANUFACTURER, 0, manufacturer));
    sscanf (tmp_model,"%[^-0-9]",model); // added number elimination
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_INSTRUMENT_MODEL, 0, model));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_INSTRUMENT_FIRMWARE_REVISION, 0, revision));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_OPTIONS_LIST, 0, options_list));

    /*- Advanced Session Information -*/
                                  
    /*  
    RS_ATTR_IO_RESOURCE_DESCRIPTOR  ... rsscope_InitWithOptions
    RS_ATTR_LOGICAL_NAME            ... not supported
    */

    /*- Inherent Vendor Specific Attributes --------------------------------*/

    /*- Error Info -*/

    /*
    RS_ATTR_PRIMARY_ERROR           ... Rs_SetErrorInfo
    RS_ATTR_SECONDARY_ERROR         ... Rs_SetErrorInfo
    RS_ATTR_ERROR_ELABORATION       ... Rs_SetErrorInfo
    */

    /*- Session I/O -*/

    /*
    RS_ATTR_VISA_RM_SESSION         ... rsscope_RsInit
    RS_ATTR_IO_SESSION              ... Rs_UpdateIOSession
    RS_ATTR_IO_SESSION_TYPE         ... not supported
    */

    /*- Version Info -*/                     

    p2value = RSSCOPE_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION, 0, &p2value));
    p2value = RSSCOPE_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION, 0, &p2value));
    p2value = RSSCOPE_MINOR_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION, 0, &p2value));
    p2value = RSSCOPE_CLASS_SPEC_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_MAJOR_VERSION, 0, &p2value));
    p2value = RSSCOPE_CLASS_SPEC_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_MINOR_VERSION, 0, &p2value));
    p2value = RS_ENGINE_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_ENGINE_MAJOR_VERSION, 0, &p2value));
    p2value = RS_ENGINE_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_ENGINE_MINOR_VERSION, 0, &p2value));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_ENGINE_REVISION, 0, RS_ENGINE_REVISION));

    /*- Session Callbacks -*/                

    p2void = rsscope_WaitForOPCCallback;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_OPC_CALLBACK, 0, &p2void));
    p2void = rsscope_CheckStatusCallback;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CHECK_STATUS_CALLBACK, 0, &p2void));
    p2value = RSSCOPE_OPC_TIMEOUT;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_OPC_TIMEOUT, 0, &p2value));
    p2value = VI_TRUE;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_RANGE_CHECK, 0, &p2value));

Error:
    return error;
}

/*****************************************************************************
 * Function: rsscope_DefaultInstrSetup
 * Purpose:  This function sends a default setup to the instrument. The
 *           rsscope_reset function calls this function. The
 *           rsscope_RsInit function calls this function when the
 *           user passes VI_FALSE for the reset parameter. This function is
 *           useful for configuring settings that other instrument driver
 *           functions require.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rsscope_DefaultInstrSetup (ViSession instrSession)
{
    ViStatus    error = VI_SUCCESS;

    /* Set all the attributes to the default state. Do not update inherent attributes! */
    checkErr (Rs_ApplyAttributeDefaults (instrSession, VI_FALSE));

    /* Init attributes */
    checkErr( rsscope_InitAttributes (instrSession));

    if (!Rs_Simulating(instrSession))
        {
        viCheckErr( viPrintf (instrSession, "*CLS;*ESE %hu;*SRE 40;FORM:BPAT STRG\n", IEEE_488_2_ESE_MASK));
        }

Error:
    return error;
}

/*****************************************************************************
 * Function: rsscope_CheckStatus
 * Purpose:  This function checks the status of the instrument to detect
 *           whether the instrument has encountered an error. This function
 *           is called at the end of most exported driver functions. If the
 *           instrument reports an error, this function returns
 *           RS_ERROR_INSTRUMENT_SPECIFIC. The user can set the
 *           rsscope_ATTR_QUERY_INSTRUMENT_STATUS attribute to VI_FALSE to disable this
 *           check and increase execution speed.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rsscope_CheckStatus (ViSession instrSession)
{
    ViStatus    error = VI_SUCCESS;

    if (Rs_QueryInstrStatus (instrSession) && !Rs_Simulating (instrSession))
        {
        checkErr( rsscope_CheckStatusCallback (instrSession));
        }

Error:
    return error;
}

/*****************************************************************************
 * Function: rsscope_WaitForOPC
 * Purpose:  This function waits for the instrument to complete the
 *           execution of all pending operations. This function is a
 *           wrapper for the WaitForOPCCallback. It can be called from
 *           other instrument driver functions.
 *
 *           The maxTime parameter specifies the maximum time to wait for
 *           operation complete in milliseconds.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rsscope_WaitForOPC (ViSession instrSession, ViUInt32 maxTime)
{
    ViStatus    error = VI_SUCCESS;
    
    if (!Rs_Simulating(instrSession))
        {
        ViInt32  oldOPCTimeout;

        checkErr( Rs_GetAttribute (instrSession, VI_NULL, RSSCOPE_ATTR_OPC_TIMEOUT, 0,
                                   (unsigned int) sizeof (oldOPCTimeout), &oldOPCTimeout));

        Rs_SetAttribute (instrSession, VI_NULL, RSSCOPE_ATTR_OPC_TIMEOUT, 0, &maxTime);

        error = rsscope_WaitForOPCCallback (instrSession);

        Rs_SetAttribute (instrSession, VI_NULL, RSSCOPE_ATTR_OPC_TIMEOUT, 0, &oldOPCTimeout);

        viCheckErr( error);
        }
Error:
    return error;
}
 
/*===========================================================================*/
/* Function: String Index                                                    */
/* Purpose:  Returns the index of string in string array                     */
/*===========================================================================*/
ViInt32 rsscope_StringIndex(ViString array[], ViChar buff[])
{
    ViInt32 index = 0;

    while (array[index]){
        if (!strcmp(buff, array[index]))
            break; 
        index++;    
    }        
    /* If found string is not found returns -1. */
    if (!array[index]) return -1;

    return index;
}

/*===========================================================================*/
/* Function: Read Binary Data Block                                          */
/* Purpose:  Reads the binary data from instrument. Allocates memory for data*/
/* WARNING:  You must deallocate buffer, if any pointer has been returned.   */
/*           This function does not work correctly, when you read bin data   */
/*           via serial intfc                                            */
/*===========================================================================*/
ViStatus rsscope_readDataBlock (ViSession instrSession,
                                  ViChar **outputBuffer, ViUInt32 *byteCount)
{
    ViStatus    error   = VI_SUCCESS;
    ViUInt16    intf_type, term_en;
    ViUInt32    ret_cnt;
    ViInt32     len;
    ViChar      buffer[RSSCOPE_IO_BUFFER_SIZE];
    
    *outputBuffer = VI_NULL;
	
	if (byteCount == NULL)
		return VI_ERROR_PARAMETER3;
    
    /* Disable termination character on serial */
    checkErr (viGetAttribute (instrSession, VI_ATTR_INTF_TYPE, &intf_type));
    /* Disable termination character */
    checkErr (viGetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, &term_en));
    checkErr (viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_FALSE));

    if (intf_type == VI_INTF_ASRL)
    {
        checkErr (viSetAttribute (instrSession, VI_ATTR_ASRL_END_IN, VI_ASRL_END_NONE));
    }

    /* Parse header */
    checkErr (viRead (instrSession, (ViBuf) buffer, 1, &ret_cnt)); 
    if (buffer[0]=='#')
    {   /* Binary data */
        /* Disable termination character */
        checkErr (viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_FALSE));
    
         /* Disable termination character on serial */
        if (intf_type == VI_INTF_ASRL)
        {
            checkErr (viSetAttribute (instrSession, VI_ATTR_ASRL_END_IN, VI_ASRL_END_NONE));
        }
        /* Parse header */
        checkErr (viRead (instrSession, (ViBuf) buffer, 1, &ret_cnt));

        buffer[1] = '\0';
		if (buffer[0] == '(')
		{
			checkErr (viScanf (instrSession, "%ld)", &len));
		}
		else
			sscanf (buffer, "%ld", &len);
		
		if (len > 0)
		{
	        checkErr (viRead (instrSession, (ViBuf) buffer, len, &ret_cnt));
	        buffer[len] = '\0';
	        sscanf (buffer, "%ld", &len);
        
	        checkAlloc (*outputBuffer = (ViChar*) calloc (len, sizeof (ViChar)));
	        /* Read useful data */
	        checkErr (viRead (instrSession, (ViBuf) *outputBuffer, len, &ret_cnt));
    
	        if (len != (ViInt32) ret_cnt)
	            viCheckErr (RS_ERROR_UNEXPECTED_RESPONSE);

			/* Flush garbage */
	        viScanf (instrSession,"%*[^\r\n]");
			*byteCount = len;
			if (error > 0) error = VI_SUCCESS;
		}
		else
		{
			/* Unlimited size of data */
			checkErr (Rs_ReadDataUnknownLength (instrSession, outputBuffer, byteCount));
		}
    }
    else
    {   /* ASCII data */
        /* read rest of first value */
		ViChar* extBuf = NULL;

		/* read all values */
        viCheckErr (Rs_ReadDataUnknownLength(instrSession, &extBuf, byteCount));
	    checkAlloc (*outputBuffer = (ViChar *)calloc (*byteCount + 2, sizeof (ViChar)));
        **outputBuffer = buffer[0];
		memcpy (*outputBuffer + 1, extBuf, *byteCount);
		*byteCount = *byteCount + 1;
		error = 1;
		
		if (extBuf) free (extBuf);
    }

Error:
    viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_TRUE);
    switch (intf_type)
    {
        case VI_INTF_ASRL:
            viSetAttribute (instrSession, VI_ATTR_ASRL_END_IN, VI_ASRL_END_TERMCHAR);
        break;    
    }    
    return error;
}

/*===========================================================================*/
/* Function: Long Signed Integer Value Out Of Range - ViInt32                */
/* Purpose:  This function checks a long signed integer value to see if it   */
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range, the return value is VI_TRUE, otherwise the return     */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViBoolean rsscope_invalidViInt32Range (ViSession instrSession, ViInt32 val, ViInt32 min, ViInt32 max)
{
    return (Rs_RangeChecking (instrSession) && (ViBoolean)((val < min || val > max) ? VI_TRUE : VI_FALSE));
}
/*===========================================================================*/
/* Function: Long Unsigned Integer Value Out Of Range - ViUInt32             */
/* Purpose:  This function checks a long unsigned integer value to see if it */
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range, the return value is VI_TRUE, otherwise the return     */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViBoolean rsscope_invalidViUInt32Range (ViSession instrSession,ViUInt32 val, ViUInt32 min, ViUInt32 max)
{
    return (Rs_RangeChecking (instrSession) && (ViBoolean)((val < min || val > max) ? VI_TRUE : VI_FALSE));
}
/*===========================================================================*/
/* Function: Real (Double) Value Out Of Range - ViReal64                     */
/* Purpose:  This function checks a real (double) value to see if it lies    */
/*           between a minimum and maximum value.  If the value is out of    */
/*           range, the return value is VI_TRUE, otherwise the return value  */
/*           is VI_FALSE.                                                    */
/*===========================================================================*/
ViBoolean rsscope_invalidViReal64Range (ViSession instrSession,ViReal64 val, ViReal64 min, ViReal64 max)
{
    return (Rs_RangeChecking (instrSession) && (ViBoolean)((val < min || val > max) ? VI_TRUE : VI_FALSE));
}
/*===========================================================================*/
/* Function: Boolean Value Out Of Range - ViBoolean                          */
/* Purpose:  This function checks a Boolean to see if it is equal to VI_TRUE */
/*           or VI_FALSE. If the value is out of range, the return value is  */
/*           VI_TRUE, otherwise the return value is VI_FALSE.                */
/*===========================================================================*/
ViBoolean rsscope_invalidViBooleanRange (ViSession instrSession,ViBoolean val)
{
    return (Rs_RangeChecking (instrSession) && (ViBoolean)((val != VI_FALSE && val != VI_TRUE) ? VI_TRUE : VI_FALSE));
}
/*===========================================================================*/
/* Function: Swap 32bit Integer                                              */
/* Purpose:  Byte order for binary transfers depends on MOTOROLA or INTEL    */
/*           formats.                                                        */
/*===========================================================================*/
void rsscope_SWAP_32(unsigned char *data, long points)
{
    /* MOTOROLA (byte order 0123) or INTEL (byte order 3210). */
    unsigned int    word = 0x1122;
    unsigned char   *p2word = (unsigned char*)&word;

    if (*p2word == 0x11) /* MOTOROLA format */
    {
       unsigned char    src[4];
       long             *p2data = (long*)data;
       int              idx;

       for (idx = 0; idx < points; idx++, p2data++)
          {
              *((long *)src) = *(p2data);
              ((unsigned char *)(p2data))[0] =  ((unsigned char*)(src))[3];
              ((unsigned char *)(p2data))[1] =  ((unsigned char*)(src))[2];
              ((unsigned char *)(p2data))[2] =  ((unsigned char*)(src))[1];
              ((unsigned char *)(p2data))[3] =  ((unsigned char*)(src))[0];
          }
    }

   return;
}

/*===========================================================================*/
/* Function: Parse Catalog List                                              */
/* Purpose:  Parse Catalog List returned from instrument and removes from it */
/*           all unneeded parameters from this list.                         */
/*===========================================================================*/
ViStatus rsscope_ParseCatalog(ViChar *buffer, ViInt32 size, ViChar *catalogList, ViInt32 *nbValues)
{
    ViStatus    error = VI_SUCCESS; 
    ViChar*     pbuf;
    ViInt32     num;
    
    if (size != 0)
    {
        memcpy(catalogList, buffer, ( size > (ViInt32)strlen(buffer)) ? strlen(buffer) : size);
    }
    pbuf = strtok(buffer, ",");
    num=0;
    while (pbuf) 
    {
        num++;
        pbuf = strtok(NULL, ",");        
    } 
    if (nbValues) *nbValues = num;
    
    return error;
}

/*===========================================================================*/
/* Function: Parse Limit Line Catalog                                        */
/* Purpose:  Parse Limit Line Catalog returned from instrument and removes   */
/*           from it all unneeded parameters from this list.                 */
/*===========================================================================*/
ViStatus rsscope_ParseLimitLineCatalog(ViChar *buffer, ViInt32 size, ViChar *catalogList, ViInt32 *nbValues)
{
    ViStatus    rsscope_status = VI_SUCCESS;
    ViChar*     plist_of_files = 0;
    ViChar*     ptag = NULL;
    ViChar*     pend = NULL;
    ViInt32     i = 0;
    
    if (*buffer != '\0')
    {
        sscanf(buffer, "%*ld,%*ld,%[^\r\n]", buffer);
        plist_of_files = (ViChar*)calloc (strlen (buffer)+1, sizeof (ViChar));
        pend = plist_of_files;
        *pend = '\0';
        ptag = strtok(buffer, ",");
        while (ptag != NULL && rsscope_status == VI_SUCCESS)
        {
            i++;
            pend += sprintf(pend, "%s,", ptag+1);
            ptag = strtok(NULL, ",");
            if (ptag == NULL)
                rsscope_status = RS_ERROR_INVALID_VALUE;
            else
                ptag = strtok(NULL, ",");
        }
    }
    
    *--pend = '\0';

    if (nbValues) *nbValues = i;

    strncpy(catalogList, plist_of_files, size);
    
    free(plist_of_files);

    return rsscope_status;
}

/*===========================================================================*/
/* Function: Read Trace Data                                                 */
/* Purpose:  This function reads out trace data from the instrument.         */
/*           It checks if data are ASCII or binary                           */
/*===========================================================================*/
ViStatus rsscope_dataReadTrace (ViSession instrSession,
                                 ViString trace, 
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR traceData[],
                                 ViPInt32 noofPoints)
{
    ViChar      *extBuf=VI_NULL;
    ViReal32    *temp;
    ViUInt32    i = 0;
    ViStatus    error = VI_SUCCESS;
    ViUInt32    count=0;
    ViChar      *p2buf=VI_NULL;
    ViUInt32    ret_cnt;
    
    viCheckErr (viPrintf (instrSession, ":FORM REAL,32;%s\n", trace));
    viCheckErr (rsscope_readDataBlock(instrSession, &extBuf, &ret_cnt));
	
	if (error == VI_SUCCESS)
	{ 	/* binary data, apply conversion */
        /* Convert binary data into array of ViReal64 types. */
        count = (ViInt32)(ret_cnt/4);
        /* Binary data byte order (MOTOROLA or INTEL). */
        rsscope_SWAP_32((ViPBuf)extBuf, count);
        /* Pointer to data */
        temp = (ViReal32 *)extBuf;
        if (noofPoints) *noofPoints=count;
    
        count=(count<(ViUInt32)arrayLength)?count:(ViUInt32)arrayLength;
    
        for (i = 0; i < count; i++)
            if (i<(ViUInt32)arrayLength)
            *traceData++ = (ViReal64)*temp++;
    }
    else
        
    {   /* ASCII data */
        //read rest of first value

        p2buf = strtok(extBuf, ",\r\n");
        i = 0;
        while (p2buf)
        {
            if (i < (ViUInt32)arrayLength)
            {
                traceData[i] = atof (p2buf);
            }   
            p2buf = strtok(NULL, ",");
            i++;
        }
    
        if (noofPoints) *noofPoints=i; 
    
    }

Error:
    if (extBuf) free(extBuf);
    return error;
}

/*===========================================================================*/
/* Function: Read Trace Data                                                 */
/* Purpose:  This function reads out trace data from the instrument.         */
/*           It checks if data are ASCII or binary                           */
/*===========================================================================*/
ViStatus rsscope_dataReadTraceIQ (ViSession instrSession,
                                 ViString trace, 
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR i[],
                                 /*@out@*/ViReal64 _VI_FAR q[],
                                 ViPInt32 noofPoints)
{
    ViChar      *extBuf=VI_NULL;
    ViReal32    *temp;
    ViUInt32    ndx = 0;
    ViStatus    error = VI_SUCCESS;
    ViUInt32    count=0;
    ViChar      *p2buf=VI_NULL;
    ViUInt32    ret_cnt;
    
    viCheckErr (viPrintf (instrSession, ":FORM REAL,32;%s\n", trace));
    viCheckErr (rsscope_readDataBlock(instrSession, &extBuf, &ret_cnt));
	if (*extBuf == '0')
	{
		free (extBuf);
		if (noofPoints) *noofPoints = 0;
		return RSSCOPE_WARN_DATA_NOT_AVAILABLE;
	}
	
	if (error == VI_SUCCESS)
	{ 	/* binary data, apply conversion */
        /* Convert binary data into array of ViReal64 types. */
        count = (ViInt32)(ret_cnt/4);
        /* Binary data byte order (MOTOROLA or INTEL). */
        rsscope_SWAP_32((ViPBuf)extBuf, count);
        /* Pointer to data */
        temp = (ViReal32 *)extBuf;
		count /= 2;
        if (noofPoints) *noofPoints=count;
    
        count=(count<(ViUInt32)arrayLength)?count:(ViUInt32)arrayLength;
    
        for (ndx = 0; ndx < count; ndx++)
		{
            *i++ = (ViReal64)* (temp + 2 * ndx);
			*q++ = (ViReal64)* (temp + 2 * ndx + 1);
		}
			
    }
    else
        
    {   /* ASCII data */
        //read rest of first value

        p2buf = strtok(extBuf, ",\r\n");
        ndx = 0;
        while (p2buf)
        {
            if (ndx < (ViUInt32)arrayLength)
            {
                i[ndx] = atof (p2buf);
	            p2buf = strtok(NULL, ",");
				q[ndx] = atof (p2buf);
            }   
            p2buf = strtok(NULL, ",");
            ndx++;
        }
    
        if (noofPoints) *noofPoints=ndx; 
    
    }

Error:
    if (extBuf) free(extBuf);
    return error;
}

/*===========================================================================*/
/* Function: Read ASCII Trace Data                                           */
/* Purpose:  This function reads out trace data in ascii form from           */
/*           the instrument.                                                 */
/*===========================================================================*/
ViStatus rsscope_dataAsciiReadTrace (ViSession instrSession,
                                 ViInt32 window,
                                 ViString trace, 
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR traceData[],
                                 ViPInt32 noofPoints)
{
    ViUInt32 retCnt = 0;
    ViChar *extBuf=VI_NULL;
    ViChar *pbuffer;
    ViInt32  i = 0;
    ViStatus error = VI_SUCCESS;
    
    
/*Don't put parameter range checking here! 
All parameters has to be checked in high level function */      
    if (window==0)    
    {
        viCheckErr (viPrintf (instrSession, "*CLS;:TRAC? %s\n",
                trace));
    }
    else
    {
        viCheckErr (viPrintf (instrSession, "*CLS;:TRAC%ld? %s\n",
                window, trace));                
    }
    viCheckErr (Rs_ReadDataUnknownLength(instrSession, &extBuf, &retCnt)); 

    pbuffer = strtok(extBuf, ",");
    i=0;
    while (pbuffer) 
    {
        if (i < arrayLength)
        {
            traceData[i++] = atof (pbuffer);
        }   
        pbuffer = strtok(NULL, ",");        
    }
    
    if (noofPoints) *noofPoints=i;    
    
    
Error:
   
    if (extBuf) free(extBuf);
    return error;
}

/*===========================================================================*/
/* Function: Read Trace Data                                                 */
/* Purpose:  This function only reads out trace data from the instrument.    */
/*           It checks if data are ASCII or binary.                           */
/*===========================================================================*/
ViStatus rsscope_dataReadTraceOnly (ViSession instrSession,
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR traceData[],
                                 ViPInt32 noofPoints)
{
    ViChar      *extBuf=VI_NULL;
    ViReal32    *temp;
    ViUInt32     i = 0;
    ViStatus    error = VI_SUCCESS;
    ViUInt16    intfc = VI_INTF_GPIB;
    ViUInt32    count=0;
    ViChar      buffer[RSSCOPE_IO_BUFFER_SIZE];
    ViChar      *p2buf=VI_NULL;
    ViUInt32    ret_cnt;
    ViInt32     len;
    
    checkErr (viGetAttribute (instrSession, VI_ATTR_INTF_TYPE, &intfc));
    //Check first character            
    checkErr (viRead (instrSession, (ViBuf) buffer, 1, &ret_cnt)); 
    if (buffer[0]=='#')
        /*Binary data*/
    {
        /* Disable termination character */
        checkErr (viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_FALSE));
    
         /* Disable termination character on serial */
        if (intfc == VI_INTF_ASRL)
        {
            checkErr (viSetAttribute (instrSession, VI_ATTR_ASRL_END_IN, VI_ASRL_END_NONE));
        }
        /* Parse header */
        checkErr (viRead (instrSession, (ViBuf) buffer, 1, &ret_cnt));
        buffer[1] = '\0';
        sscanf (buffer, "%ld", &len);
        checkErr (viRead (instrSession, (ViBuf) buffer, len, &ret_cnt));
        buffer[len] = '\0';
        sscanf (buffer, "%ld", &len);
        
        if (len>0)
        {
            checkAlloc (extBuf = (ViChar*) calloc (len, sizeof (ViChar)));
            /* Read useful data */
            checkErr (viRead (instrSession, (ViBuf) extBuf, len, &ret_cnt));
    
            if (len != (ViInt32) ret_cnt)
                viCheckErr (RS_ERROR_UNEXPECTED_RESPONSE);

            /* Flush garbage */
            viScanf (instrSession,"%*[^\r\n]");
            /* Convert binary data into array of ViReal64 types. */
            count = (ViInt32)(ret_cnt/4);
            /* Binary data byte order (MOTOROLA or INTEL). */
            rsscope_SWAP_32((ViPBuf)extBuf, count);
            /* Pointer to data */
            temp = (ViReal32 *)extBuf;
            if (noofPoints) *noofPoints=count;    
    
            count=(count<(ViUInt32)arrayLength)?count:(ViUInt32)arrayLength;
    
            for (i = 0; i < count; i++)
                if (i<(ViUInt32)arrayLength)
                *traceData++ = (ViReal64)*temp++;
        }
        else
        {
            /* Flush garbage */
            viScanf (instrSession,"%*[^\r\n]");
            if (noofPoints) *noofPoints=0; 
        }
    }
    else
        /*ASCII data*/
    {
        //read rest of first value
        p2buf=buffer;
        while((p2buf[0]!=',')&&(p2buf[0]!='\r')&&(p2buf[0]!='\n')){
            p2buf++;
            checkErr (viRead (instrSession, (ViBuf) p2buf, 1, &ret_cnt)); 
        }
        traceData[0] = atof (buffer); 
        //read all values
        viCheckErr (Rs_ReadDataUnknownLength(instrSession, &extBuf, &ret_cnt)); 

        p2buf = strtok(extBuf, ",");
        i=1;
        while (p2buf) 
        {
            if (i < (ViUInt32) arrayLength)
            {
                traceData[i] = atof (p2buf);
            }   
            p2buf = strtok(NULL, ",");  
            i++;
        }
    
        if (noofPoints) *noofPoints=i; 
    
    }

Error:
    viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_TRUE);
    switch (intfc)
    {
        case VI_INTF_ASRL:
            viSetAttribute (instrSession, VI_ATTR_ASRL_END_IN, VI_ASRL_END_TERMCHAR);
        break;    
    }    
    if (extBuf) free(extBuf);
    return error;
}

/*****************************************************************************
 * Function: rsscope_CheckBeforeRead
 * Purpose:  This function waits for the instrument to complete the
 *           execution of all pending operations and returns data. 
 *
 *           The maxTime parameter specifies the maximum time to wait for
 *           operation complete in milliseconds.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rsscope_CheckBeforeRead (ViSession instrSession, ViUInt32 maxTime)
{
    ViStatus    error = VI_SUCCESS;
    ViUInt16    response    = 0;
    ViUInt32     counter     = 0;
    ViUInt16    intfc   = VI_INTF_GPIB;
 
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

                Rs_Delay (0.01);
                counter++;

                if (counter >= maxTime)
                    return VI_ERROR_TMO;

                /* Wait while STB is non zero value. Only Error/Event Queue
                   and ESB bits are taken into consideration. */
            
            } while ((response & 0x14) == 0);

            /* (check Error(Event) Queue bit in STB) */
            /* sometimes instrument sets both bits, but error queue is empty */
            return (((response & 0x4) != 0) && ((response & 0x10) == 0)) ? RS_ERROR_INSTRUMENT_STATUS : error;
        }

Error:
    return error;
}

/*===========================================================================*/
/* Function: Clear STB Before Read                                           */
/* Purpose:  This is a utility function which clears error and message queue */
/*           before starting a query                                         */
/*===========================================================================*/
ViStatus rsscope_ClearBeforeRead (ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;
    ViUInt16 response = 0;
    ViChar  garbage[10];

    viCheckErr (viReadSTB (instrSession, &response));
    
    while (response & 0x14)
    {
        if (response & 0x4)
        {
            ViInt32 error;
            viCheckErr(viQueryf(instrSession, "*ESR?\n", "%ld", &error));
            viCheckErr(viQueryf(instrSession, ":SYST:ERR?\n", "%*[^\r\n]"));
        }
        
        if (response & 0x10)
            viRead (instrSession, (ViBuf) garbage, 10, VI_NULL);

        viCheckErr (viReadSTB (instrSession, &response));
    
    }

Error:
    return error;
}

/// HIFN This function returns repeated capabilty name according to attribute and repeated capability id
/// HIRET Returns regular status code
/// HIPAR instrSession/Session.
/// HIPAR attributeID/Attribute ID
/// HIPAR repCapNameId/Repeated capability ID. For instance: Channel
/// HIPAR value/Numeric value of repeated capability (index in array of names)
/// HIPAR bufferSize/Size of repCapName array
/// HIPAR repCapName/String representing repeated capability name
ViStatus rsscope_GetAttributeRepCapName (ViSession instrSession,
                                ViUInt32 attributeID,
                                ViString repCapNameId,
                                ViInt32 value,
                                ViInt32 bufferSize,
                                ViChar _VI_FAR repCapName[])
{
    ViStatus error = VI_SUCCESS;
    ViChar   *p2buf = NULL;
    ViChar   names [RS_MAX_MESSAGE_BUF_SIZE] = "";
    int      i = 0;
    
    checkErr (rsscope_GetAttributeRepeatedCapabilityIdNames (instrSession,
                                                             attributeID,
                                                             repCapNameId,
                                                             RS_MAX_MESSAGE_BUF_SIZE,
                                                             names));
    
    p2buf = strtok (names, ",");
    while (p2buf)
    {
        if (value == i++)
        {
            strncpy (repCapName, p2buf, bufferSize);
            break;
        }
        p2buf = strtok (NULL, ",");
    }
    if (p2buf == NULL)
        error = RS_ERROR_INVALID_REPEATED_CAPABILITY_NAME;
Error:
    return error;
}

void Convert2Binary (int decimal, char *bin)
{
    unsigned int mask;      // used to check each individual bit, 
                            //    unsigned to alleviate sign 
                            //    extension problems

    mask = 0x40;      // Set only the high-end bit
    while (mask)            // Loop until MASK is empty
    {
        if (decimal & mask)     // test the masked bit
              *bin = '1';   // if true, value is 1
          else 
              *bin = '0';   // if false, value is 0
        bin++;              // next character
        mask >>= 1;         // shift the mask 1 bit
    }
    *bin = 0;               // add the trailing null 
}

int ConvertFromBinary(char *buf, int cbase)
{
    int j;
    int bin;
    
    j = 0;
    bin = 0;                 // start the binary value at 0
    while (buf[j])
    {
        buf[j] -= 48;           // convert character for binary
        if (buf[j] > 16)
            buf[j] -= 7;        // character was probably letter
        if (buf[j] >= cbase)
            buf[j] -= 32;       // character was probably lower 
        if (buf[j] >= cbase || buf[j] < 0)
            break;              // invalid character, done
        bin *= cbase;           // multiply by the base 
        bin += buf[j];          // add current value
        j++;                    // next character
    }
    return bin;             // return the binary value
}

ViBoolean rsscope_CheckOption (ViSession instrSession, ViString option)
{
	ViChar   buffer [RSSCOPE_IO_BUFFER_SIZE];
    RsSessionPropertiesPtr sessionProperties = Rs_ViSession (instrSession);

    if (sessionProperties->optionChecking)
	{
		if (rsscope_GetAttributeViString (instrSession, "", RS_ATTR_OPTIONS_LIST, RSSCOPE_IO_BUFFER_SIZE, buffer) != VI_SUCCESS)
			return VI_FALSE;
		else
    		return (strstr(buffer, option) != NULL);
	}
	return VI_TRUE;
}
