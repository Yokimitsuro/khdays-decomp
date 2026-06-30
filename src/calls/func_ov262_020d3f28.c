void func_ov262_020d3f28(void *self, int value)
{
    *(int *)((char *)self + 0x3a8) = value;
    *(unsigned char *)((char *)self + 0x1c9) = 5;
    *(unsigned char *)((char *)self + 0x1c7) = 5;
}
