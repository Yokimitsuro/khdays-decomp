extern void func_0202afdc(int a, int b);
extern void func_ov064_020b6a54(int a, int b, int c);
extern void func_ov064_020b6c50(int a, int b);
extern int data_ov064_020b7420;

void func_ov064_020b62ec(int this_) {
    int dv = data_ov064_020b7420;
    char *b = (char *)(dv + 0xdf0);
    func_0202afdc(dv + 0x2c30, *(unsigned short *)(this_ + 0xeb0));
    func_ov064_020b6a54(this_, (int)(b + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov064_020b6c50(this_, (int)(b + 0x2000));
}
