/* NNSi_GfdSetTexNrmSearchArray (NitroSystem gfd_FrameTexVramMan.c): set the order in which the
 * frame texture VRAM manager searches its five regions for a normal texture. Each argument is
 * a region's index (NNS_GfdInitFrmTexVramManager passes 4, 3, 2, 0, 1 or 4, 3, 0, 2, 1); the
 * fifth arrives on the stack. The normal search array is the five words after the two of the
 * 4x4-compressed one. */

#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct {
    NNSGfdFrmTexRegionState *p4x4[2];    /* +0: the 4x4-compressed textures' order */
    NNSGfdFrmTexRegionState *pNrm[5];    /* +8: the normal textures' order */
} FrmTexSearchArrays;

extern NNSGfdFrmTexRegionState gGfdFrmTexRegions[];
extern FrmTexSearchArrays data_020423fc;

void NNSi_GfdSetTexNrmSearchArray(int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th) {
    data_020423fc.pNrm[0] = &gGfdFrmTexRegions[idx1st];
    data_020423fc.pNrm[1] = &gGfdFrmTexRegions[idx2nd];
    data_020423fc.pNrm[2] = &gGfdFrmTexRegions[idx3rd];
    data_020423fc.pNrm[3] = &gGfdFrmTexRegions[idx4th];
    data_020423fc.pNrm[4] = &gGfdFrmTexRegions[idx5th];
}
