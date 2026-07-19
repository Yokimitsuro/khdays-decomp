extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern int data_ov093_020bc3c0;
extern int data_ov093_020bc394;
extern int data_ov093_020bc3a8;

typedef struct { int w[5]; } Params;
extern Params data_ov093_020bc2b0;

void func_ov093_020bb138(int self) {
    Params p;
    char *blk;
    int base = *(int *)&data_ov093_020bc3c0;
    *(int *)(base + 0x2000 + 0xc2c) = 0;
    blk = (char *)(base + 0x2c + 0x2c00);
    func_0202a634((int)(blk + 4), &data_ov093_020bc394, 1, *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x120), &data_ov093_020bc3a8, 1, *(unsigned char *)(base + 9) + 7);
    p = data_ov093_020bc2b0;
    p.w[1] = 4;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
}
