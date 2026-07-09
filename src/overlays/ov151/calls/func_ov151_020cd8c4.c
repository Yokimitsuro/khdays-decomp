extern void func_0203c5c0();
extern void func_ov151_020cdaac(void);

void func_ov151_020cd8c4(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x50, func_ov151_020cdaac, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
