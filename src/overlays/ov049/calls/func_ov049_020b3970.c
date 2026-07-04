extern int data_ov049_020b4d00;
extern void func_ov049_020b3bac();
extern void func_ov049_020b3e00();

void func_ov049_020b3970(int this_) {
    char *p = (char *)(data_ov049_020b4d00 + 0xfc);
    func_ov049_020b3bac(this_, (int)(p + 0x2c00), *(short *)(this_ + 0x2aba));
    func_ov049_020b3e00(this_, (int)(p + 0x2c00));
}
