void func_ov080_020b8b50(void *self)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x10c) = 0;
}
