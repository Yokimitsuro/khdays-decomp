extern void func_ov042_020b4388();
extern void func_ov042_020b43fc();

void func_ov042_020b3664(int this_) {
    char *p = (char *)(this_ + 0x2c);
    func_ov042_020b4388(this_, p + 0x2c00, *(short *)(this_ + 0x2aba));
    func_ov042_020b43fc(this_, p + 0x2c00);
}
