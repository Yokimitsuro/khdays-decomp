/* Store param_2 at param_1+4 and mark the linked object's state byte (+0x1c7) as 1. */
void func_ov283_020cef38(int param_1, int param_2) {
    *(int *)(param_1 + 4) = param_2;
    *(unsigned char *)(*(int *)param_1 + 0x1c7) = 1;
}
