/* Recompute the cached value at (param_1)+0x10 from the source at +0x14 using the selector
 * param_2 (0-7) to pick the per-kind conversion; out-of-range selectors are ignored. */
extern int func_ov004_0204d020(int a, int b);
extern int func_ov004_0204d034(int a, int b);
extern int func_ov004_0204d0e4(int a, int b);
extern int func_ov004_0204d0d0(int a, int b);
extern int func_ov004_0204d0f8(int a, int b);
extern int func_ov004_0204d10c(int a, int b);
extern int func_ov004_0204d120(int a, int b);
extern int func_ov004_0204d134(int a, int b);
void func_ov004_0204d1a8(int param_1, int param_2) {
    switch (param_2) {
        case 0: *(short *)(param_1 + 0x10) = func_ov004_0204d020(param_1, *(int *)(param_1 + 0x14)); break;
        case 1: *(short *)(param_1 + 0x10) = func_ov004_0204d034(param_1, *(int *)(param_1 + 0x14)); break;
        case 2: *(short *)(param_1 + 0x10) = func_ov004_0204d0e4(param_1, *(int *)(param_1 + 0x14)); break;
        case 3: *(short *)(param_1 + 0x10) = func_ov004_0204d0d0(param_1, *(int *)(param_1 + 0x14)); break;
        case 4: *(short *)(param_1 + 0x10) = func_ov004_0204d0f8(param_1, *(int *)(param_1 + 0x14)); break;
        case 5: *(short *)(param_1 + 0x10) = func_ov004_0204d10c(param_1, *(int *)(param_1 + 0x14)); break;
        case 6: *(short *)(param_1 + 0x10) = func_ov004_0204d120(param_1, *(int *)(param_1 + 0x14)); break;
        case 7: *(short *)(param_1 + 0x10) = func_ov004_0204d134(param_1, *(int *)(param_1 + 0x14)); break;
    }
}
