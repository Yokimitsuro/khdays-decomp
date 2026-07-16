extern void func_02035fb0();
extern void func_02035ffc();
extern int data_ov009_020563e4;

void func_ov009_0204cd34(int arg0, unsigned int arg1) {
    func_02035fb0((unsigned int *)(*(int *)((char *)&data_ov009_020563e4 + 4) + 0x95d8), 0,
                  *(unsigned int *)(*(int *)((char *)&data_ov009_020563e4 + 4) + 0x95d4),
                  arg0 << 0xc, arg1);
    func_02035ffc(*(int *)((char *)&data_ov009_020563e4 + 4) + 0x95d8);
}
