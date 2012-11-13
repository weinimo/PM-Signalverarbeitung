/*****************************************************************************
 *- Utility Function Declarations (Non-Exported) ----------------------------*
 *****************************************************************************/

#include <visa.h>

ViStatus rsscope_InitAttributes (ViSession vi);
ViStatus rsscope_DefaultInstrSetup (ViSession openInstrSession);
ViStatus rsscope_CheckStatus (ViSession vi);
ViStatus rsscope_WaitForOPC (ViSession vi, ViUInt32 maxTime);
ViInt32 rsscope_StringIndex(ViString array[], ViChar buff[]); 
ViStatus rsscope_readDataBlock (ViSession instrSession,
                                  /*@out@*/ViChar **outputBuffer, /*@out@*/ViUInt32 *byteCount);
ViBoolean rsscope_invalidViInt32Range (ViSession instrSession, ViInt32 val, ViInt32 min, ViInt32 max);
ViBoolean rsscope_invalidViUInt32Range (ViSession instrSession,ViUInt32 val, ViUInt32 min, ViUInt32 max);
ViBoolean rsscope_invalidViReal64Range (ViSession instrSession,ViReal64 val, ViReal64 min, ViReal64 max);
ViBoolean rsscope_invalidViBooleanRange (ViSession instrSession,ViBoolean val);
ViStatus rsscope_ParseCatalog(ViChar *buffer, ViInt32 size, ViChar *catalogList, ViInt32 *nbValues);
ViStatus rsscope_ParseLimitLineCatalog(ViChar *buffer, ViInt32 size, ViChar *catalogList, ViInt32 *nbValues);
void rsscope_SWAP_32(unsigned char *data, long points);  
ViStatus rsscope_dataReadTrace (ViSession instrSession,
                                 ViString trace, 
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR traceData[],
                                 ViPInt32 noofPoints);
ViStatus rsscope_dataReadTraceOnly (ViSession instrSession,
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR traceData[],
                                 ViPInt32 noofPoints);
ViStatus rsscope_dataAsciiReadTrace (ViSession instrSession,
                                 ViInt32 window,
                                 ViString trace, 
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR traceData[],
                                 ViPInt32 noofPoints);
ViStatus rsscope_dataReadTraceIQ (ViSession instrSession,
                                 ViString trace, 
                                 ViInt32 arrayLength, 
                                 /*@out@*/ViReal64 _VI_FAR i[],
                                 /*@out@*/ViReal64 _VI_FAR q[],
                                 ViPInt32 noofPoints);
ViStatus rsscope_CheckBeforeRead (ViSession instrSession, ViUInt32 maxTime);
ViStatus rsscope_ClearBeforeRead (ViSession instrSession);
ViStatus rsscope_WaitForOPCCallback (ViSession io);
ViStatus rsscope_GetAttributeRepCapName (ViSession instrSession,
                                ViUInt32 attributeID,
                                ViString repCapNameId,
                                ViInt32 value,
                                ViInt32 bufferSize,
                                ViChar _VI_FAR repCapName[]);
void Convert2Binary(int decimal, char *bin);
int ConvertFromBinary(char *buf, int cbase);
ViBoolean rsscope_CheckOption (ViSession instrSession, ViString option);
