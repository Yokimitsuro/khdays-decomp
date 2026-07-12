/* Store param at *(*self)+0x38c and mark sub-state 1 (nonzero) or 2 (zero). */
void func_ov146_020cf200(int param_1, int param_2) {
    *(int *)(*(int *)param_1 + 0x38c) = param_2;
    *(signed char *)(*(int *)param_1 + 0x1c7) = param_2 ? 1 : 2;
}
