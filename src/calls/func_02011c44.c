int func_02011c44(void *self, unsigned int idx)
{
    char *table = *(char **)((char *)self + 0x1c);
    unsigned int count = *(unsigned short *)table;
    char *entry;
    if (idx >= count) goto fail;
    entry = *(char **)(table + 0xc) + (idx << 3);
    *(char **)self = entry;
    if (*(unsigned short *)(entry + 4) != 0)
        *(char **)((char *)self + 4) = entry;
    return 1;
fail:
    return 0;
}
