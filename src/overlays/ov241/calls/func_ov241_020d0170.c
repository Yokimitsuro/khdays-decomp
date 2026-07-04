extern void func_0203c5c0();
extern void func_ov241_020d04a0();

void func_ov241_020d0170(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x44, (int)&func_ov241_020d04a0, 0, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
