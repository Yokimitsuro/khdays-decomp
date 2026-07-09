extern void func_0203c5c0();
extern void func_ov293_020d213c(void);

void func_ov293_020d1ea4(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x54, func_ov293_020d213c, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
