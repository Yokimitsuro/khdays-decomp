extern void func_ov092_020bb848(void);
extern void func_ov092_020bbc88(void);
extern int data_ov092_020bc4e0;

void *func_ov092_020bace4(int self, int req) {
    int *blk = (int *)(*(int *)&data_ov092_020bc4e0 + 0x194 + 0x2c00);
    void *cb = 0;
    switch (req) {
    default:
        break;
    case 0x21:
        blk[3] = 0;
        blk[4] = 0;
        blk[1] = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x2f);
        cb = (void *)&func_ov092_020bb848;
        break;
    case 0x23:
        blk[3] = 2;
        blk[4] = 5;
        (*(void (**)(int, int))(self + 0x664))(self, 0x2f);
        cb = (void *)&func_ov092_020bb848;
        break;
    case 0x22:
        blk[3] = 0;
        blk[2] = 0;
        blk[1] = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x30);
        cb = (void *)&func_ov092_020bbc88;
        break;
    }
    return cb;
}
