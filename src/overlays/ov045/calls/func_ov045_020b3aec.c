extern void func_0202afdc(int a, int b);
extern void func_ov045_020b4254(int a, int b, int c);
extern void func_ov045_020b4450(int a, int b);
extern int data_ov045_020b4c20;

void func_ov045_020b3aec(int this_) {
    int dv = data_ov045_020b4c20;
    char *b = (char *)(dv + 0xdf0);
    func_0202afdc(dv + 0x2c30, *(unsigned short *)(this_ + 0xeb0));
    func_ov045_020b4254(this_, (int)(b + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov045_020b4450(this_, (int)(b + 0x2000));
}
