extern void func_ov070_020b8c10(int a, int b, int c);
extern void func_ov070_020b8c9c(int a, int b);

void func_ov070_020b8608(int this) {
    func_ov070_020b8c10(this, this + 0x2c2c, *(short *)(this + 0x2aba));
    func_ov070_020b8c9c(this, this + 0x2c2c);
}
