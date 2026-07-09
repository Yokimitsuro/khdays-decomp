extern void func_0203c5c0();
extern void func_ov152_020d532c(void);

void func_ov152_020d5144(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x50, func_ov152_020d532c, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
