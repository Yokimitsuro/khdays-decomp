/* func_ov000_0204f47c -- title scene: fade out, then start the movie player.
 *
 * heap[0] is a frame counter.  For the first 0x11 frames it drives the master brightness of
 * both screens down (-frame), then, once func_02034014 reports the fade is settled, it runs
 * the title teardown (func_ov000_0204dbb4), publishes the scene block in data_ov000_0205ac20,
 * loads ov012 and instantiates the movie-player class, parking the object at heap+0x5078.
 * Control then moves to func_ov000_0204f404, which waits for the movie to end.  Until either
 * of those happens it bumps the counter and reports 0 (stay).
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd
 * emits `OVERLAY_12_ID = 12;` into arm9.lcf.  Spelled as a plain 12 the pool word disappears
 * and the function is 4 bytes short.
 */
typedef unsigned int u32;
typedef u32 FSOverlayID;
typedef void *StateFn;

extern u32 OVERLAY_12_ID[1];
#define FS_OVERLAY_ID_ov012 ((FSOverlayID)(u32) & (OVERLAY_12_ID))

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202aa9c(void *p);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern int  func_02034014(int arg);
extern void func_ov000_0204dbb4(void);
extern void func_0201e470(int target, FSOverlayID id);
extern void *func_02023930(void *classDesc, int arg);
extern void *data_ov000_0205ac20;
extern int  data_ov012_0205c2bc;
extern void func_ov000_0204f404(void);

StateFn func_ov000_0204f47c(void) {
    int *heap = (int *)NNSi_FndGetCurrentRootHeap();

    func_0202aa9c((char *)heap + 0xc);
    if (heap[0] <= 0x10) {
        func_0201e374(-heap[0]);
        func_0201e3cc(-heap[0]);
    } else if (func_02034014(0) == 0) {
        func_ov000_0204dbb4();
        data_ov000_0205ac20 = heap;
        func_0201e470(0, FS_OVERLAY_ID_ov012);
        *(void **)((char *)heap + 0x5078) = func_02023930((void *)&data_ov012_0205c2bc, 1);
        return (StateFn)func_ov000_0204f404;
    }
    heap[0] = heap[0] + 1;
    return 0;
}
