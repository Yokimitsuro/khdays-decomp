extern int data_ov034_020b5660;
extern void func_ov034_020b531c();
extern void func_ov034_020b5490();

void func_ov034_020b3c70(int this_) {
    char *p = (char *)(data_ov034_020b5660 + 0xe4);
    func_ov034_020b531c(this_, (int)(p + 0x2c00), *(short *)(this_ + 0x2aba));
    func_ov034_020b5490(this_, (int)(p + 0x2c00));
}
