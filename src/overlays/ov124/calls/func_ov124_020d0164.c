extern void func_0203c5c0();
extern void func_ov124_020d0358(void);

void func_ov124_020d0164(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x38, func_ov124_020d0358, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
