extern void func_0203c5c0();
extern void func_ov166_020ce43c(void);

void func_ov166_020ce3f0(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x2c, func_ov166_020ce43c, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
