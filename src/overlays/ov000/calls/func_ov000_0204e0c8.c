/* func_ov000_0204e0c8 -- Scene 1 (boot/logo) re-entry graphics restore, ov000.
 * Called by func_ov000_0204d7c8 on a non-fresh entry (arg != 0). Re-arms the two
 * animation players (ids 1 and 5) from their saved heap slots, then re-streams the
 * region-specific secondary resource (heap[2]) into sub-BG3 character VRAM at 0x9000
 * (load func_0201ef9c, resolve func_020119d4, DC_FlushRange, GXS_LoadBG3Char, free).
 * No-op tail when heap[2] is absent. */

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_02024a6c(int, void *, void *, int, int);
extern void  func_02024ae0(int, void *, int, int);
extern void  func_02024b04(int, void *, int, int);
extern void *func_0201ef9c(unsigned int addr, int mode);
extern void  func_020119d4(void *handle, void **out);
extern void  DC_FlushRange(void *addr, int len);
extern void  GXS_LoadBG3Char_0x0200782c(void *src, int offset, int size);
extern void  NNSi_FndFreeFromDefaultHeap(void *handle);

void func_ov000_0204e0c8(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    func_02024a6c(1, (void *)h[0x6b], (void *)h[0x69], 0, *(int *)(h[0x6b] + 8));
    func_02024ae0(1, (void *)h[0x6a], 0, *(int *)(h[0x6a] + 0x10));
    func_02024b04(1, (void *)h[0x69], 0, *(int *)(h[0x69] + 8));
    func_02024a6c(5, (void *)h[0x5f], (void *)h[0x5d], 0, *(int *)(h[0x5f] + 8));
    func_02024ae0(5, (void *)h[0x5e], 0, *(int *)(h[0x5e] + 0x10));
    func_02024b04(5, (void *)h[0x5d], 0, *(int *)(h[0x5d] + 8));
    if (h[2] != 0) {
        void *res;
        void *handle = func_0201ef9c(((h[2] + 0x8000 & 0xfffffc) << 7) | 0x80000002, 0xe);
        func_020119d4(handle, &res);
        DC_FlushRange(*(void **)((char *)res + 0x14), *(int *)((char *)res + 0x10));
        GXS_LoadBG3Char_0x0200782c(*(void **)((char *)res + 0x14), 0x9000, *(int *)((char *)res + 0x10));
        if (handle != 0) {
            NNSi_FndFreeFromDefaultHeap(handle);
        }
    }
}
