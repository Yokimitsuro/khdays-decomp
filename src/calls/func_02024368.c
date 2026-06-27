extern int GX_GetBankForBGExtPltt(int arg);
extern void func_020056b4(int a, int b, int c);

void func_02024368(int arg0, int arg1, int arg2, int arg3) {
    int bank = GX_GetBankForBGExtPltt(arg0);
    int bit;
    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        bit = 0;
    } else {
        bit = 1;
    }
    int t = (*(volatile unsigned int *)0x4000000 & 8) ? 1 : 0;
    func_020056b4(1, *(volatile unsigned int *)0x4000000 & 7, t ? 1 : 0);
    *(volatile unsigned short *)0x400000a =
        (*(volatile unsigned short *)0x400000a & 0x43)
        | (arg0 << 14)
        | (arg1 << 7)
        | (arg2 << 8)
        | (arg3 << 2)
        | (bit << 13);
}
