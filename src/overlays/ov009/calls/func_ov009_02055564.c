/* Recompute the cached value at (param_1)+0x10 from the source at +0x14 using the selector
 * param_2 (0-7) to pick the per-kind conversion; out-of-range selectors are ignored. */
extern int func_ov009_020553dc(int a, int b);
extern int func_ov009_020553f0(int a, int b);
extern int func_ov009_020554a0(int a, int b);
extern int func_ov009_0205548c(int a, int b);
extern int func_ov009_020554b4(int a, int b);
extern int func_ov009_020554c8(int a, int b);
extern int func_ov009_020554dc(int a, int b);
extern int func_ov009_020554f0(int a, int b);
void func_ov009_02055564(int param_1, int param_2) {
    switch (param_2) {
        case 0: *(short *)(param_1 + 0x10) = func_ov009_020553dc(param_1, *(int *)(param_1 + 0x14)); break;
        case 1: *(short *)(param_1 + 0x10) = func_ov009_020553f0(param_1, *(int *)(param_1 + 0x14)); break;
        case 2: *(short *)(param_1 + 0x10) = func_ov009_020554a0(param_1, *(int *)(param_1 + 0x14)); break;
        case 3: *(short *)(param_1 + 0x10) = func_ov009_0205548c(param_1, *(int *)(param_1 + 0x14)); break;
        case 4: *(short *)(param_1 + 0x10) = func_ov009_020554b4(param_1, *(int *)(param_1 + 0x14)); break;
        case 5: *(short *)(param_1 + 0x10) = func_ov009_020554c8(param_1, *(int *)(param_1 + 0x14)); break;
        case 6: *(short *)(param_1 + 0x10) = func_ov009_020554dc(param_1, *(int *)(param_1 + 0x14)); break;
        case 7: *(short *)(param_1 + 0x10) = func_ov009_020554f0(param_1, *(int *)(param_1 + 0x14)); break;
    }
}
