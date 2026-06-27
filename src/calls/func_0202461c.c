extern int GX_GetBankForBGExtPltt(int arg);

void func_0202461c(int arg0, int arg1, int arg2, int arg3) {
    int bank = GX_GetBankForBGExtPltt(arg0);
    int bit;
    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        bit = 0;
    } else {
        bit = 1;
    }
    *(volatile unsigned short *)0x400100a =
        (*(volatile unsigned short *)0x400100a & 0x43)
        | (arg0 << 14)
        | (arg1 << 7)
        | (arg2 << 8)
        | (arg3 << 2)
        | (bit << 13);
}
