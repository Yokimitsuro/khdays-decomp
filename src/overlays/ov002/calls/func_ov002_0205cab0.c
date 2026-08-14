/* Repaint the panel around the cached sub-entry: highlight the slot it lives
 * in, colour the confirm label by whether the entry is actually usable, and
 * flip the confirm/cancel pair to whichever side the current kind wants. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 nKey;
    u16 nTag;
    void *pObject;
    u8 pad0008[0x10];
} Ov002PanelSubEntry;

typedef struct {
    u8 pad0000[7];
    u8 bDefaultKind;                /* +0x7 */
    u8 pad0008[0x49c];
    Ov002PanelSubEntry *pCachedEntry;   /* +0x4a4 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_02053558(int nId);
extern void func_ov002_020535a4(int nEntry);
extern int func_ov002_0205a714(int nGroup, int nKey);
extern int func_ov002_0205a730(int nGroup, int nKey);
extern int func_ov002_0205a540(int nKey);
extern void func_ov002_0205ad5c(int nSlot, int nSub, u16 wValue, u16 nColour,
                                int bFlag);
typedef enum {
    PANEL_SIDE_LEFT = 0,
    PANEL_SIDE_RIGHT = 1
} Ov002PanelSide;

extern void func_ov002_0205abe0(int nSlot, Ov002PanelSide eSide, int nFlag);
extern void func_ov002_02053cd4(int nId);

void func_ov002_0205cab0(void) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int bRightAlign = (s->bDefaultKind == 0);
    Ov002PanelSubEntry *pEntry;
    int nKey;
    int nColour;

    func_ov002_020535a4(func_ov002_02053558(0x65));

    pEntry = s->pCachedEntry;
    nKey = pEntry->nKey;
    if (pEntry->pObject != 0 &&
        func_ov002_0205a714(0, nKey) != 0 &&
        func_ov002_0205a730(0, nKey) != 0) {
        nColour = 0xf;
    } else {
        nColour = 0xe;
    }

    func_ov002_0205ad5c(3, 0, (u16)(func_ov002_0205a540(nKey) * 0x10 + 0x250),
                        0xf, 0);
    func_ov002_0205ad5c(4, 0, 0x3e0, (u16)nColour, bRightAlign);
    func_ov002_0205ad5c(5, 0, 0x3f0, 0xf, bRightAlign == 0);
    func_ov002_0205abe0(4, bRightAlign != 0 ? PANEL_SIDE_LEFT : PANEL_SIDE_RIGHT, 0);
    func_ov002_0205abe0(5, bRightAlign != 0 ? PANEL_SIDE_RIGHT : PANEL_SIDE_LEFT, 0);
    func_ov002_02053cd4(9);
}
