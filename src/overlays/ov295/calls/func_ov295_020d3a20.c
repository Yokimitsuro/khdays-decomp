extern void func_0203c5c0();
extern void func_ov295_020d3bc4();

void func_ov295_020d3a20(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x10, (int)&func_ov295_020d3bc4, 0, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
