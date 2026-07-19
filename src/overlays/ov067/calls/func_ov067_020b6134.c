extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern int data_ov067_020b7380;
extern int data_ov067_020b7334;
extern int data_ov067_020b7348;
extern int data_ov067_020b735c;

typedef struct { int w[5]; } Params;
extern Params data_ov067_020b728c;

void func_ov067_020b6134(int self) {
    Params p;
    char *blk;
    int base = *(int *)&data_ov067_020b7380;
    blk = (char *)(base + 0x2c + 0x2c00);
    *(int *)(blk + 8) = 0;
    *(int *)(blk + 0x11c) = 0;
    func_0202a634((int)(blk + 0x24c), &data_ov067_020b7334, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0xc), &data_ov067_020b7348, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x120), &data_ov067_020b735c, 1,
                  *(unsigned char *)(base + 9) + 7);
    p = data_ov067_020b728c;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
}
