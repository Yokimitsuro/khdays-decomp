/* NONMATCHING: register-coloring tie. Structurally identical to the original
 * (load field@+4 and pointer@+0x138, accumulate arg2, store back, guarded
 * clear+state) but mwcc colors the two initial loads into r3/r0 swapped vs the
 * original's r0/r3 (orig: ldr r0,[r1,#4]; ldr r3,[r1,#0x138]; mine swaps them).
 * Everything else matches byte-for-byte. Tried decl reorder and add-operand
 * swap; the swap persists. */
int func_ov022_020915bc(int arg0, int arg1, int arg2) {
    int v = *(int *)(arg1 + 4);
    int *pp = *(int **)(arg1 + 0x138);
    v += arg2;
    *(int *)(arg1 + 4) = v;
    if (v >= pp[7] && *(char *)(arg1 + 2) == 1) {
        *(int *)(arg1 + 4) = 0;
        *(char *)(arg1 + 2) = 2;
    }
    return 0;
}
