extern void func_0203c5c0();
extern void func_ov169_020ce5f4(void);

void func_ov169_020ce5a8(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x4c, func_ov169_020ce5f4, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
