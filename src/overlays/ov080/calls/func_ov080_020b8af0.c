extern void func_ov080_020b8c64(int a, int b);
extern void func_ov080_020b8fbc(int a, int b);
extern void func_ov080_020b9104(int a, int b);
extern void func_ov080_020b927c(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov080_020b8af0(int self, int blk) {
    int i;
    char *p;
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov080_020b8c64(self, blk);
    p = (char *)(blk + 0x330);
    for (i = 0; i < 3; i++, p += 0x110) {
        func_ov080_020b8fbc(self, (int)p);
    }
    func_ov080_020b9104(self, blk + 0x110);
    func_ov080_020b927c(self, blk + 0x220);
}
