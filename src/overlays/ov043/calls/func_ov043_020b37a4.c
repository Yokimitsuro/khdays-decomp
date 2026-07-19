extern int data_ov043_020b58e0;
extern void func_ov043_020b4898();
extern void func_ov043_020b4a68();

void func_ov043_020b37a4(int this_) {
    char *p = (char *)(data_ov043_020b58e0 + 0x138);
    func_ov043_020b4898(this_, (int)(p + 0x2c00), *(short *)(this_ + 0x2aba));
    func_ov043_020b4a68(this_, (int)(p + 0x2c00));
}
