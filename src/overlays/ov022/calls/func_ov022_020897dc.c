extern int data_ov022_020b2ea4;
extern short func_02030788(void);
extern void MI_CpuCopy8(unsigned short *arg0, unsigned short *arg1, unsigned int arg2);
void func_ov022_020897dc(unsigned short *arg0, unsigned int arg1) {
    int p = data_ov022_020b2ea4;
    if (func_02030788() == 0) return;
    MI_CpuCopy8(arg0, (unsigned short *)(p + 0x14), arg1);
    *(char *)(p + 0xd4) = 1;
}
