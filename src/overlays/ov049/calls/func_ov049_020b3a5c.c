extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern void func_ov049_020b3f54(int a);
extern int data_ov049_020b4d00;
extern int data_ov049_020b4c98;

typedef struct { int w[5]; } Params;
extern Params data_ov049_020b4b44;

void func_ov049_020b3a5c(int self) {
    int base = *(int *)&data_ov049_020b4d00;
    Params p;
    char *blk;
    *(signed char *)(base + 0x2000 + 0xcfc) = 0;
    blk = (char *)(base + 0xfc + 0x2c00);
    func_0202a634((int)(blk + 4), &data_ov049_020b4c98, 1,
                  *(unsigned char *)(base + 9) + 7);
    p = data_ov049_020b4b44;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
    func_ov049_020b3f54(base);
}
