void func_020102c0(void **out, char *node)
{
    unsigned short offset = (*(unsigned short *)(node + 2) >> 8) & 0x7f;
    char *base = node + 0x10;

    out[0] = node - offset;
    out[1] = (void *)(*(int *)(node + 4) + (int)base);
}
