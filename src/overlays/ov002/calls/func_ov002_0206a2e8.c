extern void MI_CpuFill8();
extern int data_ov002_0207fa00;

void func_ov002_0206a2e8(void) {
    MI_CpuFill8(*(int *)&data_ov002_0207fa00 + 0x8d7c, 0, 8);
}
