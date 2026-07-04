extern void func_ov061_020b6b88();
extern void func_ov061_020b6bfc();

void func_ov061_020b5e64(int this_) {
    char *p = (char *)(this_ + 0x2c);
    func_ov061_020b6b88(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov061_020b6bfc(this_, p + 0x2c00);
}
