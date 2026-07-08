extern int func_02023eb4(int range);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov203_020d49a8(int node)
{
    int *state = *(int **)(node + 4);
    int obj;
    int start;
    int range;

    if (*(unsigned char *)state[0x44 / 4] != 0) {
        return;
    }

    obj = *state;
    start = *(int *)(obj + 0x224);
    range = *(int *)(obj + 0x228) - start;
    if (range < 0) {
        range = -range;
    }
    state[0x30 / 4] = start + func_02023eb4(range + 1);
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634((void *)node, *(signed char *)(node + 0x20), 0);
}
