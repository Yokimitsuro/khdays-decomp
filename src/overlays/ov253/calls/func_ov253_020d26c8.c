/* Report whether the sub-state at +0x3dc is 0x10. */
int func_ov253_020d26c8(int param_1) {
    return *(signed char *)(param_1 + 0x3dc) == 0x10;
}
