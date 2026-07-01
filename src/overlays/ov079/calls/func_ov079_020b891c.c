void func_ov079_020b891c(void *self, int value)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x110) = 0;
    *(int *)((char *)self + 0x114) = value;
}
