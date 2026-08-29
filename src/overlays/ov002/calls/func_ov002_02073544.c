typedef unsigned char u8;

typedef struct Ov107Object Ov107Object;

typedef struct Ov002ObjectSlot {
    Ov107Object *pObject;           /* +0x00 */
    u8 gap0004[0x10];
    signed char bEntryIndex;        /* +0x14 */
    u8 gap0015;
    signed char bField16;           /* +0x16, cleared with the other two */
    signed char nSourceIndex;       /* +0x17 */
} Ov002ObjectSlot;                  /* 0x18 */

typedef struct Ov002ObjectContext {
    u8 gap0000[0x44];
    Ov002ObjectSlot *pSlots;        /* +0x44 */
    u8 nSlotsInUse;                 /* +0x48 */
    u8 nSlotCount;                  /* +0x49 */
    u8 gap004a[2];
    short *pSlotLookup;             /* +0x4c */
    u8 nLookupCount;                /* +0x50 */
    u8 nLookupInUse;                /* +0x51 */
} Ov002ObjectContext;

extern Ov002ObjectContext *data_ov002_0207fa14;

extern void *NNSi_FndAllocFromDefaultExpHeap(int nSize);
extern void MI_CpuFill8(void *pDst, int nValue, int nSize);

/* Allocate and prime the object context's two tables: a slot table of the
 * first size and a lookup table of the second.  The slots start zeroed with
 * their three index bytes set to -1, the lookup table starts all ones, and
 * both sizes are latched with their companion byte cleared.
 *
 * Worth noting for a later pass: this initialiser puts the allocated count in
 * +0x48 and zero in +0x49, and the same pattern repeats at +0x50 and +0x51.
 * That reads as capacity followed by running total, which is the opposite way
 * round from the nSlotsInUse / nSlotCount names the tree and Ghidra already
 * carry for the first pair.  The names are left alone here because two matched
 * sources already use them and one initialiser is not enough to overturn that.
 */
void func_ov002_02073544(int nSlotCount, int nLookupCount)
{
    Ov002ObjectContext *pCtx;
    int i;

    pCtx = data_ov002_0207fa14;
    pCtx->pSlots = (Ov002ObjectSlot *)
        NNSi_FndAllocFromDefaultExpHeap(nSlotCount * 0x18);
    pCtx->pSlotLookup = (short *)
        NNSi_FndAllocFromDefaultExpHeap(nLookupCount * 2);

    MI_CpuFill8(pCtx->pSlots, 0, nSlotCount * 0x18);
    MI_CpuFill8(pCtx->pSlotLookup, 0xff, nLookupCount * 2);

    for (i = 0; i < nSlotCount; i++) {
        pCtx->pSlots[i].bEntryIndex = -1;
        pCtx->pSlots[i].bField16 = -1;
        pCtx->pSlots[i].nSourceIndex = -1;
    }

    pCtx->nSlotsInUse = (u8)nSlotCount;
    pCtx->nSlotCount = 0;
    pCtx->nLookupCount = (u8)nLookupCount;
    pCtx->nLookupInUse = 0;
}
