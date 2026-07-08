extern int func_02023eb4(int range);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov204_020d07f8(int node)
{
    int *state = *(int **)(node + 4);
    int start;
    int range;
    int flags;

    flags = *(unsigned short *)(*state + 0x60);
    flags = (unsigned int)(flags << 24) >> 24;
    if ((flags & 1) == 0) {
        return;
    }

    start = *(int *)(*state + 0x224);
    range = *(int *)(*state + 0x228) - start;
    if (range < 0) {
        range = -range;
    }
    state[0x30 / 4] = start + func_02023eb4(range + 1);
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634((void *)node, *(signed char *)(node + 0x20), 0);
}
