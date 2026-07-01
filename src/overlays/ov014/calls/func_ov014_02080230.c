void func_ov014_02080230(void *self, unsigned char *value)
{
    if (*value == 1) {
        *(unsigned char *)((char *)self + 0x134) = 2;
    }
}
