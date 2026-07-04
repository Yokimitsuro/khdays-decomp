extern int data_ov104_020bc2a0;
extern void func_ov104_020bb60c();

void func_ov104_020bb4bc(int this_) {
    int *base = (int *)(data_ov104_020bc2a0 + 0x2cfc);
    base[0x43] = *(int *)(this_ + 0x2640) + 4;
    func_ov104_020bb60c(this_);
    base[0x48] = 0;
}
