/* Ov000_DrawLoadPageText -- Scene 1: draw the load-page text for the current state.
 * Guarded by the draw-done flag (+0x4d94). When the transition result flags
 * (+0x6a48, two SIGNED 16-bit bitfields -- the same declaration the caller
 * Ov000_TickLoadScene uses) are pending, draws the result records (0x13 when
 * the high half is set, else 0x14, plus 0x15). Otherwise draws per activeState:
 * 1/2 = header + optional line 2, 3 = phase line (formatted page number) or
 * completion records 0x11/0x12 (or 0x10 when the alt flag is set) + the two
 * footer records 7/8 at x=0x50/0xae, 4 = record 10 (formatted) or 9,
 * 5 = records 0xe (formatted with TWO page-number arguments -- the fifth
 * argument goes on the stack) or 4+5, or 0x16, + footers. Enqueues the surface
 * and sets the done flag.
 * MATCH NOTE: the halfword tests MUST be bitfield reads, not (short)/>>16
 * casts of a u32 -- the cast form allocates the word to a fresh register while
 * the bitfield form reuses the address register (6-byte residue otherwise). */

#include "nitro/types.h"

typedef struct Ov000PageSlot {
    int base;
    int current;
    u8  pad_0008[0x18];
} Ov000PageSlot;

typedef struct Ov000TextSceneContext {
    u8 pad_0000[0x4ad0];
    int activeState;
    int field_4ad4;
    u8 pad_4ad8[8];
    int field_4ae0;
    u8 pad_4ae4[0x4b08 - 0x4ae4];
    int pageIndex;
    u8 pad_4b0c[0x4b20 - 0x4b0c];
    Ov000PageSlot slots[3];
    u8 pad_4b80[0x4cb4 - 0x4b80];
    u8 messageArchive[0x0c];
    u8 surface0[0x3c];
    u8 surface1[0x3c];
    u8 surface2[0x3c];
    u8 pad_4d74[0x4d94 - 0x4d74];
    int drawDone;
    u8 pad_4d98[0x6a48 - 0x4d98];
    signed int resultFlags : 16;
    signed int resultFlagsHigh : 16;
} Ov000TextSceneContext;

extern Ov000TextSceneContext *data_ov000_0205ac24;

extern void Obj_InvokeInnerVtable4(void *surface);
extern int *Ov000_GetVarRecordByIndex(void *object, int index);
extern void Ov000_DrawWithShadow(void *surface, int x, int y, int size, int *record, int sel);
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void EnqueueObjGfxCommand(void *surface);

void Ov000_DrawLoadPageText(void)
{
    Ov000TextSceneContext *ctx = data_ov000_0205ac24;
    u16 buffer[128];
    int *record;

    if (ctx->drawDone != 0) {
        return;
    }

    Obj_InvokeInnerVtable4(ctx->surface1);
    ctx = data_ov000_0205ac24;

    if (ctx->resultFlags != 0) {
        int id;
        id = (ctx->resultFlagsHigh != 0) ? 0x13 : 0x14;
        record = Ov000_GetVarRecordByIndex(ctx->messageArchive, id);
        Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 4, record, 0);
        record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 0x15);
        Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0x19, 4, record, 0);
    } else {
        switch (ctx->activeState) {
        case 0:
            break;
        case 1:
        case 2:
            record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 1);
            Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 2, record, 0);
            if (data_ov000_0205ac24->pageIndex != 3) {
                record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 2);
                Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0x1e, 4, record, 0);
            }
            break;
        case 3:
            if (ctx->field_4ad4 == 0) {
                if (ctx->pageIndex < 3) {
                    record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 3);
                    Text_FormatUtf16(buffer, 0x80, (const u16 *)record,
                                  data_ov000_0205ac24->pageIndex + 1);
                    Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 2,
                                        (int *)buffer, 0);
                } else {
                    record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 0x11);
                    Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0, 2, record, 0);
                    record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 0x12);
                    Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 4, record, 0);
                }
            } else {
                record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 0x10);
                Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 2, record, 0);
            }
            record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 7);
            Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x50, 0x21, 2, record, 2);
            record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 8);
            Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0xae, 0x21, 2, record, 2);
            break;
        case 4:
            if (ctx->field_4ae0 == 2) {
                record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 10);
                Text_FormatUtf16(buffer, 0x80, (const u16 *)record,
                              data_ov000_0205ac24->pageIndex + 1);
                Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 6,
                                    (int *)buffer, 0);
            } else {
                record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 9);
                Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 6, record, 0);
            }
            break;
        case 5:
            if (ctx->field_4ad4 == 0) {
                if (ctx->pageIndex < 3 &&
                    ctx->slots[ctx->pageIndex].base == 2) {
                    record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 0xe);
                    Text_FormatUtf16(buffer, 0x80, (const u16 *)record,
                                  data_ov000_0205ac24->pageIndex + 1,
                                  data_ov000_0205ac24->pageIndex + 1);
                    Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0, 6,
                                        (int *)buffer, 0);
                } else {
                    record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 4);
                    Text_FormatUtf16(buffer, 0x80, (const u16 *)record,
                                  data_ov000_0205ac24->pageIndex + 1);
                    Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0, 6,
                                        (int *)buffer, 0);
                    record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 5);
                    Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0xf, 6, record, 0);
                }
            } else {
                record = Ov000_GetVarRecordByIndex(ctx->messageArchive, 0x16);
                Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x10, 0, 6, record, 0);
            }
            record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 7);
            Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0x50, 0x21, 2, record, 2);
            record = Ov000_GetVarRecordByIndex(data_ov000_0205ac24->messageArchive, 8);
            Ov000_DrawWithShadow(data_ov000_0205ac24->surface1, 0xae, 0x21, 2, record, 2);
            break;
        }
    }

    EnqueueObjGfxCommand(data_ov000_0205ac24->surface1);
    data_ov000_0205ac24->drawDone = 1;
}
