/*
 * Ov002_PanelRestoreGroupRows - put the four group rows back from the copy the
 * game state kept.
 *
 * Every row is emptied first, so a saved entry that no longer resolves simply
 * stays empty. A saved group 3 is only restored while its key still names a
 * slot inside the current slot count, and a saved group 8 only while one of
 * the fifteen cells still carries its key - and that test walks all fifteen
 * rather than stopping at the first hit, which is the ROM's own behaviour.
 *
 * The one mode that owns its own rows is asked to rebuild them afterwards.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[1];
    u8 bMode;                           /* +0x001 */
    u8 pad0002[0x30];
    u8 aCells[0x1e];                    /* +0x032 */
    u8 pad0050[0x45e];
    u16 wSlotCount;                     /* +0x4ae */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;
extern int data_0204be18;

extern int func_ov002_0205a540(unsigned int nKey);
extern void func_ov002_0205ba3c(int nRow, unsigned int nGroup,
                                unsigned int nKey);
extern void func_ov002_0205c9c4(void);

void func_ov002_0205ca00(void)
{
    Ov002PanelSession *s;
    int i;
    int j;
    int nOff;
    int k;
    Ov002PanelSession *pWalk;
    int nSlot;

    s = data_ov002_0207f620;
    for (i = 0; i < 4; i++) {
        func_ov002_0205ba3c(i, 7, 0);
    }

    /* The byte offset of the saved row is walked rather than multiplied out:
       with two plain terms mwcc keeps the order of the sum as written, which is
       what puts the offset ahead of the base inside the group 8 test. */
    for (j = 0, nOff = 0; j < 4; j++, nOff += 4) {
        switch (*(u16 *)(data_0204be18 + nOff + 0xfd0)) {
        case 8:
            pWalk = s;
            for (k = 0; k < 0xf; k++) {
                if (pWalk->aCells[0] == *(u16 *)(nOff + data_0204be18 + 0xfd2)) {
                    func_ov002_0205ba3c(j, 8,
                                        *(u16 *)(data_0204be18 + nOff
                                                 + 0xfd2));
                }
                pWalk = (Ov002PanelSession *)((char *)pWalk + 2);
            }
            break;
        case 3:
            nSlot = func_ov002_0205a540(
                *(u16 *)(data_0204be18 + nOff + 0xfd2));
            if (nSlot >= 0 && nSlot < s->wSlotCount) {
                func_ov002_0205ba3c(j, 3,
                                    *(u16 *)(data_0204be18 + nOff + 0xfd2));
            }
            break;
        }
    }

    if (s->bMode == 9) {
        func_ov002_0205c9c4();
    }
}
