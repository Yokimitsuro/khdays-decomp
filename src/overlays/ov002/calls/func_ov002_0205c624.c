/* Repaint one group of six panel rows.
 *
 * Rows are indexed nGroup*6 + i, so a group is a fixed block of six cells. A
 * row draws enabled only when its cell's first byte is not 0xff and the
 * availability query answers non-zero, and the row the panel's kind points at
 * is the one drawn right-aligned. Afterwards the group's own header widget is
 * fetched by tag, pushed and invoked.
 *
 * Two codegen notes. The enabled flag is one short-circuit expression, not an
 * if/else writing 0 and 1: that is what makes mwcc predicate the 1 onto the
 * second test instead of branching around both arms. And the row index needs
 * nGroup*6 hoisted into its own local -- spelled inline at each use, mwcc turns
 * it into an induction variable and increments it, while the ROM keeps the base
 * fixed and recomputes base + i.
 */
typedef unsigned char u8;

typedef struct {
    u8 bFirst;
    u8 bSecond;
} Ov002PanelCell;

typedef struct {
    u8 bKind;                       /* +0x00 */
    u8 pad0001[0x0f];
    int nState;                     /* +0x10 */
    u8 pad0014[0x1e];
    Ov002PanelCell aCells[0x227];   /* +0x32 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205a600(int nIndex);
extern void func_ov002_0205afb4(int nIndex, int nSlot, int nColumn,
                                int bEnabled, int bRightAlign);
extern int func_ov002_02053558(int nTag);
extern void func_ov002_02053578(int nHandle, short nValue, short nKind);
extern void func_ov002_020535a4(int nHandle);
extern void func_ov002_02053cd4(int nItemId);

void func_ov002_0205c624(int nGroup) {
    Ov002PanelSession *s;
    int i;
    int nBase;
    int nHandle;

    s = data_ov002_0207f620;
    nBase = nGroup * 6;

    for (i = 0; i < 6; i++) {
        int bEnabled = s->aCells[nBase + i].bFirst != 0xff &&
                       func_ov002_0205a600(nBase + i) != 0;

        func_ov002_0205afb4(nBase + i, i, 1, bEnabled, s->bKind == i);
    }

    if (s->nState != 0) {
        nHandle = func_ov002_02053558(0x58);
    } else {
        nHandle = func_ov002_02053558(0x5c);
    }
    func_ov002_02053578(nHandle, 1, 0xa);
    func_ov002_020535a4(nHandle);
    func_ov002_02053cd4(0xb);
}
