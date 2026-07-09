extern void func_02035fb0();
extern void func_02035ffc();
extern int data_ov025_020b5744;

void func_ov025_02082e18(int arg0, unsigned int arg1) {
    func_02035fb0((unsigned int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x95d8), 0,
                  *(unsigned int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x95d4),
                  arg0 << 0xc, arg1);
    func_02035ffc(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x95d8);
}
