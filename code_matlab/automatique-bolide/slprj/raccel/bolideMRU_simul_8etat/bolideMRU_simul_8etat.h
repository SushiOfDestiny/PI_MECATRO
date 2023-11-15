#ifndef RTW_HEADER_bolideMRU_simul_8etat_h_
#define RTW_HEADER_bolideMRU_simul_8etat_h_
#ifndef bolideMRU_simul_8etat_COMMON_INCLUDES_
#define bolideMRU_simul_8etat_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "bolideMRU_simul_8etat_types.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME bolideMRU_simul_8etat
#define NSAMPLE_TIMES (2) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (6) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (8)   
#elif NCSTATES != 8
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T mx20xi1qvn [ 8 ] ; real_T dmcwhlxyjn ; real_T
ax01y1div4 ; real_T cvte4gsxdy ; real_T dxox3p2m4x ; real_T cmlaobun0c [ 8 ]
; } B ; typedef struct { int32_T llhn4bw3ym ; int_T jhmp3qvn5s ; int_T
mp3rt0g3za ; int_T g1eobre1no ; int_T mkzmfsijdn ; uint8_T gdaqfrous0 ;
boolean_T hbnszvowgl ; } DW ; typedef struct { real_T mzx0gi3owr [ 8 ] ; } X
; typedef struct { real_T mzx0gi3owr [ 8 ] ; } XDot ; typedef struct {
boolean_T mzx0gi3owr [ 8 ] ; } XDis ; typedef struct { real_T mzx0gi3owr [ 8
] ; } CStateAbsTol ; typedef struct { real_T mzx0gi3owr [ 8 ] ; } CXPtMin ;
typedef struct { real_T mzx0gi3owr [ 8 ] ; } CXPtMax ; typedef struct {
real_T bztjzebkiv ; real_T odck5cytne ; real_T dj0df2pbfy ; real_T hijvu4qzbz
; } ZCV ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ;
struct P_ { real_T Ipsi ; real_T Iwy ; real_T L ; real_T M ; real_T R ;
real_T Ulbar ; real_T Urbar ; real_T beta ; real_T d ; real_T gamma ; real_T
k ; real_T l ; real_T mb ; real_T rho ; real_T statebar [ 8 ] ; real_T
Step_Time ; real_T Step1_Time ; real_T Step2_Time ; real_T Step2_Y0 ; real_T
Step2_YFinal ; real_T Step3_Time ; real_T Step3_Y0 ; real_T Step3_YFinal ; }
; extern const char_T * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X
rtX ; extern DW rtDW ; extern P rtP ; extern mxArray *
mr_bolideMRU_simul_8etat_GetDWork ( ) ; extern void
mr_bolideMRU_simul_8etat_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_bolideMRU_simul_8etat_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * bolideMRU_simul_8etat_GetCAPIStaticMap (
void ) ; extern SimStruct * const rtS ; extern DataMapInfo *
rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ;
void MdlOutputs ( int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T
tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
