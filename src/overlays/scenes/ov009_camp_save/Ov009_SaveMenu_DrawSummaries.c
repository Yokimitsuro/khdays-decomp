/* Draws each save slot's summary text (empty label or level, munny, play time). */

#include "nitro/types.h"

typedef struct Ov009SummaryRow {
    u16 pad000;
    u16 value16;
    u32 value32;
    u8 pad008[4];
    u32 elapsed;
    int state;
    u8 pad014[8];
} Ov009SummaryRow;

typedef struct Ov009BasePosition {
    int x;
    int y;
    u8 pad008[0x38];
} Ov009BasePosition;

typedef struct Ov009TweenPosition {
    int x;
    int y;
} Ov009TweenPosition;

typedef struct Ov009SaveContext {
    u8 pad000[0x14];
    Ov009SummaryRow rows[3];
    u8 pad068[4];
    Ov009BasePosition basePositions[3];
    Ov009TweenPosition tweenPositions[3];
    u8 pad144[0x18];
    u8 varRecords[0x84];
    u8 renderer[1];
} Ov009SaveContext;

extern void Ov009_GetContext(void);
extern void Obj_InvokeInnerVtable4(void *renderer);
extern u16 *Ov009_GetVarRecordByIndex(void *records, int index);
extern void Ov009_DrawWithShadow(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text,
    int shadow
);
extern void Ov009_SplitTimeUnitsHMS(
    u32 elapsed,
    u16 *hours,
    char *minutes,
    char *seconds
);
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern const u16 data_ov009_0205638c[];

void Ov009_SaveMenu_DrawSummaries(Ov009SaveContext *ctx)
{
    int rowIndex;
    Ov009SummaryRow *row;
    u8 seconds;
    u8 minutes;
    u16 hours;
    u16 buffer[128];
    int itemIndex;
    int textX;
    int shadow = 0;

    Ov009_GetContext();
    Obj_InvokeInnerVtable4(ctx->renderer);

    row = ctx->rows;
    rowIndex = 0;
    do {
        int y = (ctx->basePositions[rowIndex].y >> 12)
              + (ctx->tweenPositions[rowIndex].y >> 12);
        int x = (ctx->basePositions[rowIndex].x >> 12)
              + (ctx->tweenPositions[rowIndex].x >> 12);
        int drawY = y - 32;

        if (row->state == 2) {
            const u16 *text = Ov009_GetVarRecordByIndex(ctx->varRecords, 12);
            Ov009_DrawWithShadow(ctx->renderer, x + 55, drawY + 12, 4, text, 0);
        } else if (row->state == 1) {
            Ov009_SplitTimeUnitsHMS(row->elapsed, &hours, (char *)&minutes, (char *)&seconds);

            itemIndex = 0;
            do {
                textX = 27;
                switch (itemIndex) {
                case 0: {
                    const u16 *format = Ov009_GetVarRecordByIndex(ctx->varRecords, 9);
                    Text_FormatUtf16(buffer, 128, format, (u32)row->value16);
                    textX += 2;
                    shadow = 0;
                    break;
                }
                case 1: {
                    const u16 *format = Ov009_GetVarRecordByIndex(ctx->varRecords, 4);
                    Text_FormatUtf16(buffer, 128, format, row->value32);
                    textX += 112;
                    shadow = 1;
                    break;
                }
                case 2:
                    textX += 137;
                    Text_FormatUtf16(buffer, 128, data_ov009_0205638c, (u32)hours);
                    shadow = 1;
                    break;
                case 3:
                    textX += 146;
                    Text_FormatUtf16(buffer, 128, data_ov009_0205638c, (u32)minutes);
                    shadow = 2;
                    break;
                case 4:
                    textX += 160;
                    Text_FormatUtf16(buffer, 128, data_ov009_0205638c, (u32)seconds);
                    shadow = 2;
                    break;
                case 5:
                case 6: {
                    const u16 *format;
                    int offset = itemIndex == 5 ? 140 : 154;

                    format = Ov009_GetVarRecordByIndex(ctx->varRecords, 8);
                    Text_FormatUtf16(buffer, 128, format);
                    textX += offset;
                    shadow = 1;
                    break;
                }
                }

                Ov009_DrawWithShadow(
                    ctx->renderer,
                    x + textX,
                    drawY + 23,
                    2,
                    buffer,
                    shadow
                );
                itemIndex++;
            } while (itemIndex < 7);
        }

        row++;
        rowIndex++;
    } while (rowIndex < 3);
}
