extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern int data_ov103_020bc120;
extern int data_ov103_020bc0d4;
extern int data_ov103_020bc0e8;
extern int data_ov103_020bc0fc;

typedef struct { int w[5]; } Params;
extern Params data_ov103_020bc02c;

void func_ov103_020baed4(int self) {
    Params p;
    char *blk;
    int base = *(int *)&data_ov103_020bc120;
    blk = (char *)(base + 0x2c + 0x2c00);
    *(int *)(blk + 8) = 0;
    *(int *)(blk + 0x11c) = 0;
    func_0202a634((int)(blk + 0x24c), &data_ov103_020bc0d4, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0xc), &data_ov103_020bc0e8, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x120), &data_ov103_020bc0fc, 1,
                  *(unsigned char *)(base + 9) + 7);
    p = data_ov103_020bc02c;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
}
