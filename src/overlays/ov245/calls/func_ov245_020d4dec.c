/* Clear +0xc and mark sub-state 1. */
void func_ov245_020d4dec(int param_1) {
    *(int *)(param_1 + 0xc) = 0;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 1;
}
