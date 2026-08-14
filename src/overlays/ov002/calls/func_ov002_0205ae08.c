/* Refresh one row header of the panel.
 *
 * The glyph tile is nRow*16+0xd0 and the attribute is 0xf when the row is
 * enabled and 0xe when it is not. The slot widget is nRow+1, floored at 3.
 *
 * When the panel has its extra field set and nRow is 0 it is in its special
 * single-row mode: the tile becomes 0x120 or 0xd0 depending on the tracked
 * count, and that same count is then drawn as a two-digit counter. Otherwise,
 * if the extra field is set at all, the two counter cells are cleared instead.
 * bRightAlign picks the column, exactly as it does inside the counter draw.
 *
 * Two codegen notes. The tile and attribute are 16-bit locals, so the computed
 * tile is truncated in the branch that computes it while the constant one is
 * folded and needs no truncation. And the row state is a conditional between
 * two enum constants rather than a literal 0 and 1: mwcc rewrites a literal
 * 0/1 conditional into a comparison and emits the predicated pair in the other
 * order.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[8];
    int nField0008;         /* +0x08 */
    u8 pad000c[0xa];
    u16 wField0016;         /* +0x16 */
} Ov002PanelSession;

enum {
    ROW_STATE_ACTIVE = 0,
    ROW_STATE_IDLE = 1
};

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_02053bb8(int nItemId);
extern void func_ov002_02053cd4(int nItemId);
extern void func_ov002_0205abe0(int nSlot, int nState, int nKind);
extern void func_ov002_0205ad5c(int nSlot, int nKind, u16 nTile, u16 nAttr,
                                int bRightAlign);
extern void func_ov002_0205aa3c(int nSlot, int nValue, int nColumn,
                                int bRightAlign, int bShowZero);
extern void MIi_CpuClear16(int nValue, int pDest, int nSize);

void func_ov002_0205ae08(int nRow, int bEnabled, int bRightAlign) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int bSpecial = 0;
    u16 nTile;
    u16 nAttr;
    int nSlot;

    if (s->nField0008 != 0 && nRow == 0) {
        bSpecial = 1;
        if (s->wField0016 == 0) {
            nTile = 0x120;
        } else {
            nTile = 0xd0;
        }
        nAttr = bEnabled ? 0xf : 0xe;
    } else {
        nTile = nRow * 16 + 0xd0;
        nAttr = bEnabled ? 0xf : 0xe;
    }

    nSlot = (nRow <= 2) ? 3 : nRow + 1;
    func_ov002_0205ad5c(nSlot, 0, nTile, nAttr, bRightAlign);
    func_ov002_0205abe0(nSlot, bRightAlign ? ROW_STATE_ACTIVE : ROW_STATE_IDLE,
                        0);

    if (bSpecial) {
        func_ov002_0205aa3c(nSlot, s->wField0016, 0, bRightAlign, 1);
    } else if (s->nField0008 != 0) {
        int pRes = func_ov002_02053bb8(0xb);
        int nCol = bRightAlign ? 0xb : 0xa;

        MIi_CpuClear16(0, pRes + (nCol + 0x240) * 2, 2);
        MIi_CpuClear16(0, pRes + (nCol + 0x260) * 2, 2);
    }

    func_ov002_02053cd4(9);
    func_ov002_02053cd4(0xb);
}
