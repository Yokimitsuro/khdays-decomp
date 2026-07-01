int func_ov095_020bba84(void *unused, void *self)
{
    *(unsigned char *)((char *)self + 2) = 4;
    *(int *)((char *)self + 4) = 0x3000;
    return 0;
}
