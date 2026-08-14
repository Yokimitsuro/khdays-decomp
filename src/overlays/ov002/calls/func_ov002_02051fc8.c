/* Tear down a set of resource tables.
 *
 * Does nothing when the count at +0x50 is zero, which is the never-allocated case. Otherwise it
 * walks the tables at +0x4c with stride 0x24, hands each to func_0202a440 (FreeAllResourceTables)
 * and frees the matching heap block from the pointer array at +0x18, then frees the table array.
 *
 * This is the most widely called unresolved symbol the overlay had: 37 already matched sources
 * reference it, from ov002 itself and from the whole enemy overlay family between ov030 and ov046,
 * always on a scene teardown path.
 *
 * Arity note. Several callers, func_ov030_020b3310 among them, declare this with TWO arguments and
 * pass a second sub-object. The ROM never reads r1, so that argument is ignored and this definition
 * takes one parameter.
 *
 * Codegen note. The ROM tests the count TWICE, once for the early return and again as the loop
 * guard, and initialises the byte offset only after that second test. A plain for loop after the
 * early return folds the two tests together and comes out four bytes short; every one of the
 * obvious loop spellings does. The shape that matches is the explicit zero test, then a positive
 * guard, then a do-while.
 *
 * Ghidra carries this as Ov002_FreeResourceTables over Ov002TableSet.
 */

typedef struct {
    char pad0000[0x18];
    void *apBlocks[1];      /* +0x18, one heap block per table */
    char pad001c[0x30];
    char *pTables;          /* +0x4c, stride 0x24 */
    int nTableCount;        /* +0x50 */
} Ov002TableSet;

extern void func_0202a440(void *table);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov002_02051fc8(Ov002TableSet *self) {
    int i;
    int off;

    if (self->nTableCount == 0) {
        return;
    }
    i = 0;
    if (0 < self->nTableCount) {
        off = 0;
        do {
            func_0202a440(self->pTables + off);
            NNSi_FndFreeFromDefaultHeap(self->apBlocks[i]);
            i++;
            off += 0x24;
        } while (i < self->nTableCount);
    }
    NNSi_FndFreeFromDefaultHeap(self->pTables);
}
