extern void func_0203c5c0();
extern void func_ov193_020d5e34(void);

void func_ov193_020d5de8(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x44, func_ov193_020d5e34, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
