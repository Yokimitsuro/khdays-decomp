/* func_ov022_02083bd8 -- drop the multiplayer key-sharing session.
 *
 * If a key-sharing handle is parked at data_ov022_020b2e60[2], end it, clear the slot and the
 * "sharing active" byte, and unload the wireless overlay.  Always reports 0.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol -- the stock NitroSDK
 * FS_EXTERN_OVERLAY / FS_OVERLAY_ID idiom, which dsd emits into arm9.lcf as
 * `OVERLAY_106_ID = 106;`.  That is the whole reason the ROM loads 0x6a from its literal pool
 * instead of `movs r1,#0x6a`: it is not a constant in the source, it is `&OVERLAY_106_ID`.
 * Written as a plain `0x6a` the function is 4 bytes short -- the pool word disappears.
 */
typedef unsigned int u32;
typedef u32 FSOverlayID;

/* FS_EXTERN_OVERLAY(ov106) -- dsd names the absolute symbol OVERLAY_106_ID. */
extern u32 OVERLAY_106_ID[1];
#define FS_OVERLAY_ID_ov106 ((FSOverlayID)(u32) & (OVERLAY_106_ID))

extern void WM_EndKeySharing_0x02023ad0(int handle);
extern void func_0201e4a8(int target, FSOverlayID id);   /* unload overlay */
extern int data_ov022_020b2e60[];
extern unsigned char data_0204be04;

int func_ov022_02083bd8(void) {
    if (data_ov022_020b2e60[2] != 0) {
        WM_EndKeySharing_0x02023ad0(data_ov022_020b2e60[2]);
        data_ov022_020b2e60[2] = 0;
        data_0204be04 = 0;
        func_0201e4a8(0, FS_OVERLAY_ID_ov106);
    }
    return 0;
}
