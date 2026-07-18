extern void func_ov097_020bb324(int a, int b);
extern void func_ov097_020bb67c(int a, int b);
extern void func_ov097_020bb7c4(int a, int b);
extern void func_ov097_020bb93c(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov097_020bb1b0(int self, int blk) {
    int i;
    char *p;
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov097_020bb324(self, blk);
    p = (char *)(blk + 0x330);
    for (i = 0; i < 3; i++, p += 0x110) {
        func_ov097_020bb67c(self, (int)p);
    }
    func_ov097_020bb7c4(self, blk + 0x110);
    func_ov097_020bb93c(self, blk + 0x220);
}
