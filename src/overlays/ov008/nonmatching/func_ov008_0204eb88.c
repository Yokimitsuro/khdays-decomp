/* NONMATCHING: correct (52B); tail-merge tie -- the ROM branches both null/range checks to a
 * shared return-0 with the DAT return inline; our mwcc reorders which side is inline. Menu
 * per-frame input -> ready-transition test (codes 1/2). */
/* func_ov008_0204eb88 -- run the menu per-frame input and report a ready transition, ov008.
 * Ticks the menu input/state (func_ov008_0204d564); the transition check (func_ov008_0207dcc0)
 * returns a result code, and only codes 1 (confirm) or 2 (cancel) hand off to the next state
 * fn (func_ov008_0204eadc); anything else stays (0). */
extern void func_ov008_0204d564(void);
extern int  func_ov008_0207dcc0(void);
extern void func_ov008_0204eadc(void);

void *func_ov008_0204eb88(void) {
    int r;
    func_ov008_0204d564();
    r = func_ov008_0207dcc0();
    if (r == 0 || (r != 1 && r != 2)) {
        return 0;
    }
    return (void *)func_ov008_0204eadc;
}
