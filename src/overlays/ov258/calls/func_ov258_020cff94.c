/* Store three params and mark sub-state 2. */
void func_ov258_020cff94(int param_1, int param_2, int param_3, int param_4) {
    *(int *)(param_1 + 0x14) = param_2;
    *(int *)(param_1 + 0x18) = param_3;
    *(signed char *)(param_1 + 0x1c) = param_4;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 2;
}
