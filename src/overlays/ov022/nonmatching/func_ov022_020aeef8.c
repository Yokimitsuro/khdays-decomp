/*
 * [nonmatching: 1-register coloring tie — 88B, structurally byte-identical]
 *
 * Looks up a state slot for (byte@arg0+9 - 1), forces state 9->1, calls
 * func_ov022_020aef50 with a scratch buffer, and on a nonzero result sets the
 * slot back to 9.
 *
 * The ONLY divergence: the trailing `if (result != 0) *p = 9;` — the original
 * materializes the constant 9 in r1 (`movne r1,#9; strne r1,[r4]`), keeping the
 * tested result in r0; mwcc 3.0/139 instead reuses r0 for the constant
 * (`movne r0,#9; strne r0,[r4]`). Every other byte matches. Neither inlining the
 * call in the `if` nor a named result temp steers the constant onto r1 — a pure
 * register-allocation tie, left uncarved (byte-exact in the blob).
 */
extern int *func_020358a4(int arg0);
extern int func_ov022_020aef50(int arg0, int arg1, unsigned int *arg2);

void func_ov022_020aeef8(int arg0, int arg1, int arg2, int arg3) {
    unsigned int buf[3];
    int *p = func_020358a4((*(unsigned char *)(arg0 + 9) - 1) & 0xff);
    if (*p == 9) *p = 1;
    if (func_ov022_020aef50(arg0, arg1, buf) != 0) *p = 9;
}
