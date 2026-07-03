extern int func_02023eb4(int);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov193_020d4c3c(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)state[1] == 0) {
        int lo = *(int *)(*state + 0x224);
        int hi = *(int *)(*state + 0x228);
        int d = hi - lo;
        if (d < 0) d = -d;
        state[0xd] = lo + func_02023eb4(d + 1);
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), (void *)0);
    }
}
