extern void func_0202accc(int a, unsigned short b, int c, int d);
extern void func_01fff774(int a, unsigned short b, int c);

typedef struct { int x, y, z; } Vec3;

void func_ov075_020b9978(int self, int bit) {
    int *blk = (int *)(self + 0x2c80);
    int i;
    if (blk[2] & (1 << bit)) return;
    if (*(int *)(self + 0x7b0) < blk[1]) return;
    blk[2] |= (1 << bit);
    for (i = 0; i < 5; i++) {
        if (((short *)((char *)blk + 0xec))[(unsigned short)i] > 0) {
            func_0202accc((int)blk + 0xc, i, (int)blk + 0xec, 0);
            func_01fff774((int)blk + 0xc, i, 0);
        }
    }
    *(Vec3 *)((char *)blk + 0xb0) = *(Vec3 *)(self + 0x8c + 0x400);
    *(unsigned short *)((char *)blk + 0x88) =
        (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    *(unsigned short *)((char *)blk + 0xc) |= 0x20;
    blk[0] = 1;
}
