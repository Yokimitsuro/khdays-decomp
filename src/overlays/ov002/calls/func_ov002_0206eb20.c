extern void MIi_CpuClear16();
extern int data_ov002_0207fa04;

void func_ov002_0206eb20(void) {
    int p = *(int *)&data_ov002_0207fa04;
    *(unsigned short *)p = 1;
    MIi_CpuClear16(0xffff, p + 2, 8);
}
