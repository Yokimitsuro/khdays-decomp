extern void FX_InvAsync(int x);

long long func_01ff8a50(int x) {
    FX_InvAsync(x);
    while (*(volatile unsigned short *)0x04000280 & 0x8000) ;
    return *(long long *)0x040002a0;
}
