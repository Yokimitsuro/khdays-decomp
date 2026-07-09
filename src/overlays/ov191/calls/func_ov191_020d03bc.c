extern void func_0203c5c0();
extern void func_ov191_020d09dc(void);

void func_ov191_020d03bc(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x3c, func_ov191_020d09dc, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
