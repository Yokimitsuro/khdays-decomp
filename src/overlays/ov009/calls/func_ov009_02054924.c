typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

extern void func_ov009_0204e440(void);
extern void func_02030158(void *renderer);
extern u16 *func_ov009_02052788(void *records, int index);
extern void func_ov009_02053308(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text,
    int shadow
);
extern void func_ov009_02052abc(
    u32 elapsed,
    u16 *hours,
    char *minutes,
    char *seconds
);
extern void func_020262a0(u16 *dst, int count, const u16 *format, ...);
extern const u16 data_ov009_0205638c[];

void func_ov009_02054924(Ov009SaveContext *ctx)
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

    func_ov009_0204e440();
    func_02030158(ctx->renderer);

    row = ctx->rows;
    rowIndex = 0;
    do {
        int y = (ctx->basePositions[rowIndex].y >> 12)
              + (ctx->tweenPositions[rowIndex].y >> 12);
        int x = (ctx->basePositions[rowIndex].x >> 12)
              + (ctx->tweenPositions[rowIndex].x >> 12);
        int drawY = y - 32;

        if (row->state == 2) {
            const u16 *text = func_ov009_02052788(ctx->varRecords, 12);
            func_ov009_02053308(ctx->renderer, x + 55, drawY + 12, 4, text, 0);
        } else if (row->state == 1) {
            func_ov009_02052abc(row->elapsed, &hours, (char *)&minutes, (char *)&seconds);

            itemIndex = 0;
            do {
                textX = 27;
                switch (itemIndex) {
                case 0: {
                    const u16 *format = func_ov009_02052788(ctx->varRecords, 9);
                    func_020262a0(buffer, 128, format, (u32)row->value16);
                    textX += 2;
                    shadow = 0;
                    break;
                }
                case 1: {
                    const u16 *format = func_ov009_02052788(ctx->varRecords, 4);
                    func_020262a0(buffer, 128, format, row->value32);
                    textX += 112;
                    shadow = 1;
                    break;
                }
                case 2:
                    textX += 137;
                    func_020262a0(buffer, 128, data_ov009_0205638c, (u32)hours);
                    shadow = 1;
                    break;
                case 3:
                    textX += 146;
                    func_020262a0(buffer, 128, data_ov009_0205638c, (u32)minutes);
                    shadow = 2;
                    break;
                case 4:
                    textX += 160;
                    func_020262a0(buffer, 128, data_ov009_0205638c, (u32)seconds);
                    shadow = 2;
                    break;
                case 5:
                case 6: {
                    const u16 *format;
                    int offset = itemIndex == 5 ? 140 : 154;

                    format = func_ov009_02052788(ctx->varRecords, 8);
                    func_020262a0(buffer, 128, format);
                    textX += offset;
                    shadow = 1;
                    break;
                }
                }

                func_ov009_02053308(
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
