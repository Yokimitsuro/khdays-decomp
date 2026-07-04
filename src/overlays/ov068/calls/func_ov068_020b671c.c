extern int data_ov068_020b7500;
extern void func_ov068_020b686c();

void func_ov068_020b671c(int this_) {
    int *base = (int *)(data_ov068_020b7500 + 0x2cfc);
    base[0x43] = *(int *)(this_ + 0x2640) + 4;
    func_ov068_020b686c(this_);
    base[0x48] = 0;
}
