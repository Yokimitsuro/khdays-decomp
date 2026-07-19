extern void func_0202a634(int a, void *b, int c, int d);
extern int data_ov097_020bc24c;
extern int data_ov097_020bc260;
extern int data_ov097_020bc274;
extern int data_ov097_020bc288;

void func_ov097_020bad0c(int self) {
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
    func_0202a634((int)(blk + 4), &data_ov097_020bc24c, 1, *(unsigned char *)(self + 9) + 7);
    func_0202a634((int)(blk + 0x114), &data_ov097_020bc260, 1, *(unsigned char *)(self + 9) + 7);
    func_0202a634((int)(blk + 0x224), &data_ov097_020bc274, 1, *(unsigned char *)(self + 9) + 7);
    for (j = 0, q = blk + 0x334; j < 3; j++, q += 0x110) {
        func_0202a634((int)q, &data_ov097_020bc288, 1, *(unsigned char *)(self + 9) + 7);
    }
}
