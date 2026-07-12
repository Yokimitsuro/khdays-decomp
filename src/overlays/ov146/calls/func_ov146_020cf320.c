/* Set bit 1 of the +0x5c flags of *(*(self+4)+8). */
void func_ov146_020cf320(int param_1) {
    *(int *)(*(int *)(*(int *)(param_1 + 4) + 8) + 0x5c) |= 2;
}
