/* func_ov008_0204eb88 -- run the menu per-frame input and report a ready transition, ov008.
 * Ticks the menu input/state (func_ov008_0204d564); the transition check
 * (func_ov008_0207dcc0) returns a result code, and only codes 1 (confirm) or 2 (cancel)
 * hand off to the next state function; anything else stays put (0).
 *
 * The non-zero test is a separate guard around a two-label switch. Folding it into one
 * condition lets mwcc prove the zero test redundant and drops an instruction; writing the
 * hand-off as the switch body is also what keeps it inline with the 0 return out of line. */
extern void func_ov008_0204d564(void);
extern int  func_ov008_0207dcc0(void);
extern void func_ov008_0204eadc(void);

void *func_ov008_0204eb88(void) {
    int r;

    func_ov008_0204d564();
    r = func_ov008_0207dcc0();
    if (r != 0) {
        switch (r) {
        case 1:
        case 2:
            return (void *)func_ov008_0204eadc;
        }
    }
    return 0;
}
