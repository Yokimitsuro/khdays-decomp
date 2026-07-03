void func_ov022_02090360(int p)
{
    if (*(unsigned char *)(p + 2) != 0)
        *(unsigned short *)p |= 0x20;
}
