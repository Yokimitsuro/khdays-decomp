extern int func_ov002_0207298c(void);
extern void func_0203355c(int id);
extern int func_02025694(void *base, unsigned int bit);

extern int data_ov002_0207fa10;
extern unsigned char data_ov002_0207e610[];

void func_ov002_02072b58(void) {
    char *ctx = *(char **)&data_ov002_0207fa10;
    int i;
    unsigned char *row;

    if (func_ov002_0207298c() == 7 || func_ov002_0207298c() == 4) {
        func_0203355c(0x19);
    }
    row = data_ov002_0207e610;
    for (i = 0; i <= 0xe; i++) {
        if (func_02025694(ctx + 0x229c, i) != 0) {
            func_0203355c(row[1]);
        }
        row += 3;
    }
}
