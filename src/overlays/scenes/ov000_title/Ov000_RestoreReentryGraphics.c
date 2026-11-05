/* Ov000_RestoreReentryGraphics -- Scene 1 (boot/logo) re-entry graphics restore, ov000.
 * Called by Ov000_FreshBootGfxSetup on a non-fresh entry (arg != 0). Re-arms the two
 * animation players (ids 1 and 5) from their saved heap slots, then re-streams the
 * region-specific secondary resource (heap[2]) into sub-BG3 character VRAM at 0x9000
 * (load Archive_LoadFile, resolve GetResourceSubBlock_CHAR2, DC_FlushRange, GX_LoadBG0Char, free).
 * No-op tail when heap[2] is absent. */

#include "game/engine.h"
#include "game/archive.h"

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  Bg_LoadPaletteForScreen(int, void *, void *, int, int);
extern void *Archive_LoadFile(unsigned int addr, int mode);
extern void  GetResourceSubBlock_CHAR2(void *handle, void **out);
extern void  DC_FlushRange(void *addr, int len);
extern void  GXS_LoadBG1Char(void *src, int offset, int size);
extern void  NNSi_FndFreeFromDefaultHeap(void *handle);

void Ov000_RestoreReentryGraphics(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    Bg_LoadPaletteForScreen(1, (void *)h[0x6b], (void *)h[0x69], 0, *(int *)(h[0x6b] + 8));
    Gfx_EnqueueTableCmdAt14(1, (void *)h[0x6a], 0, *(int *)(h[0x6a] + 0x10));
    Gfx_EnqueueTableCmdAtC(1, (void *)h[0x69], 0, *(int *)(h[0x69] + 8));
    Bg_LoadPaletteForScreen(5, (void *)h[0x5f], (void *)h[0x5d], 0, *(int *)(h[0x5f] + 8));
    Gfx_EnqueueTableCmdAt14(5, (void *)h[0x5e], 0, *(int *)(h[0x5e] + 0x10));
    Gfx_EnqueueTableCmdAtC(5, (void *)h[0x5d], 0, *(int *)(h[0x5d] + 8));
    if (h[2] != 0) {
        void *res;
        void *handle = Archive_LoadFile(ARCHIVE_HANDLE(h[2], 2), 0xe);
        GetResourceSubBlock_CHAR2(handle, &res);
        DC_FlushRange(*(void **)((char *)res + 0x14), *(int *)((char *)res + 0x10));
        GXS_LoadBG1Char(*(void **)((char *)res + 0x14), 0x9000, *(int *)((char *)res + 0x10));
        if (handle != 0) {
            NNSi_FndFreeFromDefaultHeap(handle);
        }
    }
}
