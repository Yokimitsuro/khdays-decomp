extern void func_0203c5c0();
extern void func_ov250_020d03fc(void);

void func_ov250_020d00f0(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x88, func_ov250_020d03fc, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
