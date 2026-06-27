extern void DC_FlushRange(const void *addr, unsigned size);
extern void *data_02041934[];

int func_020114ac(int *job, int do_flush) {
    int (*fn)(void *, int, int);
    fn = (int (*)(void *, int, int))data_02041934[job[0]];
    if (do_flush) DC_FlushRange((void *)job[1], (unsigned)job[3]);
    return fn((void *)job[1], job[2], job[3]);
}
