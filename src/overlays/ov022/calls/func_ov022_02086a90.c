/* * Was parked as a "64-bit divide/compare runtime helper -- deferred class", with a paragraph
 * about mwcc's lowering of "the widening, the r0:r1 split, and the multi-word compare". Nothing
 * about the 64-bit lowering was wrong. Three ordinary bugs were (2026-07-17):
 *   - it returned 1 instead of the FUNCTION POINTER func_ov022_02086ae4 (the missing `ldr r5,[pc]`
 *     was the 4 bytes it was short). The file's own prose said "returns func_ov022_02086ae4 when
 *     the comparison holds" -- the code just did not.
 *   - the divisor is 0x82ea, not 0x2710. Read the pool.
 *   - func_02020368 takes a `long long` FIRST argument (r0:r1) plus divisor and flag -- three C
 *     args, four registers. Splitting the value into (lo, hi) by hand is what made the arity look
 *     like 4 and the call look exotic. The rest of the tree already spells it the plain way.
 * Also: `limit` is sign-extended to 64 bits and then compared UNSIGNED (`asrs` + `bhs`), which is
 * `q > (unsigned long long)(long long)limit` -- a signed widen feeding an unsigned compare.
 *
 * When data_0204be04 is clear, divides a widened tick count by 0x82ea and, if the result exceeds
 * the heap's threshold at +0xc4 plus 100, returns func_ov022_02086ae4 for the caller to run.
 * Always finishes with func_ov022_02086d60(0x10000).
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern long long func_020031d4(void);
extern unsigned long long func_02020368(long long value, int divisor, int flag);
extern void func_ov022_02086d60(int arg0);
extern int func_ov022_02086ae4(void);
extern int data_0204be04;

int func_ov022_02086a90(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    unsigned long long q;
    int limit;
    int ret = 0;

    if (*(unsigned char *)&data_0204be04 != 0) {
        return 0;
    }
    q = func_02020368(func_020031d4() << 6, 0x82ea, 0);
    limit = *(int *)(h + 0xc4) + 100;
    if (q > (unsigned long long)(long long)limit) {
        ret = (int)func_ov022_02086ae4;
    }
    func_ov022_02086d60(0x10000);
    return ret;
}
