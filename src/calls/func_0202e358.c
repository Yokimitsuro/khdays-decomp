extern void *SND_RegisterSeq(int a, int b);
extern int func_0202e198();
extern int func_0202e5e8();
extern void func_0202e084(int *ptr);
extern int func_0202e4f4();

int func_0202e358(int *this_, int seq) {
    int result;
    this_[0] = 0;
    this_[0x54 / 4] = 0;
    this_[1] = (int)SND_RegisterSeq(seq, 0xf);
    this_[2] = func_0202e198();
    func_0202e5e8(this_, 0);
    func_0202e084(this_);
    result = func_0202e4f4((int)this_, 0x1000);
    this_[0x48 / 4] = 0;
    this_[0x4c / 4] = 0;
    this_[0x50 / 4] = 0;
    this_[0] |= 1;
    return result;
}
