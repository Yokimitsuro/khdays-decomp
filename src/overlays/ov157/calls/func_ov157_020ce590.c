extern void func_0203c5c0();
extern void func_ov157_020ceb74(void);

void func_ov157_020ce590(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x3c, func_ov157_020ceb74, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
