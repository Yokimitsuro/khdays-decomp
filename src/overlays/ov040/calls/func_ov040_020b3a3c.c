void func_ov040_020b3a3c(void *self, int value)
{
    *(int *)self = 1;
    *(int *)((char *)self + 0x110) = 0;
    *(int *)((char *)self + 0x114) = value;
}
