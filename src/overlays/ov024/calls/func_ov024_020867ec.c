/* Copy a packed (u8,s16) pair from the source into +4 / +0. */
void func_ov024_020867ec(int param_1, int param_2) {
    *(int *)(param_1 + 4) = *(unsigned char *)param_2;
    *(int *)param_1 = *(short *)(param_2 + 2);
}
