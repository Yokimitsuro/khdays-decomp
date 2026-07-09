extern void func_0203c5c0();
extern void func_ov123_020cc718(void);

void func_ov123_020cc524(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x38, func_ov123_020cc718, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
