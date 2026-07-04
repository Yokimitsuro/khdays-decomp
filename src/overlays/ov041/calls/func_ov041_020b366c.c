extern void func_ov041_020b3bc8();
extern void func_ov041_020b3c10();

void func_ov041_020b366c(int this_) {
    char *p = (char *)(this_ + 0x84);
    func_ov041_020b3bc8(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov041_020b3c10(this_, p + 0x2c00);
}
