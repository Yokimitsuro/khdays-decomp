extern void func_ov075_020b9188(void);
extern void func_ov075_020b95c8(void);
extern int data_ov075_020b9e20;

void *func_ov075_020b8624(int self, int req) {
    int *blk = (int *)(*(int *)&data_ov075_020b9e20 + 0x194 + 0x2c00);
    void *cb = 0;
    switch (req) {
    default:
        break;
    case 0x21:
        blk[3] = 0;
        blk[4] = 0;
        blk[1] = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x2f);
        cb = (void *)&func_ov075_020b9188;
        break;
    case 0x23:
        blk[3] = 2;
        blk[4] = 5;
        (*(void (**)(int, int))(self + 0x664))(self, 0x2f);
        cb = (void *)&func_ov075_020b9188;
        break;
    case 0x22:
        blk[3] = 0;
        blk[2] = 0;
        blk[1] = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x30);
        cb = (void *)&func_ov075_020b95c8;
        break;
    }
    return cb;
}
