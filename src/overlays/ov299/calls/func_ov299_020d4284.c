extern void func_0203c5c0();
extern void func_ov299_020d42d0(void);

void func_ov299_020d4284(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x34, func_ov299_020d42d0, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
