/* The mirror of func_ov002_02075460: same link-state gate (7 or 1, with the state
 * word re-read for the second test), same pair of ov022 lookups -- but the two
 * follow-up flags are swapped, so this is the "release" half. Both handles are
 * latched before either call, which is why the ROM burns r4 and r5. */
extern int func_ov002_0206b78c(void);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern void func_ov022_02086818(int a, int b);
extern void func_ov002_0204cee0(int a, int b);

void func_ov002_0207548c(void) {
    if (func_ov002_0206b78c() == 7 || func_ov002_0206b78c() == 1) {
        int handle = func_ov022_02083f0c();
        int entry = func_ov022_02083f5c();

        func_ov002_0204cee0(handle, 0);
        func_ov022_02086818(entry, 1);
    }
}
