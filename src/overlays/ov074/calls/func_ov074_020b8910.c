extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern void func_ov074_020b8f58(int self);
extern int data_ov074_020b9b80;
extern int data_ov074_020b9b34;

typedef struct { int w[5]; } Params;
extern Params data_ov074_020b9a58;

void func_ov074_020b8910(int self) {
    Params p;
    char *blk;
    int base = *(int *)&data_ov074_020b9b80;
    blk = (char *)(base + 0xa4 + 0x2c00);
    *(int *)(blk + 0x10) = 0;
    *(int *)(blk + 0x124) = 0xf6;
    *(int *)(blk + 0x128) = 0x10a4;
    *(int *)(blk + 0x12c) = 0xccd;
    func_0202a634((int)(blk + 0x14), &data_ov074_020b9b34, 1,
                  *(unsigned char *)(base + 9) + 7);
    p = data_ov074_020b9a58;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
    func_ov074_020b8f58(self);
}
