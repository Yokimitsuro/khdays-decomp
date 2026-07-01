void func_ov088_020bafc0(void *self, int value)
{
    *(int *)((char *)self + 4) = 3;
    *(int *)((char *)self + 0x110) = value;
    *(int *)((char *)self + 0x114) = 0;
}
