extern void func_0203c5c0();
extern void func_ov202_020ccc48();
extern void func_ov202_020ccb4c();

void func_ov202_020cc81c(int this_) {
    int out;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x5c,
                  (int)&func_ov202_020ccb4c, (int)&func_ov202_020ccc48, &out);
    *(int *)out = this_;
    *(int *)(this_ + 0x214) = out;
}
