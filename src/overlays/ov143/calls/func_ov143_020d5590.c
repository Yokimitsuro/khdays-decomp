extern void func_0203c5c0();
extern void func_ov143_020d55dc(void);

void func_ov143_020d5590(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x2c, func_ov143_020d55dc, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
