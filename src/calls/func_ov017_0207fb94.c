void func_ov017_0207fb94(void *self, unsigned char *value)
{
    if (*value == 1) {
        *(unsigned char *)((char *)self + 0x4da) = 2;
    }
}
