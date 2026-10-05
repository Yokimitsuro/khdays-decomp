/* Draws the save menu's message text for the mode (prompts, confirmations, results) and uploads it.
 */

#include "nitro/types.h"

typedef struct Ov009SlotRecord {
    int status;
    u8 pad004[0x18];
} Ov009SlotRecord;

typedef struct Ov009SaveContext {
    int selectedSlot;
    u8 pad004[0x20];
    Ov009SlotRecord slots[10];
    u8 pad13c[0x20];
    u8 varRecords[0x48];
    u8 renderer[0xa0];
    int alternatePrompt;
} Ov009SaveContext;

extern void Obj_InvokeInnerVtable4(void *renderer, int mode, int arg2, int arg3);
extern u16 *Ov009_GetVarRecordByIndex(void *records, int index);
extern void Ov009_DrawTextNewline(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text
);
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void Ov009_DrawWithShadow(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text,
    int shadow
);
extern void Text_DrawWithShadow(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text,
    int option
);
extern void EnqueueObjGfxCommand(void *renderer);

void Ov009_DrawMenuText(
    Ov009SaveContext *ctx,
    int mode,
    int arg2,
    int arg3
)
{
    u16 buffer[128];
    const u16 *text;

    Obj_InvokeInnerVtable4(ctx->renderer, mode, arg2, arg3);

    switch (mode) {
    case 0:
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 1);
        Ov009_DrawTextNewline(ctx->renderer, 0x62, 0, 2, text);
        break;

    case 1:
        text = Ov009_GetVarRecordByIndex(
            ctx->varRecords,
            ctx->slots[ctx->selectedSlot].status != 0 ? 2 : 3
        );
        Text_FormatUtf16(buffer, 128, text, ctx->selectedSlot + 1);
        Ov009_DrawWithShadow(ctx->renderer, 0x10, 0, 2, buffer, 0);
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 5);
        Ov009_DrawWithShadow(ctx->renderer, 0x50, 0x12, 2, text, 2);
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 6);
        Ov009_DrawWithShadow(ctx->renderer, 0xae, 0x12, 2, text, 2);
        break;

    case 2:
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 11);
        Text_DrawWithShadow(ctx->renderer, 0x10, 0, 2, text, 0);
        break;

    case 3:
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 7);
        Text_DrawWithShadow(ctx->renderer, 0x10, 0, 2, text, 0);
        break;

    case 4:
        text = Ov009_GetVarRecordByIndex(
            ctx->varRecords,
            ctx->alternatePrompt != 0 ? 10 : 13
        );
        Text_DrawWithShadow(ctx->renderer, 0x10, 0, 4, text, 0);
        break;

    case 5:
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 14);
        Text_DrawWithShadow(ctx->renderer, 0x10, 0, 2, text, 0);
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 5);
        Ov009_DrawWithShadow(ctx->renderer, 0x50, 0x12, 2, text, 2);
        text = Ov009_GetVarRecordByIndex(ctx->varRecords, 6);
        Ov009_DrawWithShadow(ctx->renderer, 0xae, 0x12, 2, text, 2);
        break;
    }

    EnqueueObjGfxCommand(ctx->renderer);
}
