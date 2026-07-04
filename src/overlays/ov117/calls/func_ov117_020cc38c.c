extern void func_0203c5c0();
extern void func_ov117_020cc5fc();

void func_ov117_020cc38c(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x98, (int)&func_ov117_020cc5fc, 0, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
