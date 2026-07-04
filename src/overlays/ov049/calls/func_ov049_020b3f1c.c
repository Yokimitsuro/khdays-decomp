extern int data_ov049_020b4d00;
extern void func_ov049_020b406c();

void func_ov049_020b3f1c(int this_) {
    int *base = (int *)(data_ov049_020b4d00 + 0x2cfc);
    base[0x43] = *(int *)(this_ + 0x2640) + 4;
    func_ov049_020b406c(this_);
    base[0x48] = 0;
}
