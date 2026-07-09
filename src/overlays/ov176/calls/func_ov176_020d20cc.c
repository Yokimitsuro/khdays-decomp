extern void func_0203c5c0();
extern void func_ov176_020d2118(void);

void func_ov176_020d20cc(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x24, func_ov176_020d2118, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
