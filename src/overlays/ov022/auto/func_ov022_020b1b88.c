int func_ov022_020b1b88(int p)
{
    int b = *(unsigned char *)(p + 8);
    int r = 1;
    if (b != 0 && b != 3)
        r = 0;
    return r;
}
