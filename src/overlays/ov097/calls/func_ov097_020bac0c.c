extern void func_ov097_020bb168();
extern void func_ov097_020bb1b0();

void func_ov097_020bac0c(int this_) {
    char *p = (char *)(this_ + 0x84);
    func_ov097_020bb168(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov097_020bb1b0(this_, p + 0x2c00);
}
