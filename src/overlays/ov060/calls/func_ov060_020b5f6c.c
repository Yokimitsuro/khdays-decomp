extern void func_0202a634(int a, void *b, int c, int d);
extern int data_ov060_020b74ac;
extern int data_ov060_020b74c0;
extern int data_ov060_020b74d4;
extern int data_ov060_020b74e8;

void func_ov060_020b5f6c(int self) {
    char *blk = (char *)(self + 0x84 + 0x2c00);
    int i;
    char *q;
    char *p;
    int j;
    *(int *)(self + 0x2000 + 0xc84) = 0;
    *(int *)(blk + 0x110) = 0;
    *(int *)(blk + 0x220) = 0;
    for (i = 0, p = blk; i < 3; i++, p += 0x110) {
        *(int *)(p + 0x330) = 0;
    }
    func_0202a634((int)(blk + 4), &data_ov060_020b74ac, 1, *(unsigned char *)(self + 9) + 7);
    func_0202a634((int)(blk + 0x114), &data_ov060_020b74c0, 1, *(unsigned char *)(self + 9) + 7);
    func_0202a634((int)(blk + 0x224), &data_ov060_020b74d4, 1, *(unsigned char *)(self + 9) + 7);
    for (j = 0, q = blk + 0x334; j < 3; j++, q += 0x110) {
        func_0202a634((int)q, &data_ov060_020b74e8, 1, *(unsigned char *)(self + 9) + 7);
    }
}
