extern void func_ov022_020a2954(int self);
extern void func_ov097_020bba18(void);
extern void func_ov097_020bbdc0(void);

void *func_ov097_020bac98(int self, int a) {
    int *blk = (int *)(self + 0x84 + 0x2c00);
    void *cb = 0;
    switch (a) {
    default:
        break;
    case 0x21:
        *(int *)((char *)blk + 0x660) = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x2f);
        *(short *)(self + 0x64) = 0x2000;
        func_ov022_020a2954(self);
        cb = (void *)&func_ov097_020bba18;
        break;
    case 0x22:
        *(int *)((char *)blk + 0x660) = 0;
        (*(void (**)(int, int))(self + 0x664))(self, 0x30);
        cb = (void *)&func_ov097_020bbdc0;
        break;
    }
    return cb;
}
