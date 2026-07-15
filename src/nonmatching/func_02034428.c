/* NONMATCHING: semantics correct, return-block layout tie (48B vs 50B). The ROM
 * branches over the return-0 block to a separate return-1 (`beq ret0; stores; b
 * ret1; ret0:0; ret1:1`); mwcc 3.0/139 lets the stores fall through into return 1
 * and drops the extra `b` (both the guard-return and positive-if forms optimize it).
 *
 * MsgDb record alloc/init: if keep>=0 allocate a `size`-byte record; then if the
 * record exists, write rec[0]=(short)keep, rec[2]=kind, rec+4=0, rec+8=0. The
 * record pointer (*rec_out) is re-read per store. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
int func_02034428(int *rec_out, unsigned int size, short kind, int keep) {
    if (keep >= 0) {
        *rec_out = (int)NNSi_FndAllocFromDefaultExpHeap(size);
    }
    if (*rec_out == 0) {
        return 0;
    }
    *(short *)*rec_out = (short)keep;
    *(short *)(*rec_out + 2) = kind;
    *(int *)(*rec_out + 4) = 0;
    *(int *)(*rec_out + 8) = 0;
    return 1;
}
