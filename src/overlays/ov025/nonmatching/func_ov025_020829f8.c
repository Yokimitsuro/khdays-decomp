/* NONMATCHING: one-byte predication tie — the ROM materialises the 0 return unconditionally
 * (`tst r0,#1; mov r0,#0; ldmne`), mwcc predicates it (`movne r0,#0`). Everything else matches;
 * a shared `int result = 0` local makes it worse (the value gets held, 76B). */
/* func_ov025_020829f8 -- pick the ov025 idle handler from the heap state word.
 * Bit 0 set = busy, no handler. Otherwise flush pending work (func_ov025_02082ba4) when
 * func_ov025_02084370 says so, and return func_ov025_02082a40 only if bit 2 is set. */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_ov025_02084370(void);
extern void func_ov025_02082ba4(int arg);
extern void func_ov025_02082a40(void);

int func_ov025_020829f8(void) {
    unsigned int *state = (unsigned int *)NNSi_FndGetCurrentRootHeap();
    if ((*state & 1) != 0) {
        return 0;
    }
    if (func_ov025_02084370() != 0) {
        func_ov025_02082ba4(0);
    }
    if ((*state & 4) != 0) {
        return (int)func_ov025_02082a40;
    }
    return 0;
}
