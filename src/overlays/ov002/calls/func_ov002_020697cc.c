extern void MI_CpuFill8();
extern int data_ov002_0207fa00;

void func_ov002_020697cc(void) {
    MI_CpuFill8(*(int *)&data_ov002_0207fa00 + 0x8b7c, 0, 0x2c);
}
