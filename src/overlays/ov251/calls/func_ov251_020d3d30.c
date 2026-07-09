extern void func_0203c5c0();
extern void func_ov251_020d403c(void);

void func_ov251_020d3d30(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x88, func_ov251_020d403c, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
