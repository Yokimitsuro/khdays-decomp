void *func_ov014_02080444(void *self)
{
    if (*(unsigned short *)((char *)self + 0x12) & 8) {
        return *(void **)((char *)self + 0x28);
    }
    return 0;
}
