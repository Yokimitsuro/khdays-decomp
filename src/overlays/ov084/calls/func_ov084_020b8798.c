extern int data_ov084_020b9a20;
extern void func_ov084_020b8f68();
extern void func_ov084_020b9024();

void func_ov084_020b8798(int this_) {
    char *p = (char *)data_ov084_020b9a20;
    func_ov084_020b8f68(this_, (int)(p + 0x2c80), *(short *)(this_ + 0x2aba));
    func_ov084_020b9024(this_, (int)(p + 0x2c80));
}
