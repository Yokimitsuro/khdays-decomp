extern void func_0202afdc(int a, int b);
extern void func_ov100_020bb7f4(int a, int b, int c);
extern void func_ov100_020bb9f0(int a, int b);
extern int data_ov100_020bc1c0;

void func_ov100_020bb08c(int this_) {
    int dv = data_ov100_020bc1c0;
    char *b = (char *)(dv + 0xdf0);
    func_0202afdc(dv + 0x2c30, *(unsigned short *)(this_ + 0xeb0));
    func_ov100_020bb7f4(this_, (int)(b + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov100_020bb9f0(this_, (int)(b + 0x2000));
}
