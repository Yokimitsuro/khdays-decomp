extern int data_ov101_020bc0e0;
extern void func_ov101_020bb628();
extern void func_ov101_020bb6e4();

void func_ov101_020bae58(int this_) {
    char *p = (char *)data_ov101_020bc0e0;
    func_ov101_020bb628(this_, (int)(p + 0x2c80), *(short *)(this_ + 0x2aba));
    func_ov101_020bb6e4(this_, (int)(p + 0x2c80));
}
