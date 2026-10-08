/* Ov000_WaitLaunchedSceneThenMenu -- wait for the launched scene to finish, then return to the menu.
 *
 * Which scene is running depends on ctx->transitionMode: mode 0 is the movie player (ov012),
 * anything else is ov011.  While that scene reports "still running" this returns 0 and the
 * state machine stays.  Once it is done: destroy the launched scene's object, black out both
 * screens, unload whichever overlay was used, arm handler 0x20e9, and re-enter the menu
 * through Ov000_EnterSceneAndLoadResource with the two scene values as start parameters.
 *
 * Both overlay ids are the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd
 * emits `OVERLAY_11_ID = 11;` / `OVERLAY_12_ID = 12;` into arm9.lcf.  Both are encodable ARM
 * immediates, so written as plain integers the two pool words vanish and the function comes
 * out 8 bytes short.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef u32 FSOverlayID;
typedef void (*Ov000StateFn)(void);

extern u32 OVERLAY_11_ID[1];
extern u32 OVERLAY_12_ID[1];
#define FS_OVERLAY_ID_ov011 ((FSOverlayID)(u32) & (OVERLAY_11_ID))
#define FS_OVERLAY_ID_ov012 ((FSOverlayID)(u32) & (OVERLAY_12_ID))

typedef struct OverlayStartParams {
    u32 first;
    u32 second;
} OverlayStartParams;

typedef struct Ov000SceneContext {
    short secondValue;
    short firstValue;
    u8 pad_0004[0xd134];
    int transitionMode;
    void *pSceneObject;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern int Ov012_IsGlobalFlag3Set(void);
extern int Ov011_IsBootStateReady(void);
extern void *VeneerTo_Obj_Destroy(void *handle);
extern Ov000StateFn Ov000_EnterSceneAndLoadResource(const OverlayStartParams *params);

Ov000StateFn Ov000_WaitLaunchedSceneThenMenu(void) {
    Ov000SceneContext *ctx = NNSi_FndGetCurrentRootHeap();
    OverlayStartParams params;

    if (ctx->transitionMode == 0) {
        if (Ov012_IsGlobalFlag3Set() == 0) {
            return 0;
        }
    } else if (Ov011_IsBootStateReady() == 0) {
        return 0;
    }
    VeneerTo_Obj_Destroy(ctx->pSceneObject);
    SetMasterBrightnessMain(-0x10);
    SetMasterBrightnessSub(-0x10);
    if (ctx->transitionMode == 0) {
        UnloadOverlaySync(0, FS_OVERLAY_ID_ov012);
    } else {
        UnloadOverlaySync(0, FS_OVERLAY_ID_ov011);
    }
    params.first = ctx->firstValue;
    params.second = ctx->secondValue;
    GameState_ClearFlag(0x20e9);
    Sleep_Unblock();
    return Ov000_EnterSceneAndLoadResource(&params);
}
