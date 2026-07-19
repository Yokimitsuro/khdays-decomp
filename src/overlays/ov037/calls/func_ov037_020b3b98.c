extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern int data_ov037_020b4e20;
extern int data_ov037_020b4df4;
extern int data_ov037_020b4e08;

typedef struct { int w[5]; } Params;
extern Params data_ov037_020b4d10;

void func_ov037_020b3b98(int self) {
    Params p;
    char *blk;
    int base = *(int *)&data_ov037_020b4e20;
    *(int *)(base + 0x2000 + 0xc2c) = 0;
    blk = (char *)(base + 0x2c + 0x2c00);
    func_0202a634((int)(blk + 4), &data_ov037_020b4df4, 1, *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x120), &data_ov037_020b4e08, 1, *(unsigned char *)(base + 9) + 7);
    p = data_ov037_020b4d10;
    p.w[1] = 4;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
}
