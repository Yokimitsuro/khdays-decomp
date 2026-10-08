/* Ov000_BootRunSelector -- boot: hand control to the anti-tamper selector, or to the fallback.
 *
 * Sets the display and mode configs, runs the boot-time setup, and (only when the boot request
 * at ctx+0x4c40 is pending) asks GameState_GetField for the selector value.  0x191 means "run the
 * protected path": clear the boot-mode state, load ov028 (DS Protect), and if all three of its
 * predicates pass, seed the elapsed field with 10000 and enter Ov000_RequestScene11 (the opening
 * movie); either way ov028 is unloaded again.  The predicates are: always true; not a flashcart
 * (the ROM pages below 0x8000 must mirror 0x8000); not an emulator (judged by the MAC address).
 * When one fails no scene is requested at all, and the game stays on a black screen with no
 * error.  Anything else falls back to Scene_RequestPending(SCENE_CALENDAR, selector), the day title card.
 * Always reports -2.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd emits
 * `OVERLAY_28_ID = 28;` into arm9.lcf, which is why 0x1c comes from the literal pool and is
 * kept in a callee-saved register across the load and the unload.
 */

#include "nitro/types.h"
#include "game/engine.h"

#include "game/scene.h"
typedef u32 FSOverlayID;

extern u32 OVERLAY_28_ID[1];
#define FS_OVERLAY_ID_ov028 ((FSOverlayID)(u32) & (OVERLAY_28_ID))

typedef struct Ov000DisplayConfig {
    int enabled;
    int visible;
    int reserved0;
    int reserved1;
} Ov000DisplayConfig;

typedef struct Ov000ModeConfig {
    int enabledMode;
    int reserved;
} Ov000ModeConfig;

typedef struct BootModeState {
    u8 flags;
    u8 state;
    u16 elapsed;
    u16 resetWord;
} BootModeState;

typedef struct Ov000BootContext {
    u8 pad_0000[0x4c40];
    int bootRequestPending;
} Ov000BootContext;

extern Ov000BootContext *NNSi_FndGetCurrentRootHeap(void);
extern void Ov000_ResetPartyMemberAndLayout(int a, int b);
extern int  Ov028_DSProt_DetectNotDummy(int a);
extern int  Ov028_DSProt_DetectNotFlashcart(int a);
extern int  Ov028_DSProt_DetectNotEmulator(int a);
extern void Ov000_RequestScene11(void);
extern BootModeState data_0204c240;

int Ov000_BootRunSelector(void) {
    Ov000BootContext *ctx = NNSi_FndGetCurrentRootHeap();
    Ov000ModeConfig mode;
    Ov000DisplayConfig display;
    int selector = 0;

    display.enabled = 1;
    display.visible = 1;
    Session_StoreSetup(&display);
    mode.enabledMode = 1;
    mode.reserved = 0;
    CopyToSlotTable8(&mode, 0);
    EnsureServiceInstance();
    Ov000_ResetPartyMemberAndLayout(0, 0);
    if (ctx->bootRequestPending != 0) {
        selector = GameState_GetField(0, 9);
    }
    if (selector == 0x191) {
        data_0204c240.resetWord = 0;
        data_0204c240.state = 0;
        LoadOverlaySync(0, FS_OVERLAY_ID_ov028);
        if (Ov028_DSProt_DetectNotDummy(0) != 0 && Ov028_DSProt_DetectNotFlashcart(0) != 0 &&
            Ov028_DSProt_DetectNotEmulator(0) != 0) {
            data_0204c240.elapsed = 0x2710;
            Ov000_RequestScene11();
        }
        UnloadOverlaySync(0, FS_OVERLAY_ID_ov028);
    } else {
        Scene_RequestPending(SCENE_CALENDAR, selector);
    }
    return -2;
}
