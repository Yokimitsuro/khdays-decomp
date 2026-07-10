extern int func_ov022_02094678(unsigned int arg0, unsigned int arg1);
extern int func_ov022_02095618(int arg0);
int func_ov022_020946e4(int arg0) {
    int r;
    int base = *(int *)(arg0 + 0x328);
    r = func_ov022_02094678(*(unsigned short *)(arg0 + 0x336), *(unsigned short *)(base + 0x16));
    *(int *)(arg0 + 0x338) = r;
    if (func_ov022_02095618(arg0) == 2)
        r += func_ov022_02094678(*(unsigned short *)(base + 0x12), *(unsigned short *)(base + 0x16));
    return r;
}
