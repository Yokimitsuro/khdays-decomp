extern void FX_DivAsync(int num, int denom);

long long func_01ff8a14(int num, int denom)
{
    FX_DivAsync(num, denom);
    while (*(volatile unsigned short *)0x04000280 & 0x8000) {
    }
    return *(long long *)0x040002a0;
}
