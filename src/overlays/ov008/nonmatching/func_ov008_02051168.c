/* PROVEN TIE (register coloring only): mwcc reuses the just-freed r0 for the
 * reloaded base on stores 2 and 3, while the ROM keeps r3 then picks r1. The
 * instruction stream is otherwise identical (three reloads of *(&data+4), each
 * +0x9000, storing param_1/2/3 at +0x740/+0x744/+0x748). Kept here so the ov008
 * blob stays byte-exact. */
extern int data_ov008_02090f04;

void func_ov008_02051168(int param_1, int param_2, int param_3) {
    *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x9740) = param_1;
    *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x9744) = param_2;
    *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x9748) = param_3;
}
