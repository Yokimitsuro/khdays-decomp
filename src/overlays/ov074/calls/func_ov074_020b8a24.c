void func_ov074_020b8a24(void *self, int value)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x10c) = 0;
    *(int *)((char *)self + 0x110) = value;
}
