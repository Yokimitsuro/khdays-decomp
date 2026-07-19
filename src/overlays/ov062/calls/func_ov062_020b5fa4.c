extern int data_ov062_020b80e0;
extern void func_ov062_020b7098();
extern void func_ov062_020b7268();

void func_ov062_020b5fa4(int this_) {
    char *p = (char *)(data_ov062_020b80e0 + 0x138);
    func_ov062_020b7098(this_, (int)(p + 0x2c00), *(short *)(this_ + 0x2aba));
    func_ov062_020b7268(this_, (int)(p + 0x2c00));
}
