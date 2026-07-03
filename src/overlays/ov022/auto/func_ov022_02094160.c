void func_ov022_02094160(int p)
{
    if (*(unsigned char *)p & 8)
        *(int *)(p + 0x110) = 0xc000;
}
