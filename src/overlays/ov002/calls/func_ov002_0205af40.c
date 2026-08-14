/* Find the slot index that serves a group and key, or -1.
 *
 * Scans the four group slots of the session. A slot only counts when its group
 * id matches, and then group 3 compares the key against the slot's literal key
 * while group 8 compares it against the first byte behind the slot's pointer.
 * Any other group can never match, so it always answers -1.
 *
 * The result is the style index the row repaint feeds to its two translation
 * tables, which is why those tables hold exactly four entries.
 *
 * Two codegen notes. The slots are addressed by index rather than through a
 * cached pointer: caching one lets mwcc strength-reduce the loop into a pointer
 * increment, and the ROM recomputes base + i*16 every iteration. And the
 * three-way test is a switch with case 8 written before case 3 -- that source
 * order is what puts the group-8 body in the fall-through and leaves the
 * group-3 body out of line with a predicated return, even though mwcc still
 * emits the comparison against 3 first.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 nGroup;             /* +0x00 */
    u16 pad0002;
    u8 *pKeyRef;            /* +0x04 */
    u8 pad0008[4];
    u16 nKey;               /* +0x0c */
    u16 pad000e;
} Ov002PanelGroupSlot;

typedef struct {
    u8 pad0000[0x440];
    Ov002PanelGroupSlot aGroups[4];   /* +0x440 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

int func_ov002_0205af40(int nGroup, int nKey) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int i = 0;

    do {
        if (nGroup == s->aGroups[i].nGroup) {
            switch (nGroup) {
            case 8:
                if (nKey == *s->aGroups[i].pKeyRef) {
                    return i;
                }
                break;
            case 3:
                if (nKey == s->aGroups[i].nKey) {
                    return i;
                }
                break;
            }
        }
        i++;
    } while (i < 4);
    return -1;
}
