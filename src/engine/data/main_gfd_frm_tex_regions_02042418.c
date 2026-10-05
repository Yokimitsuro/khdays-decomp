/* main .data, 0x02042418-0x02042490: NitroSystem's frame texture VRAM manager's five regions
 * (NNSGfdFrmTexRegionState, gfd_FrameTexVramMan.c). head and tail start unset (-1); bHalfSize
 * marks the two half-size regions, index numbers them and baseAddress is each one's start in
 * texture VRAM. NNSi_GfdSetTexNrmSearchArray and the 4x4 search array (data_020423fc) point at
 * them; NNS_GfdResetFrmTexVramState, NNS_GfdAllocFrmTexVram, NNS_GfdGetFrmTexVramState and
 * NNS_GfdSetFrmTexVramState walk them.
 */

#include "nitro/types.h"
#include "nnsys/gfd.h"

NNSGfdFrmTexRegionState gGfdFrmTexRegions[5] = {
    { 0xffffffff, 0xffffffff, FALSE, FALSE, 0, 0xffff, 0x00000 },
    { 0xffffffff, 0xffffffff, FALSE, TRUE,  1, 0xffff, 0x20000 },
    { 0xffffffff, 0xffffffff, FALSE, TRUE,  2, 0xffff, 0x30000 },
    { 0xffffffff, 0xffffffff, FALSE, FALSE, 3, 0xffff, 0x40000 },
    { 0xffffffff, 0xffffffff, FALSE, FALSE, 4, 0xffff, 0x60000 },
};
