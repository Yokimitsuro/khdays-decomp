/*
 * NONMATCHING (register-coloring tie, size-exact byte-diff @0x15). Everything
 * matches after: typed ((int*)param_3)[i+3] indexing to defeat the induction-
 * pointer SR; `int param_4` narrowed via `(short)param_4` (a `short` param is
 * assumed pre-sign-extended so it wouldn't emit the lsl/asr); unsigned-short
 * call params so `i` re-masks per call instead of being CSE'd into a reg. The
 * only remaining divergence is which of r5/r6 holds p4=(short)param_4 vs the
 * hoisted clear-zero (orig p4=r5/zero=r6, mwcc p4=r6/zero=r5). Tried decl-order
 * swaps of p4 vs i. Pure coloring; byte-equivalent.
 *
 * for(i<5){ if(*(int)(p3+i*4+0xc)!=0){ func_02014dc4(p3+0x20, that); *(int)(...)=0; }
 *   func_0202accc(p3, i, arg1, (short)arg3); func_01fff774(p3, i, 0); }
 */
extern void func_02014dc4(unsigned int *a, int b);
extern void func_0202accc(int a, unsigned short i, int c, int d);
extern void func_01fff774(unsigned short *a, unsigned short i, int c);

void func_ov022_0208a8bc(int param_1, int param_2, unsigned short *param_3, int param_4) {
    int p4 = (short)param_4;
    unsigned int i = 0;
    do {
        if (((int *)param_3)[i + 3] != 0) {
            func_02014dc4((unsigned int *)(param_3 + 0x10), ((int *)param_3)[i + 3]);
            ((int *)param_3)[i + 3] = 0;
        }
        func_0202accc((int)param_3, i, param_2, p4);
        func_01fff774(param_3, i, 0);
        i = i + 1;
    } while ((int)i < 5);
}
