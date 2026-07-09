extern void func_0203c5c0();
extern void func_ov204_020d03f4(void);

void func_ov204_020d0100(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x5c, func_ov204_020d03f4, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
