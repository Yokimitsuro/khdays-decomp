/* Ov000_FinishMoviePlayback_2 -- title scene: wait for the movie to end, then tear the player down.
 *
 * Polls the ov012 movie-player scene (Ov012_IsGlobalFlag3Set); while it is still running this
 * returns 0 and the state machine stays put.  Once it reports done: black out both screens,
 * destroy the object parked at heap+0x5078, unload ov012, mark the movie slot at
 * heap+0x5074 as empty (-1), re-run the one-time display init, put engine A back on the top
 * screen (POWCNT1 bit 15) and hand control to the title graphics setup with mode 2.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol -- the stock NitroSDK
 * FS_EXTERN_OVERLAY / FS_OVERLAY_ID idiom, which dsd emits into arm9.lcf as
 * `OVERLAY_12_ID = 12;`.  That is why the ROM loads 12 from its literal pool instead of using
 * an ARM immediate: written as a plain `12` the function is 4 bytes short.  Same idiom as
 * Ov001_CreateMainAndSubHeaps.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef u32 FSOverlayID;
typedef void *StateFn;

/* FS_EXTERN_OVERLAY(ov012) -- dsd names the absolute symbol OVERLAY_12_ID. */
extern u32 OVERLAY_12_ID[1];
#define FS_OVERLAY_ID_ov012 ((FSOverlayID)(u32) & (OVERLAY_12_ID))

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int  Ov012_IsGlobalFlag3Set(void);
extern void VeneerTo_Obj_Destroy(int handle);
extern StateFn Ov000_FreshBootGfxSetup(int arg);

StateFn Ov000_FinishMoviePlayback_2(void) {
    char *heap = (char *)NNSi_FndGetCurrentRootHeap();
    if (Ov012_IsGlobalFlag3Set() == 0) {
        return 0;
    }
    SetMasterBrightnessMain(-0x10);
    SetMasterBrightnessSub(-0x10);
    VeneerTo_Obj_Destroy(*(int *)(heap + 0x5078));
    UnloadOverlaySync(0, FS_OVERLAY_ID_ov012);
    *(int *)(heap + 0x5074) = -1;
    Gfx_Reset2DEngines();
    *(volatile unsigned short *)0x04000304 |= 0x8000;   /* REG_POWCNT1: engine A -> top LCD */
    return Ov000_FreshBootGfxSetup(2);
}
