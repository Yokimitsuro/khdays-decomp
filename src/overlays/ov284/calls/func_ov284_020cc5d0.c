extern void func_0203c5c0();
extern void func_ov284_020cc7cc(void);

void func_ov284_020cc5d0(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x28, func_ov284_020cc7cc, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
