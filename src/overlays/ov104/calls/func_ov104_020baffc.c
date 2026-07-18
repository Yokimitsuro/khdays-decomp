extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern void func_ov104_020bb4f4(int a);
extern int data_ov104_020bc2a0;
extern int data_ov104_020bc238;

typedef struct { int w[5]; } Params;
extern Params data_ov104_020bc0e4;

void func_ov104_020baffc(int self) {
    int base = *(int *)&data_ov104_020bc2a0;
    Params p;
    char *blk;
    *(signed char *)(base + 0x2000 + 0xcfc) = 0;
    blk = (char *)(base + 0xfc + 0x2c00);
    func_0202a634((int)(blk + 4), &data_ov104_020bc238, 1,
                  *(unsigned char *)(base + 9) + 7);
    p = data_ov104_020bc0e4;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
    func_ov104_020bb4f4(base);
}
