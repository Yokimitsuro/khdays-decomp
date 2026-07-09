extern void func_0203c5c0();
extern void func_ov114_020cc98c(void);

void func_ov114_020cc444(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x6c, func_ov114_020cc98c, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
