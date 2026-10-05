/* NNS_GfdAllocFrmTexVram (NitroSystem gfd_FrameTexVramMan.c): take szByte of texture VRAM from the
 * frame manager's regions, in the normal or the 4x4-compressed search order, and return its
 * texture key (NNS_GFD_ALLOC_ERROR_TEXKEY when no region has room). */


#include "nitro/types.h"
#include "nnsys/gfd.h"

extern NNSGfdFrmTexRegionState *data_020423fc[2];
extern NNSGfdFrmTexRegionState *data_02042404[5];
extern NNSGfdFrmTexRegionState gGfdFrmTexRegions[5];

static inline u32 NNSi_GfdGetTexKeyRoundupSize(u32 size)
{
    if (size == 0) {
        return NNS_GFD_TEXSIZE_MIN;
    }
    return (size + 0xf) & ~0xf;
}

static inline NNSGfdTexKey NNS_GfdMakeTexKey(u32 addr, u32 size,
                                              BOOL b4x4Comp)
{
    return ((size >> 4) << 16) | (0xffff & (addr >> 3)) | b4x4Comp << 31;
}

static inline u32 GetReagionCapacity_(const NNSGfdFrmTexRegionState *pRegion)
{
    (void)0;
    (void)0;
    return (u32)(pRegion->tail - pRegion->head);
}

static inline u32 AllocFromReagionHead_(NNSGfdFrmTexRegionState *pRegion,
                                        u32 szByte)
{
    (void)0;
    (void)0;
    (void)0;
    {
    const u32 result = pRegion->head;
    pRegion->head += szByte;
    return result;
    }
}

static inline u32 AllocFromReagionTail_(NNSGfdFrmTexRegionState *pRegion,
                                        u32 szByte)
{
    (void)0;
    (void)0;
    (void)0;
    {
    pRegion->tail -= szByte;
    return pRegion->tail;
    }
}

static inline NNSGfdFrmTexRegionState *Get4x4IdxRegion_(const NNSGfdFrmTexRegionState *pRegion)
{
    (void)0;
    switch (pRegion->index) {
    case 0:
        return &gGfdFrmTexRegions[1];
    case 3:
        return &gGfdFrmTexRegions[2];
    default:
        (void)0;
        break;
    }
    return NULL;
}

static inline BOOL DoAlloc4x4_(u32 szByte, u32 *addr)
{
    (void)0;
    (void)0;
    {
        int i;
        NNSGfdFrmTexRegionState *pRegion = NULL;
        NNSGfdFrmTexRegionState *pPltRegion = NULL;

        for (i = 0; i < 2; i++) {
            pRegion = data_020423fc[i];
            if (pRegion->bActive &&
                GetReagionCapacity_(pRegion) >= szByte) {
                switch (pRegion->index) {
                case 0:
                    pPltRegion = &gGfdFrmTexRegions[1];
                    break;
                case 3:
                    pPltRegion = &gGfdFrmTexRegions[2];
                    break;
                default:
                    pPltRegion = NULL;
                    break;
                }
                if (pPltRegion->bActive &&
                    GetReagionCapacity_(pPltRegion) >= szByte / 2) {
                    *addr = AllocFromReagionHead_(pRegion, szByte);
                    (void)AllocFromReagionHead_(pPltRegion, szByte / 2);
                    *addr += pRegion->baseAddress;
                    return TRUE;
                }
            }
        }
        (void)0;
        return FALSE;
    }
}

static inline BOOL DoAllocNrm_(u32 szByte, u32 *addr)
{
    (void)0;
    (void)0;
    {
        int i;
        NNSGfdFrmTexRegionState *pRegion = NULL;

        for (i = 0; i < 5; i++) {
            pRegion = data_02042404[i];
            if (pRegion->bActive) {
                if (GetReagionCapacity_(pRegion) >= szByte) {
                    *addr = AllocFromReagionTail_(pRegion, szByte);
                    *addr += pRegion->baseAddress;
                    return TRUE;
                }
            }
        }
        (void)0;
        return FALSE;
    }
}

NNSGfdTexKey NNS_GfdAllocFrmTexVram(u32 szByte, BOOL is4x4comp, u32 opt)
{
#pragma unused(opt)
    u32 addr;
    BOOL result;

    (void)0;
    {
        szByte = NNSi_GfdGetTexKeyRoundupSize(szByte);
        if (szByte >= NNS_GFD_TEXSIZE_MAX) {
            (void)0;
            return NNS_GFD_ALLOC_ERROR_TEXKEY;
        }
        (void)0;
    }

    if (is4x4comp) {
        result = DoAlloc4x4_(szByte, &addr);
    } else {
        result = DoAllocNrm_(szByte, &addr);
    }

    if (result) {
        return NNS_GfdMakeTexKey(addr, szByte, is4x4comp);
    } else {
        (void)0;
        return NNS_GFD_ALLOC_ERROR_TEXKEY;
    }
}
