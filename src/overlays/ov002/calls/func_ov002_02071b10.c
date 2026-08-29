typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

/* One entry of a code entry's item list. */
typedef struct Ov002CodeItem {
    u8 nCode;
    char pad001[3];
    u16 nFlags;                 /* bit 1 says the item counts toward the row */
    char pad006[2];
} Ov002CodeItem;

typedef struct Ov002CodeEntry {
    char pad000[1];
    s8 nItems;                  /* 0x01 */
    char pad002[0x1a];
    Ov002CodeItem *pItems;      /* 0x1c */
} Ov002CodeEntry;

typedef struct Ov002CodeTable {
    u8 nEntries;
    char pad001[3];
    Ov002CodeEntry *aEntries[8];    /* 0x04 */
} Ov002CodeTable;

typedef struct Ov002CodeBase {
    char pad000[4];
    Ov002CodeTable *pTable;     /* 0x04 */
    int nOrder;                 /* 0x08 */
    char pad00c[0x23];
    s8 aSlots[4];               /* 0x2f, -1 when the slot picked nothing */
    char pad033[0x49];
    int aResolved[4][8];        /* 0x7c */
    s8 aCount[4];               /* 0xfc */
} Ov002CodeBase;

extern Ov002CodeBase *data_ov002_0207fa10;

/* Resolve one item code to whatever the base wants to hold for it. */
extern int func_ov002_020711d0(int nCode);

/* Rebuild the resolved rows of all four slots.
 *
 * Each slot picks one code entry, and every item of that entry whose flag bit
 * 1 is up is resolved and appended to the slot's own eight-wide row.  A slot
 * that picked nothing, or one whose entry is empty, simply ends up with an
 * empty row.
 */
void func_ov002_02071b10(void)
{
    Ov002CodeEntry *pEntry;
    Ov002CodeItem *pItem;
    int i;
    Ov002CodeBase *pBase;
    int j;
    int nSlot;

    pBase = data_ov002_0207fa10;
    for (i = 0; i < 4; i++) {
        nSlot = data_ov002_0207fa10->aSlots[i];
        pBase->aCount[i] = 0;
        if (nSlot >= 0) {
            pEntry = data_ov002_0207fa10->pTable->aEntries[nSlot];
            for (j = 0; j < pEntry->nItems; j++) {
                pItem = &pEntry->pItems[j];
                if ((pItem->nFlags & 2) != 0) {
                    pBase->aResolved[i][pBase->aCount[i]] =
                        func_ov002_020711d0(pItem->nCode);
                    pBase->aCount[i]++;
                }
            }
        }
    }
}
