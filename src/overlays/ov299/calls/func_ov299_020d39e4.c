extern void func_0203c5c0();
extern void func_ov299_020d3a30(void);

void func_ov299_020d39e4(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0xc, func_ov299_020d3a30, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
