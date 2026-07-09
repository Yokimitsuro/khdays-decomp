extern void func_0203c5c0();
extern void func_ov193_020d461c(void);

void func_ov193_020d3ffc(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x3c, func_ov193_020d461c, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
