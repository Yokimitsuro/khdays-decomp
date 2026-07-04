extern void func_ov060_020b63c8();
extern void func_ov060_020b6410();

void func_ov060_020b5e6c(int this_) {
    char *p = (char *)(this_ + 0x84);
    func_ov060_020b63c8(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov060_020b6410(this_, p + 0x2c00);
}
