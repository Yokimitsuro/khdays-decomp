/* NONMATCHING: instruction-scheduling tie. The original hoists the (field6 & 7)
 * shift-extract before the guard call; mwcc schedules it after (4B short). Same
 * logic: if not busy, MI_CpuCopy8 into global+0x58+(field6&7)*0x10. */
extern int data_ov022_020b2ea4;
extern short func_02030788(void);
extern void MI_CpuCopy8(unsigned short *a, unsigned short *b, unsigned int n);
void func_ov022_0208973c(unsigned short *arg0, unsigned int arg1) {
    unsigned int idx = arg0[6] & 7;
    int base = data_ov022_020b2ea4;
    if (func_02030788() != 0) return;
    MI_CpuCopy8(arg0, (unsigned short *)(base + 0x58 + idx * 0x10), arg1);
}
