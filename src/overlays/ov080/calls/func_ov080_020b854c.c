extern void func_ov080_020b8aa8();
extern void func_ov080_020b8af0();

void func_ov080_020b854c(int this_) {
    char *p = (char *)(this_ + 0x84);
    func_ov080_020b8aa8(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov080_020b8af0(this_, p + 0x2c00);
}
