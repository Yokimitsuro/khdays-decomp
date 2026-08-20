extern int func_ov002_0207285c(int slot);
extern char *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void func_ov002_0206ffa4(void);
extern char data_0204c240;

static inline void Ov002_SetSlot(void **slot, void *value) {
    if ((int)value != ~0) {
        *slot = value;
    }
}

/* Allocate a script-callback record: resolve the model id (-1 = no slot,
 * -2 = unresolved), store the caller's tag in whichever half the flags select,
 * and fill the three handler slots.
 *
 * Two forms here are load-bearing. The sentinel test lives in a static inline
 * helper because writing the three comparisons open lets mwcc decide them at
 * compile time and fold the stores, losing 12 bytes. And the sentinel is
 * spelled (int)value != ~0 rather than value != (void *)-1: with the pointer
 * form mwcc derives -1 from the compared value with a subs, where the original
 * builds it independently with movs plus mvns and materialises a fresh zero for
 * the last store.
 *
 * The tag conversion must not be cast to short in either arm; the ternary then
 * has short type and mwcc re-extends it before the strh. */
char *func_ov002_02070110(int kind, int tag, int slot, void *ctx) {
    char *rec = NNSi_FndAllocFromDefaultExpHeap(0x18);
    int id;
    rec[0x14] = (char)kind;
    if (slot >= 0) {
        id = func_ov002_0207285c(slot);
        if (id < 0) {
            rec[0x15] = (char)~1;
        } else {
            rec[0x15] = (char)id;
        }
    } else {
        rec[0x15] = (char)~0;
    }
    *(short *)(rec + 0x16) = (*(unsigned char *)&data_0204c240 & 4) != 0
        ? (tag >> 0x10) : (unsigned short)tag;
    *(void **)(rec + 0xc) = ctx;
    Ov002_SetSlot((void **)rec, (void *)&func_ov002_0206ffa4);
    Ov002_SetSlot((void **)(rec + 4), 0);
    Ov002_SetSlot((void **)(rec + 8), 0);
    return rec;
}
