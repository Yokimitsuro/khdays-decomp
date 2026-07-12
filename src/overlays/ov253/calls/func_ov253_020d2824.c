/* Read the s16 at +2 of the +0x3e4 table entry indexed by the +0x3dd counter. */
int func_ov253_020d2824(int param_1) {
    int idx = *(signed char *)(param_1 + 0x3dd);
    return *(short *)(*(int *)(param_1 + 0x3e4) + idx * 4 + 2);
}
