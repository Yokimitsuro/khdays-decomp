#pragma thumb on
/* PauseMenu_PollInput -- pause menu input poll, MAIN (THUMB). Always returns 0. While
 * Session_GetLocalPlayerIndex holds, a first open (+0xe8 clear, root state 1) outside mode bit 1
 * hands over to the overlay and sets game field 0x2484. With data_0204c240 bit 2 outside mode bit
 * 1 it only runs the pending-request pair (PollAndLatchRequest / LatchPendingRequestOnce) when
 * field 0x248f is set and nothing is open. Otherwise the menu needs gPauseAllowed or field 0x20ef,
 * an idle menu (PauseMenu_GetMode) and an expired timer (+0xc8, counted down here); it then reacts
 * to START (gPadPressed & 8, KEYINPUT bit 3) or a latched request (+0xd8): it is refused while
 * GetMasterBrightnessMain reports busy (unless mode 0xc without GetMasterBrightnessSub), in mode
 * bit 1 without the overlay's permission, and it only latches the request (+0xd8) in mode bit 3
 * with data_0204be04 clear or when an entry (+0xdc) finds none of the three overlay states; a real
 * open pushes step 1 or 2 (PauseMenu_SetMode) before Callbacks_Run(0). */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    char pad0000[0xc8];
    int timer;                          /* +0xc8 */
    char pad00cc[0xd8 - 0xcc];
    int request;                        /* +0xd8 */
    int entry;                          /* +0xdc */
    int handedOver;                     /* +0xe0 */
    int pad00e4;
    int opened;                         /* +0xe8 */
} PauseContext;

typedef struct {
    u16 state;                          /* +0x00 */
    u16 pad02;
    PauseContext *pCtx;                 /* +0x04 */
} Root0204be08;

extern Root0204be08 data_0204be08;
extern u8 data_0204c240;
extern u8 gPauseAllowed;
extern u8 data_0204be04;
extern unsigned short gPadPressed;    /* keys pressed this frame */

extern void Ov023_FlushTextBox(void);
extern int Ov023_ScriptTestStatusBit3(void);
extern int Ov002_Scene_IsIdle(void);
extern int Ov002_Field_IsActive(void);
extern int Ov002_ScenePanel_IsState4(void);
extern int Ov002_ScenePanel_IsIdle(void);
extern int Ov002_ScenePanel_IsState3(void);

int PauseMenu_PollInput(void)
{
    PauseContext *ctx = data_0204be08.pCtx;

    if (Session_GetLocalPlayerIndex() != 0) {
        if (LoadGlobalU16At0() & 2) {
            return 0;
        }
        if (ctx->opened == 0 && data_0204be08.state == 1) {
            Ov023_FlushTextBox();
            GameState_SetField(0x2484, 1, 1);
            ctx->opened = 1;
            return 0;
        }
    }
    if ((data_0204c240 & 4) && !(LoadGlobalU16At0() & 2)) {
        if ((GetMasterBrightnessSub() == 0 || Ov023_ScriptTestStatusBit3() != 0) && GameState_IsFlagSet(0x248f) != 0
            && ctx->opened == 0) {
            PollAndLatchRequest();
            LatchPendingRequestOnce();
        }
        return 0;
    }
    if (gPauseAllowed == 0 && GameState_IsFlagSet(0x20ef) == 0) {
        return 0;
    }
    if (PauseMenu_GetMode() != 0) {
        return 0;
    }
    if (ctx->timer > 0) {
        ctx->timer--;
        return 0;
    }
    if ((gPadPressed & 8) || ctx->request != 0) {
        if (GetMasterBrightnessMain() != 0 && (LoadGlobalU16At0() != 0xc || GetMasterBrightnessSub() != 0)) {
            return 0;
        }
        if ((LoadGlobalU16At0() & 2) && Ov002_Scene_IsIdle() == 0) {
            return 0;
        }
        if ((LoadGlobalU16At0() & 8) && data_0204be04 == 0) {
            ctx->request = 1;
            return 0;
        }
        if (ctx->entry != 0) {
            if (Ov002_Field_IsActive() != 0) {
                return 0;
            }
            if (Ov002_ScenePanel_IsState4() == 0 && Ov002_ScenePanel_IsIdle() == 0 && Ov002_ScenePanel_IsState3() == 0) {
                ctx->request = 1;
                return 0;
            }
            PauseMenu_SetMode((u8)(((data_0204c240 & 4) && (LoadGlobalU16At0() & 2)) ? 2 : 1));
        }
        Callbacks_Run(0);
    }
    return 0;
}
#pragma thumb off
