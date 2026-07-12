/* Twin of func_ov008_0207bda4 for a different global; the flag byte is at
 * global+0x9520 and the base index is 0xd. */
extern int data_ov008_02090fa4;

int func_ov008_0207ddc4(int param_1) {
    int idx = (signed char)(param_1 - 0xd);
    if (idx >= 0) {
        if ((*(unsigned char *)(*(int *)&data_ov008_02090fa4 + 0x9520) >> idx & 1) == 0)
            return 0;
    }
    return 1;
}
