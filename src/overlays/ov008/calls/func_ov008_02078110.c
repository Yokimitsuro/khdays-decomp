/* If the object has no active handle (+0x158 and +0x180 both zero) and both
 * counters at +0x17a/+0x178 exceed 1, kick off the transition (mode 1). */
extern void func_ov008_020779e8(int obj, int mode);
extern void func_02033b78(int a, int b);

void func_ov008_02078110(int param_1) {
    if (*(int *)(param_1 + 0x158) == 0 && *(int *)(param_1 + 0x180) == 0 &&
        *(unsigned char *)(param_1 + 0x17a) > 1 && *(unsigned char *)(param_1 + 0x178) > 1) {
        func_ov008_020779e8(param_1, 1);
        func_02033b78(0, 2);
    }
}
