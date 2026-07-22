extern void func_0202ba18(int arg0);
extern void func_0202a7dc(int arg0);

void func_ov002_0207befc(int self) {
    int owner = *(int *)(self + 8);

    func_0202ba18(self + 0x2c);
    if (*(signed char *)(owner + 0x58) != 0) {
        func_0202a7dc(self + 0x1b0);
    }
    *(unsigned short *)(self + 0x12) &= ~4;
}
