typedef struct {
    unsigned short count;
    unsigned short flags;
    char *base;
} Table;

void *func_020118c4(Table *t, unsigned int idx)
{
    if (idx >= t->count)
        return 0;
    if (t->flags & 1)
        return t->base + idx * 16;
    return t->base + idx * 8;
}
