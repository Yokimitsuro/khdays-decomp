extern void func_0203c5c0();
extern void func_ov285_020d1cec();

void func_ov285_020d1bfc(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x30, (int)&func_ov285_020d1cec, 0, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
