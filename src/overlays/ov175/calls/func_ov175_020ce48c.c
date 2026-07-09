extern void func_0203c5c0();
extern void func_ov175_020ce4d8(void);

void func_ov175_020ce48c(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x24, func_ov175_020ce4d8, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
