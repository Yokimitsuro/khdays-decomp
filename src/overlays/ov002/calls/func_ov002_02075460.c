/* Hand the ov022 battle handle over to func_ov002_0204cee0, but only in link
 * states 7 and 1. The state word is re-read for the second comparison instead of
 * being cached -- the ROM calls func_ov002_0206b78c twice, so the source tests it
 * twice; caching it into a local costs the second call and the match.
 *
 * The tail is the same three-call sequence as func_ov002_0207b368: latch the
 * handle first, silence the current entry, then dispatch with follow-up state 1. */
extern int func_ov002_0206b78c(void);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern void func_ov022_02086818(int a, int b);
extern void func_ov002_0204cee0(int a, int b);

void func_ov002_02075460(void) {
    if (func_ov002_0206b78c() == 7 || func_ov002_0206b78c() == 1) {
        int handle = func_ov022_02083f0c();

        func_ov022_02086818(func_ov022_02083f5c(), 0);
        func_ov002_0204cee0(handle, 1);
    }
}
