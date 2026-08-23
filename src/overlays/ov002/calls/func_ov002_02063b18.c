/*
 * Ov002_DrawPageCounter - lay out "left / right" as icon cells and send them.
 *
 * Both numbers are written a digit at a time, lowest first, so the cells come
 * out right to left; the slash between them is the cell after the left number.
 * A digit is taken modulo ten and the number is shortened by a tenth each pass,
 * always as an unsigned short, so the walk ends on the last digit.
 *
 * The finished strip is handed to the graphics queue once, at the end.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[0x14];
    char *pTiles;
} Ov002GlyphSheet;

typedef struct {
    char pad000[0x18];
    void *pOwner;
    char *pStrip;
    char pad020[0xc];
    Ov002GlyphSheet *pSheet;
} Ov002PageContext;

extern Ov002PageContext *data_ov002_0207f634;

extern void GFXi_EnqueueCommand(int nCmd, int nDest, int nSrc, int nSize);
extern void func_ov002_02063aa0(int nCell, int nSlot);

void func_ov002_02063b18(int nLeft, int nRight)
{
    Ov002PageContext *ctx;
    int nCell;
    u8 nDigit;

    ctx = data_ov002_0207f634;
    nCell = 0;
    if (ctx->pOwner == 0) {
        return;
    }

    do {
        nDigit = (u8)(nLeft % 10);
        func_ov002_02063aa0(nCell, nDigit);
        nCell++;
        nLeft = (u16)(nLeft / 10);
    } while (nLeft != 0);

    func_ov002_02063aa0(nCell, 10);
    nCell++;

    do {
        nDigit = (u8)(nRight % 10);
        func_ov002_02063aa0(nCell, nDigit);
        nCell++;
        nRight = (u16)(nRight / 10);
    } while (nRight != 0);

    GFXi_EnqueueCommand(0x16, 0x1a60, (int)ctx->pStrip, 0x40);
}
