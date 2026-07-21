/* Search up to 12 candidate cells: starting from the byte at +0x54 plus param_2, repeatedly form
 * x = cell + 12, reduce it mod 12, offer (x%12, high word of (x/12)*12, x, param_4) to
 * func_ov008_0205b720, and return x%12 as soon as func_ov008_0205b708 accepts it; otherwise step
 * the cell by param_2 and retry, finally returning the original +0x54 byte.
 *
 * NON-MATCHING. Semantics are right but two codegen details diverge. (1) The ROM computes the
 * 64-bit product (x/12)*12 with a single signed `smull` (it needs the high word as arg 2), while
 * mwcc 139 lowers `(long long)(x/12) * 12` to umull + two mla + asr. (2) The ROM keeps param_4 in
 * r3 across the two calls without reloading (relying on the callees preserving r3), whereas mwcc
 * parks param_4 in a callee-saved register and re-issues `mov r3, saved` before each call. Both
 * are compiler-era behaviours no source spelling reproduces under our flags. */
extern void func_ov008_0205b720(int a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned short func_ov008_0205b708(void);

unsigned int func_ov008_0206fce0(int param_1, int param_2, unsigned int param_3, unsigned int param_4) {
    int base = *(unsigned char *)(param_1 + 0x54) + param_2;
    int i = 0;
    do {
        int x = base + 0xc;
        long long prod = (long long)(x / 12) * 12;
        int mod = x - (int)prod;
        func_ov008_0205b720(mod & 0xffff, (unsigned int)(int)((unsigned long long)prod >> 32), x, param_4);
        if (func_ov008_0205b708() != 0) {
            return mod;
        }
        base = mod + param_2;
        i++;
    } while (i < 0xc);
    return *(unsigned char *)(param_1 + 0x54);
}
