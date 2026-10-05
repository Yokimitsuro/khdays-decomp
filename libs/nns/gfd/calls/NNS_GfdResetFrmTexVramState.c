

#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/gfd.h"

extern NNSGfdFrmTexVramMnager data_02047360;
extern NNSGfdFrmTexRegionState gGfdFrmTexRegions[5 ];
static inline void ResetRegionNormal_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 ;
}
static inline void ResetRegionHalf_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 / 2;
}

/* NNS_GfdResetFrmTexVramState -- NitroSystem gfd_FrameTexVramMan.c: NNS_GfdResetFrmTexVramState. */
void NNS_GfdResetFrmTexVramState (void)
{
    int i;
    u16 numSlot = data_02047360.numSlot;

    const numRegion = (numSlot > 1) ? numSlot + 1 : numSlot + 0;

    for (i = 0; i < NNS_GFD_NUM_TEX_VRAM_REGION; i++) {
        if ( i < numRegion ) {
            gGfdFrmTexRegions[i].bActive = TRUE;
        } else {
            gGfdFrmTexRegions[i].bActive = FALSE;
        }

        if ( gGfdFrmTexRegions[i].bHalfSize ) {
            ResetRegionHalf_(&gGfdFrmTexRegions[i]);
        } else {
            ResetRegionNormal_(&gGfdFrmTexRegions[i]);
        }
    }
}
