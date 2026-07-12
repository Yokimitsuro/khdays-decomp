/* Store a boolean at +0x18. */
void func_ov146_020ce670(int param_1, int param_2) {
    *(signed char *)(param_1 + 0x18) = param_2 != 0;
}
