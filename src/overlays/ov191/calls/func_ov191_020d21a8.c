extern void func_0203c5c0();
extern void func_ov191_020d21f4(void);

void func_ov191_020d21a8(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x44, func_ov191_020d21f4, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
