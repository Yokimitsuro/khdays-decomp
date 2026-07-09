extern void func_0203c5c0();
extern void func_ov184_020d23ec(void);

void func_ov184_020d1e60(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x88, func_ov184_020d23ec, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
