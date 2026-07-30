/*
 * ResSlot_Release - decrement a resource slot's refcount and free its buffers at zero.
 *
 * Slot table at data_0204c238 (0x14-byte entries). For index param_1 (must be <= 0x20), decrements
 * the refcount (s16 at +0xe); while it stays positive returns 1 (still referenced). At zero it
 * frees the two buffers pBuf0 (+0) and pBuf1 (+4) via NNSi_FndFreeFromDefaultHeap, clears the
 * associated fields, sets +0x10 back to 0x10, and returns 1 if either buffer was actually freed,
 * 0 otherwise. Out-of-range index returns 0.
 *
 * THUMB. The freed flag lives in r1 (0-init, re-set to 1 after each free) and is the return value.
 */

typedef struct {
    int pBuf0;
    int pBuf1;
    int nUnk8;
    short nUnkC;
    short nRefCount;
    int nUnk10;
} ResEntry;

extern ResEntry *data_0204c238;
extern void NNSi_FndFreeFromDefaultHeap(int p);

int func_02034258(int param_1)
{
    int freed = 0;
    ResEntry *e;

    if (param_1 >= 0x21)
        return freed;
    e = &data_0204c238[param_1];
    e->nRefCount = e->nRefCount - 1;
    if (e->nRefCount > 0)
        return 1;
    e->nRefCount = 0;
    if (e->pBuf0 != 0) {
        NNSi_FndFreeFromDefaultHeap(e->pBuf0);
        e->pBuf0 = 0;
        e->nUnkC = 0;
        e->nUnk8 = 0;
        freed = 1;
    }
    if (e->pBuf1 != 0) {
        NNSi_FndFreeFromDefaultHeap(e->pBuf1);
        e->pBuf1 = 0;
        freed = 1;
    }
    e->nUnk10 = 0x10;
    return freed;
}
