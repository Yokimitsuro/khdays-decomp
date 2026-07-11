extern void GXS_SetGraphicsMode(int mode);

/* Pick the sub-engine graphics mode from a table indexed by DISPCNT-B mode bits. */
void func_02012904(unsigned char *table)
{
    volatile unsigned int *reg_dispcnt_b = (volatile unsigned int *)0x04001000;
    int mode = (*reg_dispcnt_b) & 7;
    int v = table[mode];
    if (v >= 8) v -= 8;
    GXS_SetGraphicsMode(v);
}
