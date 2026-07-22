/* func_ov023_02089108 -- bind entry `func_ov023_02089064(a)` of the 0xc-byte table at +0x45c to
 * the handle func_ov023_02089080 resolves from `b`, and mark it live (+8 = 1). */
extern int func_ov023_02089064(int a);
extern int func_ov023_02089080(int b);

void func_ov023_02089108(int a, int b) {
    int *slot = (int *)((a + 0x45c) + func_ov023_02089064(a) * 0xc);
    slot[1] = func_ov023_02089080(b);
    slot[2] = 1;
}
