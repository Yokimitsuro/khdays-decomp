extern int data_ov087_020b9be0;
extern void func_ov087_020b8f4c();

void func_ov087_020b8dfc(int this_) {
    int *base = (int *)(data_ov087_020b9be0 + 0x2cfc);
    base[0x43] = *(int *)(this_ + 0x2640) + 4;
    func_ov087_020b8f4c(this_);
    base[0x48] = 0;
}
