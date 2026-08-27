/*
 * Commits a chosen slot value and tells the rest of the panel about it.
 *
 * The four table words are copied into a local array rotated by two, so the two
 * call sites can read it as a pair of pairs: the sound id from the first pair at
 * the index, and the value handed on from the second pair at the same index.
 * When the flag is set a sound starts first and its handle travels with the
 * value, and the extra step runs afterwards. The flag is remembered on the
 * context only when the context's own slot belongs to the local player.
 *
 * Three things here are load-bearing rather than style.
 *
 * The pointer to the first pair is taken before anything else in the body. That
 * is what puts the frame address ahead of the slot table's own address in the
 * schedule; taking it later swaps those two instructions.
 *
 * The slot entry pointer is taken early, before the calls, which is what lets
 * the index multiply happen once at the top and survive in a register across
 * them rather than being recomputed at the store.
 *
 * The second pair is reached through its own pointer rather than by indexing at
 * two plus the index, which would cost an extra add at the call site.
 *
 * ARM.
 */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SlotContext {
    char pad000[4];
    int nSlot;
    char pad008[0x20];
    int bFlag;
} Ov002SlotContext;

typedef struct Ov002SlotEntry {
    int nValue;
    char pad004[0x10];
} Ov002SlotEntry;

extern Ov002SlotContext *data_ov002_0207f99c;
extern const u32 data_ov002_0207e424[];
extern Ov002SlotEntry data_ov002_0207f9a0[];

extern int func_ov002_02053558(int nSound);
extern void func_ov002_020658c8(int nValue, int hSound);
extern void func_ov002_02066c84(int nIndex);
extern u16 func_02030788(void);

void func_ov002_02065940(int nIndex, int bFlag)
{
    Ov002SlotContext *pCtx;
    Ov002SlotEntry *pEntry;
    u32 *pFirst;
    u32 *pSecond;
    u32 aLocal[4];
    int hSound;

    pFirst = &aLocal[0];
    pCtx = data_ov002_0207f99c;
    pEntry = &data_ov002_0207f9a0[pCtx->nSlot];
    aLocal[2] = data_ov002_0207e424[0];
    aLocal[3] = data_ov002_0207e424[1];
    aLocal[0] = data_ov002_0207e424[2];
    aLocal[1] = data_ov002_0207e424[3];

    hSound = 0;
    if (bFlag != 0) {
        hSound = func_ov002_02053558((u16)pFirst[nIndex]);
    }
    pSecond = &aLocal[2];
    func_ov002_020658c8(pSecond[nIndex], hSound);
    if (bFlag != 0) {
        func_ov002_02066c84(nIndex);
    }

    if ((u32)pCtx->nSlot == (u32)func_02030788()) {
        pCtx->bFlag = bFlag;
    }
    pEntry->nValue = nIndex;
}
