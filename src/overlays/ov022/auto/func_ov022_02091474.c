struct b { unsigned char b0 : 1; };
void func_ov022_02091474(int p)
{
    if (p == 0)
        return;
    if (((struct b *)(*(int *)(p + 8) + 0x694))->b0 == 0)
        return;
    ((void (*)(int))(*(int *)(p + 0x24)))(p);
}
