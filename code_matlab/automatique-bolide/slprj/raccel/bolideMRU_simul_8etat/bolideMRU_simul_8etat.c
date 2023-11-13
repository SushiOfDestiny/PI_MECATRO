#include "bolideMRU_simul_8etat.h"
#include "rtwtypes.h"
#include <string.h>
#include "mwmathutil.h"
#include "bolideMRU_simul_8etat_private.h"
#include "rt_logging_mmi.h"
#include "bolideMRU_simul_8etat_capi.h"
#include "bolideMRU_simul_8etat_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; extern ssExecutionInfo gblExecutionInfo ; RTWExtModeInfo *
gblRTWExtModeInfo = NULL ; void raccelForceExtModeShutdown ( boolean_T
extModeStartPktReceived ) { if ( ! extModeStartPktReceived ) { boolean_T
stopRequested = false ; rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 2 , &
stopRequested ) ; } rtExtModeShutdown ( 2 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 2 ; const char_T
* gbl_raccel_Version = "23.2 (R2023b) 01-Aug-2023" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; int_T enableFcnCallFlag [ ] = { 1 , 1 } ; const char
* raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S , const char *
inportFileName , int * matFileFormat ) { return rt_RAccelReadInportsMatFile (
S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
#define gl2johm1a5 (-1)
B rtB ; X rtX ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS =
& model_S ; void MdlInitialize ( void ) { memcpy ( & rtX . mzx0gi3owr [ 0 ] ,
& rtP . statebar [ 0 ] , sizeof ( real_T ) << 3U ) ; rtDW . hbnszvowgl =
false ; rtDW . llhn4bw3ym = gl2johm1a5 ; } void MdlStart ( void ) { { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { real_T id ; real_T
iddot ; real_T is ; real_T isdot ; memcpy ( & rtB . mx20xi1qvn [ 0 ] , & rtX
. mzx0gi3owr [ 0 ] , sizeof ( real_T ) << 3U ) ; if ( ssIsSampleHit ( rtS , 1
, 0 ) ) { rtDW . jhmp3qvn5s = ( ssGetTaskTime ( rtS , 1 ) >= rtP . Step_Time
) ; if ( rtDW . jhmp3qvn5s == 1 ) { rtB . dmcwhlxyjn = rtP . Urbar - 2.0 ; }
else { rtB . dmcwhlxyjn = rtP . Urbar ; } rtDW . mp3rt0g3za = ( ssGetTaskTime
( rtS , 1 ) >= rtP . Step1_Time ) ; if ( rtDW . mp3rt0g3za == 1 ) { rtB .
ax01y1div4 = rtP . Ulbar - 2.0 ; } else { rtB . ax01y1div4 = rtP . Ulbar ; }
rtDW . g1eobre1no = ( ssGetTaskTime ( rtS , 1 ) >= rtP . Step2_Time ) ; if (
rtDW . g1eobre1no == 1 ) { rtB . cvte4gsxdy = rtP . Step2_YFinal ; } else {
rtB . cvte4gsxdy = rtP . Step2_Y0 ; } rtDW . mkzmfsijdn = ( ssGetTaskTime (
rtS , 1 ) >= rtP . Step3_Time ) ; if ( rtDW . mkzmfsijdn == 1 ) { rtB .
dxox3p2m4x = rtP . Step3_YFinal ; } else { rtB . dxox3p2m4x = rtP . Step3_Y0
; } } rtDW . llhn4bw3ym = gl2johm1a5 ; is = rtB . mx20xi1qvn [ 4 ] + rtB .
mx20xi1qvn [ 5 ] ; id = rtB . mx20xi1qvn [ 4 ] - rtB . mx20xi1qvn [ 5 ] ;
isdot = ( ( ( ( ( rtB . dmcwhlxyjn + rtB . ax01y1div4 ) + rtB . cvte4gsxdy )
+ rtB . dxox3p2m4x ) - rtP . R * is ) - 2.0 * rtP . k / rtP . rho * rtB .
mx20xi1qvn [ 1 ] ) * ( 1.0 / rtP . L ) ; iddot = ( ( ( ( ( rtB . dmcwhlxyjn -
rtB . ax01y1div4 ) + rtB . cvte4gsxdy ) - rtB . dxox3p2m4x ) - rtP . R * id )
- rtP . k * rtP . l / rtP . rho * rtB . mx20xi1qvn [ 3 ] ) * ( 1.0 / rtP . L
) ; rtB . cmlaobun0c [ 0 ] = rtB . mx20xi1qvn [ 1 ] ; rtB . cmlaobun0c [ 1 ]
= ( rtP . k / rtP . rho * is - rtP . mb * rtP . d * ( rtB . mx20xi1qvn [ 3 ]
* rtB . mx20xi1qvn [ 3 ] ) ) * ( 1.0 / rtP . beta ) ; rtB . cmlaobun0c [ 2 ]
= rtB . mx20xi1qvn [ 3 ] ; rtB . cmlaobun0c [ 3 ] = ( rtP . l * rtP . k / (
2.0 * rtP . rho ) * id + rtP . mb * rtP . d * rtB . mx20xi1qvn [ 1 ] * rtB .
mx20xi1qvn [ 3 ] ) * ( 1.0 / rtP . gamma ) ; rtB . cmlaobun0c [ 4 ] = ( isdot
+ iddot ) * 0.5 ; rtB . cmlaobun0c [ 5 ] = ( isdot - iddot ) * 0.5 ; rtB .
cmlaobun0c [ 6 ] = muDoubleScalarSin ( rtB . mx20xi1qvn [ 2 ] ) * rtB .
mx20xi1qvn [ 1 ] ; rtB . cmlaobun0c [ 7 ] = muDoubleScalarCos ( rtB .
mx20xi1qvn [ 2 ] ) * rtB . mx20xi1qvn [ 1 ] ; if ( ssIsSampleHit ( rtS , 1 ,
0 ) ) { } UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) { XDot * _rtXdot ;
_rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; memcpy ( & _rtXdot -> mzx0gi3owr [
0 ] , & rtB . cmlaobun0c [ 0 ] , sizeof ( real_T ) << 3U ) ; } void
MdlProjection ( void ) { } void MdlZeroCrossings ( void ) { ZCV * _rtZCSV ;
_rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ; _rtZCSV ->
bztjzebkiv = ssGetT ( rtS ) - rtP . Step_Time ; _rtZCSV -> odck5cytne =
ssGetT ( rtS ) - rtP . Step1_Time ; _rtZCSV -> dj0df2pbfy = ssGetT ( rtS ) -
rtP . Step2_Time ; _rtZCSV -> hijvu4qzbz = ssGetT ( rtS ) - rtP . Step3_Time
; } void MdlTerminate ( void ) { } static void
mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( mxArray * destArray , mwIndex i
, int j , const void * srcData , size_t numBytes ) ; static void
mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( mxArray * destArray , mwIndex i
, int j , const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( void *
destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ;
static void mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( void * destData
, const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy (
( uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_bolideMRU_simul_8etat_cacheBitFieldToMxArray ( mxArray * destArray ,
mwIndex i , int j , uint_T bitVal ) ; static void
mr_bolideMRU_simul_8etat_cacheBitFieldToMxArray ( mxArray * destArray ,
mwIndex i , int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j
, mxCreateDoubleScalar ( ( real_T ) bitVal ) ) ; } static uint_T
mr_bolideMRU_simul_8etat_extractBitFieldFromMxArray ( const mxArray *
srcArray , mwIndex i , int j , uint_T numBits ) ; static uint_T
mr_bolideMRU_simul_8etat_extractBitFieldFromMxArray ( const mxArray *
srcArray , mwIndex i , int j , uint_T numBits ) { const uint_T varVal = (
uint_T ) mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return
varVal & ( ( 1u << numBits ) - 1u ) ; } static void
mr_bolideMRU_simul_8etat_cacheDataToMxArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes )
; static void mr_bolideMRU_simul_8etat_cacheDataToMxArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_bolideMRU_simul_8etat_restoreDataFromMxArrayWithOffset ( void *
destData , const mxArray * srcArray , mwIndex i , int j , mwIndex offset ,
size_t numBytes ) ; static void
mr_bolideMRU_simul_8etat_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData (
mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData ,
( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static
void mr_bolideMRU_simul_8etat_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static
void mr_bolideMRU_simul_8etat_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( real_T ) fieldVal ) ) ; } static uint_T
mr_bolideMRU_simul_8etat_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ;
static uint_T mr_bolideMRU_simul_8etat_extractBitFieldFromCellArrayWithOffset
( const mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T
numBits ) { const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_bolideMRU_simul_8etat_GetDWork ( ) {
static const char_T * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" ,
"NULL_PrevZCX" , } ; mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 ,
ssDWFieldNames ) ; mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( ssDW , 0 , 0
, ( const void * ) & ( rtB ) , sizeof ( rtB ) ) ; { static const char_T *
rtdwDataFieldNames [ 7 ] = { "rtDW.llhn4bw3ym" , "rtDW.jhmp3qvn5s" ,
"rtDW.mp3rt0g3za" , "rtDW.g1eobre1no" , "rtDW.mkzmfsijdn" , "rtDW.gdaqfrous0"
, "rtDW.hbnszvowgl" , } ; mxArray * rtdwData = mxCreateStructMatrix ( 1 , 1 ,
7 , rtdwDataFieldNames ) ; mr_bolideMRU_simul_8etat_cacheDataAsMxArray (
rtdwData , 0 , 0 , ( const void * ) & ( rtDW . llhn4bw3ym ) , sizeof ( rtDW .
llhn4bw3ym ) ) ; mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( rtdwData , 0 ,
1 , ( const void * ) & ( rtDW . jhmp3qvn5s ) , sizeof ( rtDW . jhmp3qvn5s ) )
; mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const
void * ) & ( rtDW . mp3rt0g3za ) , sizeof ( rtDW . mp3rt0g3za ) ) ;
mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void
* ) & ( rtDW . g1eobre1no ) , sizeof ( rtDW . g1eobre1no ) ) ;
mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void
* ) & ( rtDW . mkzmfsijdn ) , sizeof ( rtDW . mkzmfsijdn ) ) ;
mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void
* ) & ( rtDW . gdaqfrous0 ) , sizeof ( rtDW . gdaqfrous0 ) ) ;
mr_bolideMRU_simul_8etat_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void
* ) & ( rtDW . hbnszvowgl ) , sizeof ( rtDW . hbnszvowgl ) ) ;
mxSetFieldByNumber ( ssDW , 0 , 1 , rtdwData ) ; } return ssDW ; } void
mr_bolideMRU_simul_8etat_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW ;
mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW
, 0 , 0 , sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber
( ssDW , 0 , 1 ) ; mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void *
) & ( rtDW . llhn4bw3ym ) , rtdwData , 0 , 0 , sizeof ( rtDW . llhn4bw3ym ) )
; mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void * ) & ( rtDW .
jhmp3qvn5s ) , rtdwData , 0 , 1 , sizeof ( rtDW . jhmp3qvn5s ) ) ;
mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void * ) & ( rtDW .
mp3rt0g3za ) , rtdwData , 0 , 2 , sizeof ( rtDW . mp3rt0g3za ) ) ;
mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void * ) & ( rtDW .
g1eobre1no ) , rtdwData , 0 , 3 , sizeof ( rtDW . g1eobre1no ) ) ;
mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void * ) & ( rtDW .
mkzmfsijdn ) , rtdwData , 0 , 4 , sizeof ( rtDW . mkzmfsijdn ) ) ;
mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void * ) & ( rtDW .
gdaqfrous0 ) , rtdwData , 0 , 5 , sizeof ( rtDW . gdaqfrous0 ) ) ;
mr_bolideMRU_simul_8etat_restoreDataFromMxArray ( ( void * ) & ( rtDW .
hbnszvowgl ) , rtdwData , 0 , 6 , sizeof ( rtDW . hbnszvowgl ) ) ; } }
mxArray * mr_bolideMRU_simul_8etat_GetSimStateDisallowedBlocks ( ) { return (
NULL ) ; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 8 )
; ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU
( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS
, 2 ) ; ssSetNumBlocks ( rtS , 9 ) ; ssSetNumBlockIO ( rtS , 6 ) ;
ssSetNumBlockParams ( rtS , 30 ) ; } void MdlInitializeSampleTimes ( void ) {
ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 598282297U ) ;
ssSetChecksumVal ( rtS , 1 , 2989193449U ) ; ssSetChecksumVal ( rtS , 2 ,
2600091950U ) ; ssSetChecksumVal ( rtS , 3 , 1491904638U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; static struct _ssBlkInfo2 blkInfo2 ;
static struct _ssBlkInfoSLSize blkInfoSLSize ; rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; executionInfo -> gblObjects_ . numToFiles = 0 ;
executionInfo -> gblObjects_ . numFrFiles = 0 ; executionInfo -> gblObjects_
. numFrWksBlocks = 0 ; executionInfo -> gblObjects_ . numModelInputs = 0 ;
executionInfo -> gblObjects_ . numRootInportBlks = 0 ; executionInfo ->
gblObjects_ . inportDataTypeIdx = NULL ; executionInfo -> gblObjects_ .
inportDims = NULL ; executionInfo -> gblObjects_ . inportComplex = NULL ;
executionInfo -> gblObjects_ . inportInterpoFlag = NULL ; executionInfo ->
gblObjects_ . inportContinuous = NULL ; ( void ) memset ( ( char_T * ) rtS ,
0 , sizeof ( SimStruct ) ) ; ( void ) memset ( ( char_T * ) & mdlInfo , 0 ,
sizeof ( struct _ssMdlInfo ) ) ; ( void ) memset ( ( char_T * ) & blkInfo2 ,
0 , sizeof ( struct _ssBlkInfo2 ) ) ; ( void ) memset ( ( char_T * ) &
blkInfoSLSize , 0 , sizeof ( struct _ssBlkInfoSLSize ) ) ; ssSetBlkInfo2Ptr (
rtS , & blkInfo2 ) ; ssSetBlkInfoSLSizePtr ( rtS , & blkInfoSLSize ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; ssSetExecutionInfo ( rtS ,
executionInfo ) ; slsaAllocOPModelData ( rtS ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 23 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
bolideMRU_simul_8etat_InitializeDataMapInfo ( ) ;
ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ;
ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"bolideMRU_simul_8etat" ) ; ssSetPath ( rtS , "bolideMRU_simul_8etat" ) ;
ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 5.0 ) ; { static RTWLogInfo
rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = ( NULL ) ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 8 } ; static int_T rt_LoggedStateNumDimensions [
] = { 1 } ; static int_T rt_LoggedStateDimensions [ ] = { 8 } ; static
boolean_T rt_LoggedStateIsVarDims [ ] = { 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE } ; static int_T
rt_LoggedStateComplexSignals [ ] = { 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) } ; static const char_T
* rt_LoggedStateLabels [ ] = { "CSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = { "bolideMRU_simul_8etat/Bolide/Integrator" }
; static const char_T * rt_LoggedStateNames [ ] = { "" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 } ; static RTWLogDataTypeConvert
rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } } ; static int_T rt_LoggedStateIdxList [ ] = { 0 } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 1 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 1 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . mzx0gi3owr [ 0 ] ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"xFinal" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 8 ] ;
static real_T absTol [ 8 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 } ; static uint8_T absTolControl [ 8 ] = { 0U , 0U ,
0U , 0U , 0U , 0U , 0U , 0U } ; static real_T contStateJacPerturbBoundMinVec
[ 8 ] ; static real_T contStateJacPerturbBoundMaxVec [ 8 ] ; static uint8_T
zcAttributes [ 4 ] = { ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_UP ) , (
ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_UP ) } ; static ssNonContDerivSigInfo
nonContDerivSigInfo [ 4 ] = { { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
dxox3p2m4x ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
cvte4gsxdy ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
ax01y1div4 ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
dmcwhlxyjn ) , ( NULL ) } } ; { int i ; for ( i = 0 ; i < 8 ; ++ i ) {
contStateJacPerturbBoundMinVec [ i ] = 0 ; contStateJacPerturbBoundMaxVec [ i
] = rtGetInf ( ) ; } } ssSetSolverRelTol ( rtS , 0.001 ) ; ssSetStepSize (
rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , -
1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ; ssSetMaxStepSize ( rtS , 0.1 )
; ssSetSolverMaxOrder ( rtS , - 1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ;
ssSetOutputTimes ( rtS , ( NULL ) ) ; ssSetNumOutputTimes ( rtS , 0 ) ;
ssSetOutputTimesOnly ( rtS , 0 ) ; ssSetOutputTimesIndex ( rtS , 0 ) ;
ssSetZCCacheNeedsReset ( rtS , 0 ) ; ssSetDerivCacheNeedsReset ( rtS , 0 ) ;
ssSetNumNonContDerivSigInfos ( rtS , 4 ) ; ssSetNonContDerivSigInfos ( rtS ,
nonContDerivSigInfo ) ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS
, 1 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; ssSetAbsTolVector ( rtS , absTol ) ; ssSetAbsTolControlVector (
rtS , absTolControl ) ; ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverZcSignalAttrib ( rtS , zcAttributes ) ;
ssSetSolverNumZcSignals ( rtS , 4 ) ; ssSetModelZeroCrossings ( rtS ,
MdlZeroCrossings ) ; ssSetSolverConsecutiveZCsStepRelTol ( rtS ,
2.8421709430404007E-13 ) ; ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ;
ssSetSolverConsecutiveZCsError ( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic (
rtS , 1 ) ; ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 4 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 598282297U ) ; ssSetChecksumVal ( rtS , 1 ,
2989193449U ) ; ssSetChecksumVal ( rtS , 2 , 2600091950U ) ; ssSetChecksumVal
( rtS , 3 , 1491904638U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 2 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = & rtAlwaysEnabled ;
rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_bolideMRU_simul_8etat_GetSimStateDisallowedBlocks ) ;
slsaGetWorkFcnForSimTargetOP ( rtS , mr_bolideMRU_simul_8etat_GetDWork ) ;
slsaSetWorkFcnForSimTargetOP ( rtS , mr_bolideMRU_simul_8etat_SetDWork ) ;
rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if ( ssGetErrorStatus ( rtS ) )
{ return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
void MdlOutputsParameterSampleTime ( int_T tid ) { UNUSED_PARAMETER ( tid ) ;
}
