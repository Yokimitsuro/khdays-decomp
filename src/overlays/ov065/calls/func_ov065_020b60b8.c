extern int data_ov065_020b7340;
extern void func_ov065_020b6888();
extern void func_ov065_020b6944();

void func_ov065_020b60b8(int this_) {
    char *p = (char *)data_ov065_020b7340;
    func_ov065_020b6888(this_, (int)(p + 0x2c80), *(short *)(this_ + 0x2aba));
    func_ov065_020b6944(this_, (int)(p + 0x2c80));
}
