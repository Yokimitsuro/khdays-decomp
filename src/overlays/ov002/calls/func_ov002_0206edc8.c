extern int data_ov002_0207fa04;
extern void func_ov002_0206ed7c(void);
extern void func_ov002_0206eda0(void);
extern void MIi_CpuClear16();

void func_ov002_0206edc8(void) {
    int p = *(int *)&data_ov002_0207fa04;
    func_ov002_0206ed7c();
    func_ov002_0206eda0();
    MIi_CpuClear16(0xffff, p + 2, 8);
    *(unsigned short *)p = 1;
}
