extern void func_ov041_020b3d84(int a, int b);
extern void func_ov041_020b40dc(int a, int b);
extern void func_ov041_020b4224(int a, int b);
extern void func_ov041_020b439c(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov041_020b3c10(int self, int blk) {
    int i;
    char *p;
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov041_020b3d84(self, blk);
    p = (char *)(blk + 0x330);
    for (i = 0; i < 3; i++, p += 0x110) {
        func_ov041_020b40dc(self, (int)p);
    }
    func_ov041_020b4224(self, blk + 0x110);
    func_ov041_020b439c(self, blk + 0x220);
}
