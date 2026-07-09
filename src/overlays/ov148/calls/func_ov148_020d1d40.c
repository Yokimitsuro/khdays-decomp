extern void func_0203c5c0();
extern void func_ov148_020d1d8c(void);

void func_ov148_020d1d40(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x34, func_ov148_020d1d8c, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
