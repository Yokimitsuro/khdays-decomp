struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_02023eb4(int range);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov297_020d474c(int node) {
    int *state = *(int **)(node + 4);
    int obj = *state;
    int start;
    int delta;

    if ((((struct hw60 *)(obj + 0x60))->lo & 1) == 0) return;

    start = *(int *)(obj + 0x224);
    delta = *(int *)(obj + 0x228) - start;
    if (delta < 0) {
        delta = -delta;
    }

    state[0x10] = start + func_02023eb4(delta + 1);
    state[0x12] = 0;
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634((void *)node, *(signed char *)(node + 0x20), 0);
}
