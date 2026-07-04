extern int data_ov046_020b4b40;
extern void func_ov046_020b4088();
extern void func_ov046_020b4144();

void func_ov046_020b38b8(int this_) {
    char *p = (char *)data_ov046_020b4b40;
    func_ov046_020b4088(this_, (int)(p + 0x2c80), *(short *)(this_ + 0x2aba));
    func_ov046_020b4144(this_, (int)(p + 0x2c80));
}
