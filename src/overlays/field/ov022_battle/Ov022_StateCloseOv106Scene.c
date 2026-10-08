/* Ov022_StateCloseOv106Scene -- close the ov106 scene Ov022_LoadSceneResources opened.
 *
 * If its object is still up (data_ov022_020b2e60[2]), destroy it, clear the slot and the byte
 * that says the scene runs (data_0204be04), and unload ov106.  Always reports 0.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol -- the stock NitroSDK
 * FS_EXTERN_OVERLAY / FS_OVERLAY_ID idiom, which dsd emits into arm9.lcf as
 * `OVERLAY_106_ID = 106;`.  That is the whole reason the ROM loads 0x6a from its literal pool
 * instead of `movs r1,#0x6a`: it is not a constant in the source, it is `&OVERLAY_106_ID`.
 * Written as a plain `0x6a` the function is 4 bytes short -- the pool word disappears.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef u32 FSOverlayID;

/* FS_EXTERN_OVERLAY(ov106) -- dsd names the absolute symbol OVERLAY_106_ID. */
extern u32 OVERLAY_106_ID[1];
#define FS_OVERLAY_ID_ov106 ((FSOverlayID)(u32) & (OVERLAY_106_ID))

extern void VeneerTo_Obj_Destroy(int handle);
extern int data_ov022_020b2e60[];
extern unsigned char data_0204be04;

int Ov022_StateCloseOv106Scene(void) {
    if (data_ov022_020b2e60[2] != 0) {
        VeneerTo_Obj_Destroy(data_ov022_020b2e60[2]);
        data_ov022_020b2e60[2] = 0;
        data_0204be04 = 0;
        UnloadOverlaySync(0, FS_OVERLAY_ID_ov106);
    }
    return 0;
}
