/* func_ov025_020829f8 -- pick the ov025 idle handler from the heap state word.
 * Bit 0 set = busy, no handler. Otherwise flush pending work (func_ov025_02082ba4) when
 * func_ov025_02084370 says so, and return func_ov025_02082a40 only if bit 2 is set.
 *
 * The lever that closed this one (it was parked as a "one-byte predication tie"): the ROM
 * materialises the 0 UNCONDITIONALLY between the `tst` and the `popne`, where mwcc predicates
 * it (`movne r0,#0`). That constant is doing double duty -- it is both the early return value
 * and r0 for the call that immediately follows the conditional return, which is what forces it
 * above the branch. func_ov025_02084370 is defined `(void)` and ignores it, so the declaration
 * here is the K&R one the original translation unit must have used. A constant hoisted above a
 * branch is the arity smell, not a predication tie. */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_ov025_02084370();
extern void func_ov025_02082ba4(int arg);
extern void func_ov025_02082a40(void);

int func_ov025_020829f8(void) {
    unsigned int *state = (unsigned int *)NNSi_FndGetCurrentRootHeap();
    if ((*state & 1) != 0) {
        return 0;
    }
    if (func_ov025_02084370(0) != 0) {
        func_ov025_02082ba4(0);
    }
    if ((*state & 4) != 0) {
        return (int)func_ov025_02082a40;
    }
    return 0;
}
