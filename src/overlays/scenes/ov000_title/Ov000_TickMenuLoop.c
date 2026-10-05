/* Ov000_TickMenuLoop -- the ov000 menu's interactive loop.
 *
 * The state Ov000_MenuFadeInState hands off to once the fade-in finishes, and the one the
 * page transitions come back to.  Per frame it services input, finishes the cross-fade,
 * redraws, dispatches the selection and watches the idle timer.
 *
 * Input is held off until the transition object at gPadHeld reports idle; from then
 * on Ov000_StepMenuSelection advances the cursor row for the current page.  A/Start counts as
 * confirm (key mask 9), B as cancel (mask 2).
 *
 * Confirm on the root page: row 0 arms the sub-page (cursorRow[1] pre-selected when a save
 * exists, altLayout off) and pushes pendingPage; row 1 arms the alternate sub-page layout
 * with pendingPage 2; row 2 only works when extraOptionAvailable is set and leaves for
 * Ov000_TickFadeThenPublishContext.  Confirm on a sub-page leaves for Ov000_TickFadeOutToScene or
 * Ov000_BootFadeAndSubScreenSetup depending on altLayout.  Cancel pops a page -- twice when the page is
 * deeper than 1 -- and returns to the transition state Ov000_TickMenuLevelChange.
 *
 * The idle timer is restarted while the transition object is busy.  Once 0x69 = 105 seconds
 * have passed with nothing pressed it fires Table_TailCallWithEntry(0, 0x1e) and hands off to
 * Ov000_FadeOutAndStartMovie, i.e. the attract sequence.
 *
 * CODEGEN NOTE -- two shapes are load-bearing.  The two pendingPage decrements have to be
 * compound assignments (`-= 1`): a compound assignment evaluates the lvalue address once, so
 * mwcc binds a pointer to the field and loads/stores through it at offset 0, whereas
 * `x = x - 1` recomputes the address on each side and reaches the field through two
 * different bases.  And the idle test has to be written as the POSITIVE guard
 * (`if (elapsed > 0x69) { ...; return next; } return 0;`); with the early-out spelling mwcc
 * schedules the pool load of the next state ahead of the counter store.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef void         *StateFn;

typedef struct Ov000MenuContext {
    int       counter;
    u8        pad_0004[8];
    u8        node[0x108];
    u8        scrollBounds[0x9c];
    u8        pad_01b0[0x4a38];
    u8        inputSource[0x1c];
    u8        pad_4c04[0x28];
    s8        pendingPage;
    s8        page;
    s8        cursorRow[3];
    s8        altLayout;
    u8        pad_4c32[0x21];
    u8        loadAvailable;
    int       extraOptionAvailable;
    int       inputReady;
    u8        pad_4c5c[8];
    long long enterTick;
} Ov000MenuContext;

extern unsigned short gPadHeld;
extern unsigned short gPadPressed;

extern Ov000MenuContext *NNSi_FndGetCurrentRootHeap(void);
extern void      Ov000_FadeStateHookNoOp(void);
extern int       Ov000_StepMenuSelection(void *input, int selection, int group);
extern void      G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
extern void      Ov000_RefreshMenuLayout(void);
extern void      Ov000_RegisterLogoObjects(void);
extern void      Camera_CommitMatricesEx(void *bounds, int a, int b, int c, int d);
extern void      Scene_DrawNode(void *node);
extern long long OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern void      Table_TailCallWithEntry(int a, int b);
extern void      Ov000_TickMenuLevelChange(void);
extern void      Ov000_TickFadeThenPublishContext(void);
extern void      Ov000_TickFadeOutToScene(void);
extern void      Ov000_BootFadeAndSubScreenSetup(void);
extern void      Ov000_FadeOutAndStartMovie(void);

StateFn Ov000_TickMenuLoop(void) {
    Ov000MenuContext *ctx;
    int confirm;
    int cancel;

    ctx = NNSi_FndGetCurrentRootHeap();
    confirm = 0;
    cancel = 0;
    Ov000_FadeStateHookNoOp();
    if (ctx->inputReady != 0) {
        KeyRepeat_Step(ctx->inputSource);
        ctx->cursorRow[ctx->page] = Ov000_StepMenuSelection(ctx->inputSource,
                                                        ctx->cursorRow[ctx->page],
                                                        ctx->page);
    } else if (gPadHeld == 0) {
        ctx->inputReady = 1;
    }

    if (ctx->counter < 0x3c) {
        SetMasterBrightnessSub(0x10);
        ctx->counter = ctx->counter + 1;
    } else if (ctx->counter <= 0x5c) {
        SetMasterBrightnessSub(0x10 - (ctx->counter - 0x3c) / 2);
        G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, (ctx->counter - 0x3c) / 2,
                           0x10 - (ctx->counter - 0x3c) / 2);
        ctx->counter = ctx->counter + 1;
    } else {
        SetMasterBrightnessSub(0);
        G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, 0x10, 0);
    }

    Ov000_RefreshMenuLayout();
    Ov000_RegisterLogoObjects();
    if ((gPadPressed & 9) != 0) {
        confirm = 1;
    } else if ((gPadPressed & 2) != 0) {
        cancel = 1;
    }
    Camera_CommitMatricesEx(ctx->scrollBounds, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
    Scene_DrawNode(ctx->node);

    if (confirm != 0) {
        if (ctx->page == 0) {
            switch (ctx->cursorRow[ctx->page]) {
            case 0:
                if (ctx->page + 1 != 3) {
                    PlaySound(0, 1);
                    ctx->counter = 0;
                    if (ctx->loadAvailable != 0) {
                        ctx->cursorRow[1] = 1;
                    }
                    ctx->altLayout = 0;
                    ctx->pendingPage = ctx->pendingPage + 1;
                    return (StateFn)Ov000_TickMenuLevelChange;
                }
                break;
            case 1:
                PlaySound(0, 1);
                ctx->counter = 0;
                ctx->altLayout = 1;
                ctx->pendingPage = 2;
                return (StateFn)Ov000_TickMenuLevelChange;
            case 2:
                if (NNSi_FndGetCurrentRootHeap()->extraOptionAvailable != 0) {
                    PlaySound(0, 1);
                    ctx->counter = 0;
                    return (StateFn)Ov000_TickFadeThenPublishContext;
                }
                break;
            }
        } else if (ctx->page >= 1) {
            ctx->counter = 0;
            switch (ctx->cursorRow[ctx->page]) {
            case 0:
                PlaySound(0, 1);
                if (ctx->altLayout == 0) {
                    return (StateFn)Ov000_TickFadeOutToScene;
                }
                return (StateFn)Ov000_BootFadeAndSubScreenSetup;
            case 1:
                PlaySound(0, 1);
                return (StateFn)Ov000_BootFadeAndSubScreenSetup;
            }
        }
    } else if (cancel != 0 && ctx->page != 0) {
        PlaySound(0, 3);
        ctx->pendingPage -= 1;
        if (ctx->page > 1) {
            ctx->pendingPage -= 1;
        }
        ctx->counter = 0;
        return (StateFn)Ov000_TickMenuLevelChange;
    }

    if (ctx->inputReady != 0 && gPadHeld != 0) {
        ctx->enterTick = OS_GetTick();
    }
    if (func_02020368((OS_GetTick() - ctx->enterTick) << 6, 0x01ff6210) > 0x69) {
        Table_TailCallWithEntry(0, 0x1e);
        ctx->counter = 0;
        return (StateFn)Ov000_FadeOutAndStartMovie;
    }
    return 0;
}
