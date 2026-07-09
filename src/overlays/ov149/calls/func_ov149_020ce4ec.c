extern void func_0203c5c0();
extern void func_ov149_020ce704(void);

void func_ov149_020ce4ec(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x4c, func_ov149_020ce704, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
