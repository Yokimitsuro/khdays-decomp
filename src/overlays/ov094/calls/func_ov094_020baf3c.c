extern void func_ov094_020bb0e0(int a, int b, int c);
extern void func_ov094_020bb2f8(int a, int b, int c);
extern void func_ov094_020bb8a0(int a, int b, int c);
extern void func_ov094_020bb3fc(int a, int b, int c);
extern void func_ov094_020bb5f0(int a, int b, int c);
extern int func_02030788(void);

void func_ov094_020baf3c(int self, char *blk, int arg) {
    int any = 0;
    if (*(int *)(blk + 0x228) != 0) any = 1;
    func_ov094_020bb0e0(self, (int)(blk + 0x228), arg);
    func_ov094_020bb2f8(self, (int)blk, arg);
    func_ov094_020bb8a0(self, (int)(blk + 0x118), arg);
    func_ov094_020bb3fc(self, (int)(blk + 0x338), arg);
    func_ov094_020bb5f0(self, (int)(blk + 0x44 + 0x400), arg);
    if (any == 0) return;
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x46c) |= 0x10000;
}
