/* Save commit state: shows the running play time, polls the save transfer and, when it finishes,
 * refreshes the slots and shows the result with a sound. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov009GameState {
    int value0;
    int pad004;
    int value8;
    u8 pad00c[0x1ca0];
} Ov009GameState;

typedef struct Ov009SaveContext {
    int variant;
    int nextVariant;
    int state;
    int currentSlot;
    int phase;
    u8 pad014[0x22c];
    int interactionLock;
    int field244;
    u8 slotPhase;
    u8 pad249[0x03];
    Ov009GameState snapshot;
} Ov009SaveContext;

extern Ov009GameState *volatile gGameState;

extern void Ov009_GetContext(void);
extern long long OS_GetTick(void);
extern long long Ov009_GetLatchedTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern void Ov009_RenderTimeDigits(int value);
extern int Ov009_PollSaveTransfer(Ov009SaveContext *ctx);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void Ov009_LatchTick(void);
extern int Ov009_TickSaveSlotPrep(Ov009SaveContext *ctx, int slot);
extern void Ov009_SaveMenu_RefreshRows(Ov009SaveContext *ctx);
extern void Ov009_SaveMenu_UpdateNumbers(Ov009SaveContext *ctx);
extern void Ov009_SetMenuEntriesVisible(int enabled, int mode);
extern void Ov009_DrawMenuText(Ov009SaveContext *ctx, int mode);
extern void Ov009_SetCtxField95fc(int value);
extern void Ov009_TickPageScroll(Ov009SaveContext *ctx);
extern void Ov009_UpdateSlotSelectionTargets(Ov009SaveContext *ctx);

void Ov009_TickSaveCommitState(Ov009SaveContext *ctx)
{
    Ov009_GetContext();

    switch (ctx->state) {
    case 0:
        {
            long long elapsed =
                OS_GetTick() - Ov009_GetLatchedTick();
            Ov009_RenderTimeDigits(
                (u32)(gGameState->value0 +
                      func_02020368(elapsed << 6, 0x1ff6210)));
        }
        break;

    case 1:
        break;

    case 2:
        {
            int result = Ov009_PollSaveTransfer(ctx);

            if (result == 0) {
                MI_CpuCopy8(gGameState, &ctx->snapshot,
                            sizeof(Ov009GameState));
                ctx->slotPhase = 0;
                ctx->state = 3;
                Ov009_LatchTick();
            } else if (result == 3) {
                ctx->interactionLock = 1;
                ctx->field244 = 1;
            }
        }
        break;

    case 3:
        if (Ov009_TickSaveSlotPrep(ctx, ctx->variant) == 2) {
            MI_CpuCopy8(&ctx->snapshot, gGameState,
                        sizeof(Ov009GameState));
            Ov009_SaveMenu_RefreshRows(ctx);
            Ov009_SaveMenu_UpdateNumbers(ctx);
            Ov009_SetMenuEntriesVisible(0, 0);
            Ov009_DrawMenuText(ctx, 3);
            PlaySound(0, 0x39);
            ctx->state = 4;
            Sleep_Unblock();
            Ov009_SetCtxField95fc(1);
        }
        break;

    case 4:
        break;

    case 5:
        SetMasterBrightnessMain(0);
        SetMasterBrightnessSub(0);
        break;
    }

    if (ctx->interactionLock != 0) {
        Ov009_DrawMenuText(ctx, 4);
        Ov009_SetMenuEntriesVisible(0, 0);
        ctx->state = 5;
        Ov009_SetCtxField95fc(0);
    }
    Ov009_TickPageScroll(ctx);
    Ov009_UpdateSlotSelectionTargets(ctx);
}
