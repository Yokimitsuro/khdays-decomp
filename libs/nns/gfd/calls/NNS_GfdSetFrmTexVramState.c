

#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/gfd.h"

extern NNSGfdFrmTexRegionState gGfdFrmTexRegions[5 ];

/* NNS_GfdSetFrmTexVramState -- NitroSystem gfd_FrameTexVramMan.c: NNS_GfdSetFrmTexVramState. */
void NNS_GfdSetFrmTexVramState (const NNSGfdFrmTexVramState * pState)
{
    int i;

    for (i = 0; i < NNS_GFD_NUM_TEX_VRAM_REGION; i++)
    {
        gGfdFrmTexRegions[i].head = pState->address[i * 2 + 0];
        gGfdFrmTexRegions[i].tail = pState->address[i * 2 + 1];
    }
}
