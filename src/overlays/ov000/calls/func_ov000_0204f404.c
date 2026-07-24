/* func_ov000_0204f404 -- title scene: wait for the movie to end, then tear the player down.
 *
 * Polls the ov012 movie-player scene (func_ov012_0205b920); while it is still running this
 * returns 0 and the state machine stays put.  Once it reports done: black out both screens,
 * release the key-sharing handle parked at heap+0x5078, unload ov012, mark the movie slot at
 * heap+0x5074 as empty (-1), re-run the one-time display init, put engine A back on the top
 * screen (POWCNT1 bit 15) and hand control to the title graphics setup with mode 2.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol -- the stock NitroSDK
 * FS_EXTERN_OVERLAY / FS_OVERLAY_ID idiom, which dsd emits into arm9.lcf as
 * `OVERLAY_12_ID = 12;`.  That is why the ROM loads 12 from its literal pool instead of using
 * an ARM immediate: written as a plain `12` the function is 4 bytes short.  Same idiom as
 * func_ov001_0204ce40.
 */
typedef unsigned int u32;
typedef u32 FSOverlayID;
typedef void *StateFn;

/* FS_EXTERN_OVERLAY(ov012) -- dsd names the absolute symbol OVERLAY_12_ID. */
extern u32 OVERLAY_12_ID[1];
#define FS_OVERLAY_ID_ov012 ((FSOverlayID)(u32) & (OVERLAY_12_ID))

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int  func_ov012_0205b920(void);
extern void func_0201e374(int brightness);   /* master brightness, main engine */
extern void func_0201e3cc(int brightness);   /* master brightness, sub engine  */
extern void WM_EndKeySharing_0x02023ad0(int handle);
extern void func_0201e4a8(int target, FSOverlayID id);   /* unload overlay */
extern void func_0201e1d0(void);
extern StateFn func_ov000_0204d7c8(int arg);

StateFn func_ov000_0204f404(void) {
    char *heap = (char *)NNSi_FndGetCurrentRootHeap();
    if (func_ov012_0205b920() == 0) {
        return 0;
    }
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    WM_EndKeySharing_0x02023ad0(*(int *)(heap + 0x5078));
    func_0201e4a8(0, FS_OVERLAY_ID_ov012);
    *(int *)(heap + 0x5074) = -1;
    func_0201e1d0();
    *(volatile unsigned short *)0x04000304 |= 0x8000;   /* REG_POWCNT1: engine A -> top LCD */
    return func_ov000_0204d7c8(2);
}
