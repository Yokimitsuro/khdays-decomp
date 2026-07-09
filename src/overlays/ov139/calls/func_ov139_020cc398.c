extern void func_0203c5c0();
extern void func_ov139_020cc694(void);

void func_ov139_020cc398(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x58, func_ov139_020cc694, 0, &entry);
    *entry = this_;
    *(int **)(this_ + 0x214) = entry;
}
