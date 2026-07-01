void func_ov054_020b6344(void *self, int value)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x10c) = 0;
    *(int *)((char *)self + 0x110) = value;
}
