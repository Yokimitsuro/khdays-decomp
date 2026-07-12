/* Clear +0x48 and mark sub-state 1. */
void func_ov254_020d2e34(int param_1) {
    *(int *)(param_1 + 0x48) = 0;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 1;
}
