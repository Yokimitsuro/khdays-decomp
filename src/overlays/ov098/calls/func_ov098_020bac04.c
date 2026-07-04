extern void func_ov098_020bb928();
extern void func_ov098_020bb99c();

void func_ov098_020bac04(int this_) {
    char *p = (char *)(this_ + 0x2c);
    func_ov098_020bb928(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov098_020bb99c(this_, p + 0x2c00);
}
