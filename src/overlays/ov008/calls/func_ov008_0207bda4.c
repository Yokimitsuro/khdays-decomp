/* param_1 indexes a bit (base 0xd) in the flag byte at global+0x30; below the
 * base, or when the bit is set, return 1; otherwise 0. */
extern int data_ov008_02090fa0;

int func_ov008_0207bda4(int param_1) {
    int idx = (signed char)(param_1 - 0xd);
    if (idx >= 0) {
        if ((*(unsigned char *)(*(int *)&data_ov008_02090fa0 + 0x30) >> idx & 1) == 0)
            return 0;
    }
    return 1;
}
