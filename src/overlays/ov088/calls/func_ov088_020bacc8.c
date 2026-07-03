extern void func_ov088_020bb2d0(int a, int b, int c);
extern void func_ov088_020bb35c(int a, int b);

void func_ov088_020bacc8(int this) {
    func_ov088_020bb2d0(this, this + 0x2c2c, *(short *)(this + 0x2aba));
    func_ov088_020bb35c(this, this + 0x2c2c);
}
