extern int data_ov053_020b7e60;
extern void func_ov053_020b7b1c();
extern void func_ov053_020b7c90();

void func_ov053_020b6470(int this_) {
    char *p = (char *)(data_ov053_020b7e60 + 0xe4);
    func_ov053_020b7b1c(this_, (int)(p + 0x2c00), *(short *)(this_ + 0x2aba));
    func_ov053_020b7c90(this_, (int)(p + 0x2c00));
}
