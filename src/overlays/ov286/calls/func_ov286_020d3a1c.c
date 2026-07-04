extern void func_0203c5c0();
extern void func_ov286_020d3b0c();

void func_ov286_020d3a1c(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x30, (int)&func_ov286_020d3b0c, 0, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
