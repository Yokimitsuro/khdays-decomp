/* func_ov000_0204de30 -- Scene 1 (boot/logo) third fade state, ov000.
 * Same fade shape as func_ov000_0204dc38, for the next logo/screen pair (players
 * heap[0x66]/[0x5a]); when the fade finishes it advances to func_ov000_0204df98.
 * On frame 0 it additionally streams the region-specific secondary resource
 * (heap[2], set up by func_ov000_0204d72c) into BG3 character VRAM: load the file
 * (func_0201ef9c), resolve its data pointer (func_020119d4), flush the CPU cache
 * over it (DC_FlushRange), copy it to sub-BG3 char base 0x7000
 * (GX_LoadBG1Char), then free the transient load handle. */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_ov000_0204d354(void);
extern void  func_02024b04(int id, void *player, int, int);
extern void *func_0201ef9c(unsigned int addr, int mode);
extern void  func_020119d4(void *handle, void **out);
extern void  DC_FlushRange(void *addr, int len);
extern void  GX_LoadBG1Char(void *src, int offset, int size);
extern void  NNSi_FndFreeFromDefaultHeap(void *handle);
extern void  func_0201e374(int brightness);
extern void  func_0201e3cc(int brightness);
extern void  func_ov000_0204df98(void);

StateFn func_ov000_0204de30(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    func_ov000_0204d354();
    if (h[0] == 0) {
        func_02024b04(1, (void *)h[0x66], 0, *(int *)(h[0x66] + 8));
        func_02024b04(5, (void *)h[0x5a], 0, *(int *)(h[0x5a] + 8));
        if (h[2] != 0) {
            void *res;
            void *handle = func_0201ef9c(((h[2] + 0x8000 & 0xfffffc) << 7) | 0x80000000, 0xe);
            func_020119d4(handle, &res);
            DC_FlushRange(*(void **)((char *)res + 0x14), *(int *)((char *)res + 0x10));
            GX_LoadBG1Char(*(void **)((char *)res + 0x14), 0x7000, *(int *)((char *)res + 0x10));
            if (handle != 0) {
                NNSi_FndFreeFromDefaultHeap(handle);
            }
        }
    }
    if (h[0] < 0x20) {
        func_0201e374(0x10 - h[0] / 2);
        func_0201e3cc(0x10 - h[0] / 2);
    } else if (h[0] <= 0x3a) {
        func_0201e374(0);
        func_0201e3cc(0);
    } else if (h[0] <= 0x5a) {
        func_0201e374((h[0] - 0x3a) / 2);
        func_0201e3cc((h[0] - 0x3a) / 2);
    } else {
        func_0201e374(0x10);
        func_0201e3cc(0x10);
        h[0] = 0;
        return (StateFn)func_ov000_0204df98;
    }
    h[0]++;
    return 0;
}
