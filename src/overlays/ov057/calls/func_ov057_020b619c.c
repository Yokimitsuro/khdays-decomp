extern void func_ov057_020b6340(int a, int b, int c);
extern void func_ov057_020b6558(int a, int b, int c);
extern void func_ov057_020b6b00(int a, int b, int c);
extern void func_ov057_020b665c(int a, int b, int c);
extern void func_ov057_020b6850(int a, int b, int c);
extern int func_02030788(void);

void func_ov057_020b619c(int self, char *blk, int arg) {
    int any = 0;
    if (*(int *)(blk + 0x228) != 0) any = 1;
    func_ov057_020b6340(self, (int)(blk + 0x228), arg);
    func_ov057_020b6558(self, (int)blk, arg);
    func_ov057_020b6b00(self, (int)(blk + 0x118), arg);
    func_ov057_020b665c(self, (int)(blk + 0x338), arg);
    func_ov057_020b6850(self, (int)(blk + 0x44 + 0x400), arg);
    if (any == 0) return;
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x46c) |= 0x10000;
}
