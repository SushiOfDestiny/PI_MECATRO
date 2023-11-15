#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "bolideMRU_simul_8etat_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "bolideMRU_simul_8etat.h"
#include "bolideMRU_simul_8etat_capi.h"
#include "bolideMRU_simul_8etat_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"bolideMRU_simul_8etat/Step" ) , TARGET_STRING ( "Ur" ) , 0 , 0 , 0 , 0 , 0 }
, { 1 , 0 , TARGET_STRING ( "bolideMRU_simul_8etat/Step1" ) , TARGET_STRING (
"Ul" ) , 0 , 0 , 0 , 0 , 0 } , { 2 , 1 , TARGET_STRING (
"bolideMRU_simul_8etat/Bolide/State equation" ) , TARGET_STRING ( "" ) , 0 ,
0 , 1 , 0 , 1 } , { 3 , 0 , TARGET_STRING (
"bolideMRU_simul_8etat/Bolide/State equation/is_active_c2_bolideMRU_simul_8etat"
) , TARGET_STRING ( "is_active_c2_bolideMRU_simul_8etat" ) , 0 , 1 , 0 , 0 ,
1 } , { 4 , 0 , TARGET_STRING ( "bolideMRU_simul_8etat/Bolide/Integrator" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 1 } , { 5 , 0 , TARGET_STRING (
"bolideMRU_simul_8etat/Bolide/Step2" ) , TARGET_STRING ( "edr" ) , 0 , 0 , 0
, 0 , 0 } , { 6 , 0 , TARGET_STRING ( "bolideMRU_simul_8etat/Bolide/Step3" )
, TARGET_STRING ( "edl" ) , 0 , 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 7 , TARGET_STRING ( "bolideMRU_simul_8etat/Step"
) , TARGET_STRING ( "Time" ) , 0 , 0 , 0 } , { 8 , TARGET_STRING (
"bolideMRU_simul_8etat/Step1" ) , TARGET_STRING ( "Time" ) , 0 , 0 , 0 } , {
9 , TARGET_STRING ( "bolideMRU_simul_8etat/Bolide/Step2" ) , TARGET_STRING (
"Time" ) , 0 , 0 , 0 } , { 10 , TARGET_STRING (
"bolideMRU_simul_8etat/Bolide/Step2" ) , TARGET_STRING ( "Before" ) , 0 , 0 ,
0 } , { 11 , TARGET_STRING ( "bolideMRU_simul_8etat/Bolide/Step2" ) ,
TARGET_STRING ( "After" ) , 0 , 0 , 0 } , { 12 , TARGET_STRING (
"bolideMRU_simul_8etat/Bolide/Step3" ) , TARGET_STRING ( "Time" ) , 0 , 0 , 0
} , { 13 , TARGET_STRING ( "bolideMRU_simul_8etat/Bolide/Step3" ) ,
TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , { 14 , TARGET_STRING (
"bolideMRU_simul_8etat/Bolide/Step3" ) , TARGET_STRING ( "After" ) , 0 , 0 ,
0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } } ; static int_T
rt_LoggedStateIdxList [ ] = { - 1 } ; static const rtwCAPI_Signals
rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 , ( NULL ) , (
NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters
rtModelParameters [ ] = { { 15 , TARGET_STRING ( "Ipsi" ) , 0 , 0 , 0 } , {
16 , TARGET_STRING ( "Iwy" ) , 0 , 0 , 0 } , { 17 , TARGET_STRING ( "L" ) , 0
, 0 , 0 } , { 18 , TARGET_STRING ( "M" ) , 0 , 0 , 0 } , { 19 , TARGET_STRING
( "R" ) , 0 , 0 , 0 } , { 20 , TARGET_STRING ( "Ulbar" ) , 0 , 0 , 0 } , { 21
, TARGET_STRING ( "Urbar" ) , 0 , 0 , 0 } , { 22 , TARGET_STRING ( "beta" ) ,
0 , 0 , 0 } , { 23 , TARGET_STRING ( "d" ) , 0 , 0 , 0 } , { 24 ,
TARGET_STRING ( "gamma" ) , 0 , 0 , 0 } , { 25 , TARGET_STRING ( "k" ) , 0 ,
0 , 0 } , { 26 , TARGET_STRING ( "l" ) , 0 , 0 , 0 } , { 27 , TARGET_STRING (
"mb" ) , 0 , 0 , 0 } , { 28 , TARGET_STRING ( "rho" ) , 0 , 0 , 0 } , { 29 ,
TARGET_STRING ( "statebar" ) , 0 , 2 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . dmcwhlxyjn , & rtB . ax01y1div4 ,
& rtB . cmlaobun0c [ 0 ] , & rtDW . gdaqfrous0 , & rtB . mx20xi1qvn [ 0 ] , &
rtB . cvte4gsxdy , & rtB . dxox3p2m4x , & rtP . Step_Time , & rtP .
Step1_Time , & rtP . Step2_Time , & rtP . Step2_Y0 , & rtP . Step2_YFinal , &
rtP . Step3_Time , & rtP . Step3_Y0 , & rtP . Step3_YFinal , & rtP . Ipsi , &
rtP . Iwy , & rtP . L , & rtP . M , & rtP . R , & rtP . Ulbar , & rtP . Urbar
, & rtP . beta , & rtP . d , & rtP . gamma , & rtP . k , & rtP . l , & rtP .
mb , & rtP . rho , & rtP . statebar [ 0 ] , } ; static int32_T *
rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } ,
{ "unsigned char" , "uint8_T" , 0 , 0 , sizeof ( uint8_T ) , ( uint8_T )
SS_UINT8 , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 2 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] = {
1 , 1 , 8 , 1 } ; static const real_T rtcapiStoredFloats [ ] = { 0.0 , 1.0 }
; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , (
int8_T ) 1 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 0 ]
, ( const void * ) & rtcapiStoredFloats [ 0 ] , ( int8_T ) 0 , ( uint8_T ) 0
} } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals ,
7 , rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 8 ,
rtModelParameters , 15 } , { ( NULL ) , 0 } , { rtDataTypeMap ,
rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap ,
rtDimensionArray } , "float" , { 598282297U , 2989193449U , 2600091950U ,
1491904638U } , ( NULL ) , 0 , ( boolean_T ) 0 , rt_LoggedStateIdxList } ;
const rtwCAPI_ModelMappingStaticInfo * bolideMRU_simul_8etat_GetCAPIStaticMap
( void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void bolideMRU_simul_8etat_InitializeDataMapInfo ( void ) {
rtwCAPI_SetVersion ( ( * rt_dataMapInfoPtr ) . mmi , 1 ) ;
rtwCAPI_SetStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ;
rtwCAPI_SetLoggingStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetDataAddressMap ( ( * rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ;
rtwCAPI_SetVarDimsAddressMap ( ( * rt_dataMapInfoPtr ) . mmi ,
rtVarDimsAddrMap ) ; rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr )
. mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi
, ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi ,
0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void bolideMRU_simul_8etat_host_InitializeDataMapInfo (
bolideMRU_simul_8etat_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap ->
mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
