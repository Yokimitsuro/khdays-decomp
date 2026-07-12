/* Recompute the cached value at (param_1)+0x10 from the source at +0x14 using the selector
 * param_2 (0-7) to pick the per-kind conversion; out-of-range selectors are ignored. */
extern int func_ov026_02084a34(int a, int b);
extern int func_ov026_02084a48(int a, int b);
extern int func_ov026_02084af8(int a, int b);
extern int func_ov026_02084ae4(int a, int b);
extern int func_ov026_02084b0c(int a, int b);
extern int func_ov026_02084b20(int a, int b);
extern int func_ov026_02084b34(int a, int b);
extern int func_ov026_02084b48(int a, int b);
void func_ov026_02084bbc(int param_1, int param_2) {
    switch (param_2) {
        case 0: *(short *)(param_1 + 0x10) = func_ov026_02084a34(param_1, *(int *)(param_1 + 0x14)); break;
        case 1: *(short *)(param_1 + 0x10) = func_ov026_02084a48(param_1, *(int *)(param_1 + 0x14)); break;
        case 2: *(short *)(param_1 + 0x10) = func_ov026_02084af8(param_1, *(int *)(param_1 + 0x14)); break;
        case 3: *(short *)(param_1 + 0x10) = func_ov026_02084ae4(param_1, *(int *)(param_1 + 0x14)); break;
        case 4: *(short *)(param_1 + 0x10) = func_ov026_02084b0c(param_1, *(int *)(param_1 + 0x14)); break;
        case 5: *(short *)(param_1 + 0x10) = func_ov026_02084b20(param_1, *(int *)(param_1 + 0x14)); break;
        case 6: *(short *)(param_1 + 0x10) = func_ov026_02084b34(param_1, *(int *)(param_1 + 0x14)); break;
        case 7: *(short *)(param_1 + 0x10) = func_ov026_02084b48(param_1, *(int *)(param_1 + 0x14)); break;
    }
}
