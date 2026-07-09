extern void func_0203c5c0();
extern void func_ov261_020d0700(void);

void func_ov261_020d02fc(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x90, func_ov261_020d0700, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
