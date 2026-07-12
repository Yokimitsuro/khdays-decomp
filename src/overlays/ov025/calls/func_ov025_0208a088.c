/* Recompute the cached value at (param_1)+0x10 from the source at +0x14 using the selector
 * param_2 (0-7) to pick the per-kind conversion; out-of-range selectors are ignored. */
extern int func_ov025_02089f00(int a, int b);
extern int func_ov025_02089f14(int a, int b);
extern int func_ov025_02089fc4(int a, int b);
extern int func_ov025_02089fb0(int a, int b);
extern int func_ov025_02089fd8(int a, int b);
extern int func_ov025_02089fec(int a, int b);
extern int func_ov025_0208a000(int a, int b);
extern int func_ov025_0208a014(int a, int b);
void func_ov025_0208a088(int param_1, int param_2) {
    switch (param_2) {
        case 0: *(short *)(param_1 + 0x10) = func_ov025_02089f00(param_1, *(int *)(param_1 + 0x14)); break;
        case 1: *(short *)(param_1 + 0x10) = func_ov025_02089f14(param_1, *(int *)(param_1 + 0x14)); break;
        case 2: *(short *)(param_1 + 0x10) = func_ov025_02089fc4(param_1, *(int *)(param_1 + 0x14)); break;
        case 3: *(short *)(param_1 + 0x10) = func_ov025_02089fb0(param_1, *(int *)(param_1 + 0x14)); break;
        case 4: *(short *)(param_1 + 0x10) = func_ov025_02089fd8(param_1, *(int *)(param_1 + 0x14)); break;
        case 5: *(short *)(param_1 + 0x10) = func_ov025_02089fec(param_1, *(int *)(param_1 + 0x14)); break;
        case 6: *(short *)(param_1 + 0x10) = func_ov025_0208a000(param_1, *(int *)(param_1 + 0x14)); break;
        case 7: *(short *)(param_1 + 0x10) = func_ov025_0208a014(param_1, *(int *)(param_1 + 0x14)); break;
    }
}
