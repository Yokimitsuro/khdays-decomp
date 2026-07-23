/* MsgDb record alloc/init: when `keep` is non-negative allocate a `size`-byte record
 * into *rec_out; then, if a record is present, seed it with the keep flag, the kind,
 * and two zero words, and report success.
 *
 * The two exits are written with gotos because that is what fixes the block layout.
 * The ROM branches over the failure block: guard -> stores -> `b` to the success
 * epilogue, with `return 0` sitting BETWEEN the two. Written as a plain early
 * `return 0`, mwcc lets the stores fall through into `return 1` and drops the extra
 * branch, which is two bytes short. Both the guard-return and the positive-if forms
 * do that; only an explicit `goto` past the failure block reproduces it.
 *
 * The record pointer is re-read from *rec_out for every store, as the ROM does. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);

int func_02034428(int *rec_out, unsigned int size, short kind, int keep) {
    if (keep >= 0) {
        *rec_out = (int)NNSi_FndAllocFromDefaultExpHeap(size);
    }
    if (*rec_out != 0) {
        *(short *)*rec_out = (short)keep;
        *(short *)(*rec_out + 2) = kind;
        *(int *)(*rec_out + 4) = 0;
        *(int *)(*rec_out + 8) = 0;
        goto done;
    }
    return 0;
done:
    return 1;
}
