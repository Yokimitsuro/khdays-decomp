void *func_02010140(char *base, char *table)
{
    if (table == 0) {
        return *(void **)(base + 4);
    }
    return *(void **)(table + *(unsigned short *)(base + 0xa));
}
