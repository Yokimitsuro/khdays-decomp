struct b { unsigned char b0 : 1; };
int func_ov002_02077040(int p)
{
    return ((struct b *)(p + 0x1b6))->b0 ? 0 : p + 0x1c;
}
