/* Set *(*self)+0x39c=0 and mark sub-state 4. */
void func_ov259_020d1c44(int param_1) {
    *(int *)(*(int *)param_1 + 0x39c) = 0;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 4;
}
