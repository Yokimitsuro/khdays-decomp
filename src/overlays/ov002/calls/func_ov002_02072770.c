/*
 * Finds which entry owns a code, and reports where it was found.
 *
 * The four slots are searched first, in order, skipping the ones that hold
 * nothing; a hit there reports the slot's position and the entry it holds.
 * Failing that the whole table is searched, and a hit there reports no slot
 * and the entry's own index instead. No hit anywhere is zero.
 *
 * Three things here are load-bearing rather than style.
 *
 * The slot scan walks a byte pointer alongside its counter, both stepped in
 * the for statement with the pointer first. Written as an indexed read the
 * function comes out four bytes short, and stepping the counter first costs
 * far more than that.
 *
 * The item code is read into a local before it is compared. Compared in place
 * the compiler puts the wanted code first in the compare, and the original
 * puts the item's; it is the same test either way, but not the same two bytes.
 *
 * The item is reached by index off the entry rather than through a pointer of
 * its own, so the compiler's own strength reduction places the base load after
 * the loop's zero-trip guard, where the original has it.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002Item {
    u8 nCode;
    char pad1[7];
} Ov002Item;

typedef struct Ov002Entry {
    char pad0[1];
    s8 nCount;
    char pad2[0x1a];
    Ov002Item *pItems;
} Ov002Entry;

typedef struct Ov002Table {
    u8 nEntries;
    char pad1[3];
    Ov002Entry *aEntries[8];
} Ov002Table;

typedef struct Ov002Base {
    char pad0[4];
    Ov002Table *pTable;
    char pad8[0x27];
    s8 aSlots[4];
} Ov002Base;

extern Ov002Base *data_ov002_0207fa10;

int func_ov002_02072770(int nCode, int *pOutSlot, int *pOutIndex)
{
    Ov002Base *pBase;
    Ov002Table *pTable;
    Ov002Entry *pEntry;
    int i;
    int j;
    int nSlot;
    s8 *pWalk;
    int nItem;

    pBase = data_ov002_0207fa10;
    for (i = 0, pWalk = (s8 *)pBase; i < 4; pWalk++, i++) {
        nSlot = pWalk[0x2f];
        if (nSlot >= 0) {
            pEntry = pBase->pTable->aEntries[nSlot];
            for (j = 0; j < pEntry->nCount; j++) {
                nItem = pEntry->pItems[j].nCode;
                if (nItem == nCode) {
                    *pOutSlot = i;
                    *pOutIndex = nSlot;
                    return 1;
                }
            }
        }
    }

    pTable = pBase->pTable;
    for (i = 0; i < pTable->nEntries; i++) {
        pEntry = pTable->aEntries[i];
        for (j = 0; j < pEntry->nCount; j++) {
            nItem = pEntry->pItems[j].nCode;
            if (nItem == nCode) {
                *pOutSlot = -1;
                *pOutIndex = i;
                return 1;
            }
        }
    }
    return 0;
}
