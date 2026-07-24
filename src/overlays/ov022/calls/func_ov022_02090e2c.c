/* func_ov022_02090e2c -- run one pass of the per-slot handler over an object's slot array.
 *
 * The object holds the slot array at +0xc (stride 0x1c8), its length at +0x19 (a byte) and
 * the current mode at +4.  Each slot carries a signed handler tag at +2; a zero tag means
 * "nothing to do".  The tag indexes one of two handler tables, picked by the mode, and the
 * handler is called with (object, slot, param_2).
 *
 * CODEGEN NOTE -- the dispatch has to be a plain array subscript on a typed table
 * (`table[tag](...)`), not `(*(Fn *)((int)&table + tag * 4))(...)`.  Both compute the same
 * address, but with the hand-written cast mwcc colours the two hoisted table bases into
 * r6/r7 and the loop counters into r4/r5, i.e. the exact mirror image of the ROM; written as
 * an array the bases take r4/r5 and the counters r6/r7.  The `i * 0x1c8` offset is left to
 * strength reduction -- an explicit accumulator local compiles to the same stream.
 */
typedef void (*Ov022SlotFn)(int obj, int slot, int arg);

extern Ov022SlotFn data_ov022_020b2b48[];
extern Ov022SlotFn data_ov022_020b2b58[];

void func_ov022_02090e2c(int param_1, int param_2) {
    int i = 0;
    if (0 < (int)*(unsigned char *)(param_1 + 0x19)) {
        do {
            int slot = *(int *)(param_1 + 0xc) + i * 0x1c8;
            int tag = *(char *)(slot + 2);
            if (tag != 0) {
                switch (*(int *)(param_1 + 4)) {
                case 1:
                    data_ov022_020b2b48[tag](param_1, slot, param_2);
                    break;
                case 2:
                    data_ov022_020b2b58[tag](param_1, slot, param_2);
                    break;
                }
            }
            i = i + 1;
        } while (i < (int)*(unsigned char *)(param_1 + 0x19));
    }
}
