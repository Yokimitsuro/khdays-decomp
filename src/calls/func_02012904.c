extern void GXS_SetGraphicsMode(int mode);

void func_02012904(unsigned char *table)
{
    int mode = (*(volatile unsigned int *)0x04001000) & 7;
    int v = table[mode];
    if (v >= 8) v -= 8;
    GXS_SetGraphicsMode(v);
}
