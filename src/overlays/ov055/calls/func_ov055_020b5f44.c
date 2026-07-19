extern void func_ov055_020b6aa8(void);
extern void func_ov055_020b6ee8(void);
extern int data_ov055_020b7740;

void *func_ov055_020b5f44(int self, int req) {
    int *blk = (int *)(*(int *)&data_ov055_020b7740 + 0x194 + 0x2c00);
    void *cb = 0;
    switch (req) {
    default:
        break;
    case 0x21:
        blk[3] = 0;
        blk[4] = 0;
        blk[1] = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x2f);
        cb = (void *)&func_ov055_020b6aa8;
        break;
    case 0x23:
        blk[3] = 2;
        blk[4] = 5;
        (*(void (**)(int, int))(self + 0x664))(self, 0x2f);
        cb = (void *)&func_ov055_020b6aa8;
        break;
    case 0x22:
        blk[3] = 0;
        blk[2] = 0;
        blk[1] = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x30);
        cb = (void *)&func_ov055_020b6ee8;
        break;
    }
    return cb;
}
