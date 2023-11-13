#include "bolideMRU_simul_8etat_capi_host.h"
static bolideMRU_simul_8etat_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        bolideMRU_simul_8etat_host_InitializeDataMapInfo(&(root), "bolideMRU_simul_8etat");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction(){return(getRootMappingInfo());}
