/* Recompute the cached value at (param_1)+0x10 from the source at +0x14 using the selector
 * param_2 (0-7) to pick the per-kind conversion; out-of-range selectors are ignored. */
extern int func_ov008_020562f0(int a, int b);
extern int func_ov008_02056304(int a, int b);
extern int func_ov008_020563b4(int a, int b);
extern int func_ov008_020563a0(int a, int b);
extern int func_ov008_020563c8(int a, int b);
extern int func_ov008_020563dc(int a, int b);
extern int func_ov008_020563f0(int a, int b);
extern int func_ov008_02056404(int a, int b);
void func_ov008_02056478(int param_1, int param_2) {
    switch (param_2) {
        case 0: *(short *)(param_1 + 0x10) = func_ov008_020562f0(param_1, *(int *)(param_1 + 0x14)); break;
        case 1: *(short *)(param_1 + 0x10) = func_ov008_02056304(param_1, *(int *)(param_1 + 0x14)); break;
        case 2: *(short *)(param_1 + 0x10) = func_ov008_020563b4(param_1, *(int *)(param_1 + 0x14)); break;
        case 3: *(short *)(param_1 + 0x10) = func_ov008_020563a0(param_1, *(int *)(param_1 + 0x14)); break;
        case 4: *(short *)(param_1 + 0x10) = func_ov008_020563c8(param_1, *(int *)(param_1 + 0x14)); break;
        case 5: *(short *)(param_1 + 0x10) = func_ov008_020563dc(param_1, *(int *)(param_1 + 0x14)); break;
        case 6: *(short *)(param_1 + 0x10) = func_ov008_020563f0(param_1, *(int *)(param_1 + 0x14)); break;
        case 7: *(short *)(param_1 + 0x10) = func_ov008_02056404(param_1, *(int *)(param_1 + 0x14)); break;
    }
}
