extern void func_0202a634(int a, void *b, int c, int d);
extern int data_ov080_020b9b8c;
extern int data_ov080_020b9ba0;
extern int data_ov080_020b9bb4;
extern int data_ov080_020b9bc8;

void func_ov080_020b864c(int self) {
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
    func_0202a634((int)(blk + 4), &data_ov080_020b9b8c, 1, *(unsigned char *)(self + 9) + 7);
    func_0202a634((int)(blk + 0x114), &data_ov080_020b9ba0, 1, *(unsigned char *)(self + 9) + 7);
    func_0202a634((int)(blk + 0x224), &data_ov080_020b9bb4, 1, *(unsigned char *)(self + 9) + 7);
    for (j = 0, q = blk + 0x334; j < 3; j++, q += 0x110) {
        func_0202a634((int)q, &data_ov080_020b9bc8, 1, *(unsigned char *)(self + 9) + 7);
    }
}
