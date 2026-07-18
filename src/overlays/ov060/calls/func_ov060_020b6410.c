extern void func_ov060_020b6584(int a, int b);
extern void func_ov060_020b68dc(int a, int b);
extern void func_ov060_020b6a24(int a, int b);
extern void func_ov060_020b6b9c(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov060_020b6410(int self, int blk) {
    int i;
    char *p;
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov060_020b6584(self, blk);
    p = (char *)(blk + 0x330);
    for (i = 0; i < 3; i++, p += 0x110) {
        func_ov060_020b68dc(self, (int)p);
    }
    func_ov060_020b6a24(self, blk + 0x110);
    func_ov060_020b6b9c(self, blk + 0x220);
}
