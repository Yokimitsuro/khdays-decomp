extern void func_ov031_020b3d30(int a, int b, int c);
extern void func_ov031_020b3dbc(int a, int b);

void func_ov031_020b3728(int this) {
    func_ov031_020b3d30(this, this + 0x2c2c, *(short *)(this + 0x2aba));
    func_ov031_020b3dbc(this, this + 0x2c2c);
}
