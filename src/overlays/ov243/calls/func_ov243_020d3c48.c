extern void func_0203c5c0();
extern void func_ov243_020d3f70(void);

void func_ov243_020d3c48(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x44, func_ov243_020d3f70, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
