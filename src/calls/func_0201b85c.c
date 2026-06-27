extern void *func_02010b88(void *start, unsigned int size, int flags);
extern int WM_EndKeySharing_0x02010bc0(void *p);
extern int func_0201bb38(void *p, void *arg);

void *func_0201b85c(unsigned int start, unsigned int size)
{
    unsigned int end;
    unsigned int aligned = (start + 3);
    end = start + size;
    aligned &= ~3u;
    unsigned int remaining;
    void *inner;

    if (aligned > end)
        return (void *)0;

    remaining = end - aligned;
    if (remaining < 0x10)
        return (void *)0;

    inner = func_02010b88((void *)(aligned + 0x10), remaining - 0x10, 0);
    if (inner == (void *)0)
        return (void *)0;

    if (func_0201bb38((void *)aligned, inner))
        return (void *)aligned;

    WM_EndKeySharing_0x02010bc0(inner);
    return (void *)0;
}
