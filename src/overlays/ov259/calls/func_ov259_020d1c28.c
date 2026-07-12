/* Set *(*self)+0x39c=1 and mark sub-state 3. */
void func_ov259_020d1c28(int param_1) {
    *(int *)(*(int *)param_1 + 0x39c) = 1;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 3;
}
