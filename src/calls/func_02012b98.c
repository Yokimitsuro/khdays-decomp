extern int GX_GetBankForBGExtPltt(void);
extern void func_020128c0(void *);
extern void func_02012904(void *);

extern char data_02041a6c[];
extern unsigned short *data_02041ac0[];

void func_02012b98(int a, int b, int c, int d, int e) {
    int flag = 0;
    int idx = a & 3;
    unsigned short *reg;
    unsigned short v;
    if (a <= 3) {
        int bank = GX_GetBankForBGExtPltt();
        if (bank != 0x20 && bank != 0x10 && bank != 0x60) flag = 1;
        func_020128c0(data_02041a6c + (idx << 3));
    } else {
        func_02012904(data_02041a6c + (idx << 3));
    }
    reg = data_02041ac0[a];
    v = (unsigned short)((b << 14) | (d << 8) | (e << 2) | (flag << 13) | (c << 7));
    *reg = (*reg & 0x43) | v;
}
