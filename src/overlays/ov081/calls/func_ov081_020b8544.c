extern void func_ov081_020b9268();
extern void func_ov081_020b92dc();

void func_ov081_020b8544(int this_) {
    char *p = (char *)(this_ + 0x2c);
    func_ov081_020b9268(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov081_020b92dc(this_, p + 0x2c00);
}
