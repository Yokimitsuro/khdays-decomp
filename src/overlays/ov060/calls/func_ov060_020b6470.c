void func_ov060_020b6470(void *self)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x10c) = 0;
}
