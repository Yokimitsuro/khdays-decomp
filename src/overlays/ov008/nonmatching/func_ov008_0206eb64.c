/* Draw a page-B element while the gate at data_02090f20 is set, passing a pointer to a two-word
 * extra-argument block (param_3, param_4) as the draw's 5th argument; returns 1 when drawn, else 0.
 *
 * NON-MATCHING. The home-save of the incoming args (stmdb {r0-r3}), the gate check, and the call
 * shape are right. Residue: the ROM builds the extra-arg pointer with a varargs-style aligned
 * computation (add sp,#N; bic #3; add #4) and re-reads param_2 from the home-save area, i.e. this
 * was almost certainly written with a `...` parameter and va_start(ap, param_2). The plain
 * `&param_3` spelling below produces an unaligned direct `add sp,#N` and caches param_2 in a
 * callee-saved register instead; a <stdarg.h> va_start spelling fails to compile under our headers.
 * Left as the readable equivalent. */
extern int func_ov008_02050cec(void);
extern void func_ov008_0206d46c(int page, int p1, int a, int p2, void *pExtra, int one);
extern int *data_ov008_02090f20;

int func_ov008_0206eb64(int param_1, int param_2, unsigned int param_3, int param_4) {
    int page = func_ov008_02050cec();
    if (*data_ov008_02090f20 != 0) {
        func_ov008_0206d46c(page, param_1, 0, param_2, &param_3, 1);
        return 1;
    }
    return 0;
}
