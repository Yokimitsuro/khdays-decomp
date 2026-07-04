extern int data_ov068_020b7500;
extern void func_ov068_020b63ac();
extern void func_ov068_020b6600();

void func_ov068_020b6170(int this_) {
    char *p = (char *)(data_ov068_020b7500 + 0xfc);
    func_ov068_020b63ac(this_, (int)(p + 0x2c00), *(short *)(this_ + 0x2aba));
    func_ov068_020b6600(this_, (int)(p + 0x2c00));
}
