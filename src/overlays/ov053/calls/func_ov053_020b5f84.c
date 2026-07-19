extern int func_0202aee0(int a, int b);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cdf4(int a, int b, int c);
extern int func_02030788(void);
extern int func_ov022_020ad718(int self);
extern void func_ov002_020521e4(int a, int b, int c, int d);
extern void func_ov053_020b6044(int self);
extern void func_ov022_020ad588(int self);

void func_ov053_020b5f84(int self) {
    int *blk = (int *)(self + 0xe4 + 0x2c00);
    int t = func_0202aee0(*(int *)(self + 0x20) + 4, 0);
    int st = *(int *)(self + 0x6bc);
    if ((st != 0x31 && st != 0x33) ||
        (st == 0x31 && *(int *)(self + 0x7b0) >= 0x18000)) {
        if (blk[3] == 1) {
            func_ov002_0204cdf4(func_ov022_02083f0c(), 0, 0);
            blk[3] = 0;
        }
    } else if (*(unsigned char *)(self + 8) == func_02030788()) {
        blk[3] = func_ov022_020ad718(self);
    }
    func_ov002_020521e4(self + 0x1a8 + 0xc00, self + 0x2c + 0x2c00,
                        *(short *)(self + 0x2a00 + 0xba), t);
    func_ov053_020b6044(self);
    func_ov022_020ad588(self);
}
