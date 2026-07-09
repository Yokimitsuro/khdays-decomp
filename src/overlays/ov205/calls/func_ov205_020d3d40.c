extern void func_0203c5c0();
extern void func_ov205_020d4034(void);

void func_ov205_020d3d40(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x5c, func_ov205_020d4034, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
