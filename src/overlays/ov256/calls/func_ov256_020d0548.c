/* Set *(*self)+0x394 = 1 and mark sub-state 1. */
void func_ov256_020d0548(int param_1) {
    *(int *)(*(int *)param_1 + 0x394) = 1;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 1;
}
