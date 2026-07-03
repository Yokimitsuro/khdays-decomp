void func_ov015_02080408(int p, int q)
{
    if (*(unsigned char *)q == 1)
        *(unsigned char *)(p + 0x50) = 2;
}
