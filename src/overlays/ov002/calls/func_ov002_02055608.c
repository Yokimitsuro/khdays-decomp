/*
 * Ov002_DrawSlotIcons - draw the icon each filled panel slot asks for.
 *
 * The caller hands one signed byte per slot id. Only ids that actually landed
 * somewhere are drawn, and the slot they landed in picks where: two bytes per
 * slot, position then mode. A byte of -1 asks for the fixed 0x98 sprite;
 * anything at or past the last real entry is clamped to 3 and drawn as a 2x2
 * block of map rows instead of a sprite; everything else looks its sprite id
 * up in the table.
 *
 * ARM.
 *
 * Two shapes the codegen needs. The handle goes through a named local rather
 * than being nested in the call: written nested, mwcc hoists the byte-pair
 * address into a callee-saved register before the call instead of computing it
 * after. And nIcon is a signed char, not an int - the clamp copies it into
 * nKind, and with both the same width mwcc propagates the copy backwards and
 * compares nIcon where the ROM compares nKind. The narrower type is what keeps
 * the two apart.
 */

typedef unsigned short u16;

typedef struct {
    char pad0000[0x220];
    int anSlotForId[4];                 /* +0x220 */
} Ov002PanelCtx;

extern Ov002PanelCtx *data_ov002_0207f614;
extern unsigned char data_ov002_0207db94[];
extern u16 data_ov002_0207db7e[];

extern int func_ov022_020882f8(void);
extern int func_ov002_02053558(int nId);
extern int func_ov002_020535c4(int nHandle, int nPosition, int nMode);
extern void func_ov002_02053b28(int nDest, int nX, int nY, short nWidth,
                                short nHeight);

void func_ov002_02055608(signed char *pIcons)
{
    unsigned char *pPos;
    Ov002PanelCtx *ctx;
    int i;
    int nSlot;
    signed char nIcon;
    int nKind;
    int nHandle;

    ctx = data_ov002_0207f614;
    pPos = data_ov002_0207db94;
    for (i = 0; i < 4; i++) {
        nSlot = ctx->anSlotForId[i];
        if (nSlot >= 0) {
            nIcon = pIcons[i];
            nKind = nIcon;
            if (nKind >= func_ov022_020882f8() - 1) {
                nKind = 3;
            }
            switch (nKind) {
            case -1:
                nHandle = func_ov002_02053558(0x98);
                func_ov002_020535c4(nHandle, pPos[nSlot * 2],
                                    pPos[nSlot * 2 + 1]);
                break;
            case 3:
                func_ov002_02053b28(0xb, pPos[nSlot * 2], pPos[nSlot * 2 + 1],
                                    2, 2);
                break;
            default:
                nHandle = func_ov002_02053558(data_ov002_0207db7e[nIcon]);
                func_ov002_020535c4(nHandle, pPos[nSlot * 2],
                                    pPos[nSlot * 2 + 1]);
                break;
            }
        }
    }
}
