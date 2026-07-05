extern void func_0202afdc(int a, int b);
extern void func_ov083_020b9134(int a, int b, int c);
extern void func_ov083_020b9330(int a, int b);
extern int data_ov083_020b9b00;

void func_ov083_020b89cc(int this_) {
    int dv = data_ov083_020b9b00;
    char *b = (char *)(dv + 0xdf0);
    func_0202afdc(dv + 0x2c30, *(unsigned short *)(this_ + 0xeb0));
    func_ov083_020b9134(this_, (int)(b + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov083_020b9330(this_, (int)(b + 0x2000));
}
