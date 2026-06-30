void func_ov261_020d02e8(void *self, int value)
{
    *(int *)((char *)self + 0x3a8) = value;
    *(unsigned char *)((char *)self + 0x1c9) = 5;
    *(unsigned char *)((char *)self + 0x1c7) = 5;
}
