struct b { unsigned char bit0 : 1; };
int func_ov002_02054c60(int p)
{
    return ((struct b *)(p + 0x2c))->bit0;
}
