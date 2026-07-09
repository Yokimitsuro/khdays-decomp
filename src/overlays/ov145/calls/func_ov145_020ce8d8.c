extern void func_0203c5c0();
extern void func_ov145_020cebbc(void);

void func_ov145_020ce8d8(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x54, func_ov145_020cebbc, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
