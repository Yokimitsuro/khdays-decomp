extern void func_0203c5c0();
extern void func_ov262_020d4340(void);

void func_ov262_020d3f3c(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x90, func_ov262_020d4340, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
