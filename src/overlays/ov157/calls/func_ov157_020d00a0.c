extern void func_0203c5c0();
extern void func_ov157_020d00ec(void);

void func_ov157_020d00a0(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x30, func_ov157_020d00ec, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
