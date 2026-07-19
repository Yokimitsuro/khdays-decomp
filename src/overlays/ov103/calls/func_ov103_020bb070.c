extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);
extern void func_ov022_020ad44c(void *out, int self);
extern int func_02030788(void);

typedef struct { int x, y, z; } Vec3;

void func_ov103_020bb070(int self, char *blk) {
    Vec3 v;
    func_0202accc((int)(blk + 0x120), 0, (int)(blk + 0x200), 0);
    func_0202accc((int)(blk + 0x120), 2, (int)(blk + 0x200), 0);
    func_01fff774((int)(blk + 0x120), 0, 0);
    func_01fff774((int)(blk + 0x120), 2, 0);
    func_ov022_020ad44c(&v, self);
    *(unsigned short *)(blk + 0x19c) =
        (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    *(unsigned short *)(blk + 0x120) |= 0x20;
    *(Vec3 *)(blk + 0x1c4) = v;
    *(int *)(blk + 0x11c) = 1;
    if (func_02030788() != 0) return;
    if ((*(int *)self & 0x10000) != 0) return;
    *(signed char *)(self + 0x47a) = 3;
    *(signed char *)(self + 0x47b) = 1;
}
