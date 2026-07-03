extern void func_ov050_020b6530(int a, int b, int c);
extern void func_ov050_020b65bc(int a, int b);

void func_ov050_020b5f28(int this) {
    func_ov050_020b6530(this, this + 0x2c2c, *(short *)(this + 0x2aba));
    func_ov050_020b65bc(this, this + 0x2c2c);
}
