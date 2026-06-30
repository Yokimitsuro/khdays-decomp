void func_ov041_020b3c70(void *self)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x10c) = 0;
}
