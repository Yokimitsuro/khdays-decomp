/* When status bit 2 of the flag word at param_1+0x4a7c is set, run func_02032428
 * and clear that bit. */
extern void func_02032428(int obj);

void func_ov000_02055b0c(int param_1) {
    if ((((unsigned int)*(unsigned int *)(param_1 + 0x4a7c) << 0x1d) >> 0x1f) == 1) {
        func_02032428(param_1);
        *(int *)(param_1 + 0x4a7c) &= ~4;
    }
}
