void func_ov096_020bafdc(void *self, int value)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x110) = 0;
    *(int *)((char *)self + 0x114) = value;
}
