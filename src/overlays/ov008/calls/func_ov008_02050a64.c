extern void func_ov008_02055c08();
extern void func_ov008_02054e4c();
extern void func_ov008_02054e24();
extern int data_ov008_02090f04;

void func_ov008_02050a64(unsigned int arg0) {
    func_ov008_02055c08(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x9500, arg0);
    func_ov008_02054e4c(*(int *)((char *)&data_ov008_02090f04 + 4), arg0);
    func_ov008_02054e24(*(int *)((char *)&data_ov008_02090f04 + 4), arg0);
    *(unsigned int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x9600) = arg0;
}
