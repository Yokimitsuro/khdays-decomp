extern void func_0203c5c0();
extern void func_ov242_020d40e0();

void func_ov242_020d3db0(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x44, (int)&func_ov242_020d40e0, 0, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
