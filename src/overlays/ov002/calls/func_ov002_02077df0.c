/*
 * Hands a slot's owner back and, for the slots past the fixed block, frees the
 * slot's bit.
 *
 * A slot with no owner is already free. Otherwise the owner is told the slot is
 * going, and released outright once nothing else holds it; either way the slot
 * forgets it. The slot's index comes from its distance down the table, and only
 * indices from thirty-two up have a bit to clear - the ones below live in the
 * fixed block and are not tracked that way.
 *
 * One thing here is load-bearing rather than style. The bit setter takes the
 * index as a second argument. The index is already in that register when the
 * call is reached, so declaring the helper with one argument leaves twenty-three
 * bytes wrong across the whole division: the compiler is free to put the
 * quotient elsewhere and every temporary shifts with it.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov002Owner {
    char pad00[0xc];
    int nRefs;
} Ov002Owner;

typedef struct Ov002Slot {
    char pad00[0x24];
    Ov002Owner *pOwner;
    char pad28[0x34];
} Ov002Slot;

typedef struct Ov002SlotTable {
    char pad00[0x54];
    Ov002Slot *pSlots;
    char pad58[4];
    int *pFreeBits;
} Ov002SlotTable;

extern Ov002SlotTable *data_ov002_0207fa28[];

extern void func_0202c614(Ov002Owner *pOwner, Ov002Slot *pSlot);
extern void func_0202c5e4(Ov002Owner *pOwner);
extern void func_02025640(int *pFreeBits, int nIndex);

void func_ov002_02077df0(Ov002Slot *pSlot)
{
    Ov002Owner *pOwner;
    Ov002SlotTable *pTable;
    int nIndex;

    pOwner = pSlot->pOwner;
    if (pOwner == 0) {
        return;
    }

    func_0202c614(pOwner, pSlot);
    pOwner = pSlot->pOwner;
    if (pOwner->nRefs == 0) {
        func_0202c5e4(pOwner);
    }
    pSlot->pOwner = 0;

    pTable = data_ov002_0207fa28[1];
    nIndex = pSlot - pTable->pSlots;
    if (nIndex >= 0x20) {
        func_02025640(pTable->pFreeBits, nIndex);
    }
}
