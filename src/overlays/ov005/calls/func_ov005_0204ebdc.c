/* Recompute the cached value at (param_1)+0x10 from the source at +0x14 using the selector
 * param_2 (0-7) to pick the per-kind conversion; out-of-range selectors are ignored. */
extern int func_ov005_0204ea54(int a, int b);
extern int func_ov005_0204ea68(int a, int b);
extern int func_ov005_0204eb18(int a, int b);
extern int func_ov005_0204eb04(int a, int b);
extern int func_ov005_0204eb2c(int a, int b);
extern int func_ov005_0204eb40(int a, int b);
extern int func_ov005_0204eb54(int a, int b);
extern int func_ov005_0204eb68(int a, int b);
void func_ov005_0204ebdc(int param_1, int param_2) {
    switch (param_2) {
        case 0: *(short *)(param_1 + 0x10) = func_ov005_0204ea54(param_1, *(int *)(param_1 + 0x14)); break;
        case 1: *(short *)(param_1 + 0x10) = func_ov005_0204ea68(param_1, *(int *)(param_1 + 0x14)); break;
        case 2: *(short *)(param_1 + 0x10) = func_ov005_0204eb18(param_1, *(int *)(param_1 + 0x14)); break;
        case 3: *(short *)(param_1 + 0x10) = func_ov005_0204eb04(param_1, *(int *)(param_1 + 0x14)); break;
        case 4: *(short *)(param_1 + 0x10) = func_ov005_0204eb2c(param_1, *(int *)(param_1 + 0x14)); break;
        case 5: *(short *)(param_1 + 0x10) = func_ov005_0204eb40(param_1, *(int *)(param_1 + 0x14)); break;
        case 6: *(short *)(param_1 + 0x10) = func_ov005_0204eb54(param_1, *(int *)(param_1 + 0x14)); break;
        case 7: *(short *)(param_1 + 0x10) = func_ov005_0204eb68(param_1, *(int *)(param_1 + 0x14)); break;
    }
}
