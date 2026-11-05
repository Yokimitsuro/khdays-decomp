/* Ov000_LogoFadeState3 -- Scene 1 (boot/logo) third fade state, ov000.
 * Same fade shape as Ov000_LogoFadeState, for the next logo/screen pair (players
 * heap[0x66]/[0x5a]); when the fade finishes it advances to Ov000_HandoffState.
 * On frame 0 it additionally streams the region-specific secondary resource
 * (heap[2], set up by Ov000_PreloadLogoResources) into BG3 character VRAM: load the file
 * (Archive_LoadFile), resolve its data pointer (GetResourceSubBlock_CHAR2), flush the CPU cache
 * over it (DC_FlushRange), copy it to sub-BG3 char base 0x7000
 * (GX_LoadBG1Char), then free the transient load handle. */

#include "game/engine.h"
#include "game/archive.h"

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  Ov000_FadeStateHookNoOp(void);
extern void *Archive_LoadFile(unsigned int addr, int mode);
extern void  GetResourceSubBlock_CHAR2(void *handle, void **out);
extern void  DC_FlushRange(void *addr, int len);
extern void  GX_LoadBG1Char(void *src, int offset, int size);
extern void  NNSi_FndFreeFromDefaultHeap(void *handle);
extern void  Ov000_HandoffState(void);

StateFn Ov000_LogoFadeState3(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    Ov000_FadeStateHookNoOp();
    if (h[0] == 0) {
        Gfx_EnqueueTableCmdAtC(1, (void *)h[0x66], 0, *(int *)(h[0x66] + 8));
        Gfx_EnqueueTableCmdAtC(5, (void *)h[0x5a], 0, *(int *)(h[0x5a] + 8));
        if (h[2] != 0) {
            void *res;
            void *handle = Archive_LoadFile(ARCHIVE_HANDLE(h[2], 0), 0xe);
            GetResourceSubBlock_CHAR2(handle, &res);
            DC_FlushRange(*(void **)((char *)res + 0x14), *(int *)((char *)res + 0x10));
            GX_LoadBG1Char(*(void **)((char *)res + 0x14), 0x7000, *(int *)((char *)res + 0x10));
            if (handle != 0) {
                NNSi_FndFreeFromDefaultHeap(handle);
            }
        }
    }
    if (h[0] < 0x20) {
        SetMasterBrightnessMain(0x10 - h[0] / 2);
        SetMasterBrightnessSub(0x10 - h[0] / 2);
    } else if (h[0] <= 0x3a) {
        SetMasterBrightnessMain(0);
        SetMasterBrightnessSub(0);
    } else if (h[0] <= 0x5a) {
        SetMasterBrightnessMain((h[0] - 0x3a) / 2);
        SetMasterBrightnessSub((h[0] - 0x3a) / 2);
    } else {
        SetMasterBrightnessMain(0x10);
        SetMasterBrightnessSub(0x10);
        h[0] = 0;
        return (StateFn)Ov000_HandoffState;
    }
    h[0]++;
    return 0;
}
