extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);
extern void func_02035d30(void);

extern unsigned char data_02042a1c[];
extern unsigned char data_0204c678[];
extern unsigned char data_0204c4f0[];
extern unsigned char data_0204c500[];

void func_020352cc(void) {
    int i;
    unsigned char *p;

    data_02042a1c[1] = 0;
    p = data_0204c678;
    for (i = 0; i < 4; i++) {
        MI_CpuFill8(p, 0, 0x104);
        p += 0x104;
    }
    data_0204c4f0[1] = 0;
    data_02042a1c[0] = 0;
    p = data_0204c500;
    for (i = 0; i < 2; i++) {
        MI_CpuFill8(p, 0, 0x48);
        p += 0x48;
    }
    func_02035d30();
}
