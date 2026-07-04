extern void func_0203c5c0();
extern void func_ov203_020d44c8();
extern void func_ov203_020d43cc();

void func_ov203_020d409c(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x5c,
                  (int)&func_ov203_020d43cc, (int)&func_ov203_020d44c8, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
