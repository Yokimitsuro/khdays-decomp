extern void func_0203c5c0();
extern void func_ov301_020cc2a4();

void func_ov301_020cc240(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x4c, (int)&func_ov301_020cc2a4, 0, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
