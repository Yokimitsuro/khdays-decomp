extern int data_ov012_0205cb20;
extern void func_020115b8();
extern void func_ov012_0205ac40();
extern void func_02032f5c();

void func_ov012_0205accc(void) {
    int base = data_ov012_0205cb20;
    if (base == 0) return;
    if (*(unsigned char *)(base + 0x8be1) != 0) {
        func_020115b8();
        *(unsigned char *)(data_ov012_0205cb20 + 0x8be1) = 0;
    }
    func_ov012_0205ac40(base);
    func_02032f5c();
}
