/*
 * [nonmatching: store-address scheduling tie — 52B, structurally byte-identical]
 *
 * On the global node (data_ov022_020b2e74), when state byte[0xc0] is 0 or 6:
 * if byte[0xc3] differs from arg0, writes arg0 there and sets state[0xc0]=1;
 * otherwise sets state[0xc0]=3.
 *
 * The byte at +0xc3 is read via register-offset (THUMB ldrsb has no immediate
 * form) and written via a computed address (strb's 5-bit offset can't reach
 * 0xc3). The original computes that store address INSIDE the taken branch (after
 * the `beq`); mwcc 3.0/139 hoists the `add p,#0xc3` above the compare regardless
 * of source form (inline, value-temp, or an explicit `char *q` in the branch).
 * Same instructions, only their order differs — an unsteerable scheduler tie.
 * Left uncarved (byte-exact in the blob).
 */
extern int data_ov022_020b2e74;

void func_ov022_02086ec0(int arg0) {
    int p = *(int *)&data_ov022_020b2e74;
    if (*(char *)(p + 0xc0) == 0 || *(char *)(p + 0xc0) == 6) {
        if (*(char *)(p + 0xc3) != arg0) {
            *(char *)(p + 0xc3) = (char)arg0;
            *(unsigned char *)(p + 0xc0) = 1;
            return;
        }
        *(unsigned char *)(p + 0xc0) = 3;
    }
}
