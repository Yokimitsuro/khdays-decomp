void *func_ov014_02080430(void *self)
{
    if (*(unsigned short *)((char *)self + 0x12) & 8) {
        return (char *)self + 0x1c;
    }
    return 0;
}
