#ifndef RTW_HEADER_bolideMRU_simul_8etat_cap_host_h__
#define RTW_HEADER_bolideMRU_simul_8etat_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap_simtarget.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
bolideMRU_simul_8etat_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void bolideMRU_simul_8etat_host_InitializeDataMapInfo (
bolideMRU_simul_8etat_host_DataMapInfo_T * dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
