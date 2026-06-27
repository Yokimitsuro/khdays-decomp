void *func_02010344(void **list, unsigned short value)
{
    char *node = list[0];

    *(unsigned short *)node = value;
    *(unsigned short *)(node + 2) = 0;
    *(int *)(node + 4) = (char *)list[1] - (node + 0x10);
    *(int *)(node + 8) = 0;
    *(int *)(node + 0xc) = 0;

    return node;
}
