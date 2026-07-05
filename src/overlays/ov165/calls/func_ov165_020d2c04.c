extern int func_02023eb4(int max);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov165_020d2c04(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)state[0x16] != 0) return;
    int base = *(int *)(*state + 0x224);
    int d = *(int *)(*state + 0x228) - base;
    if (d < 0) d = -d;
    state[0xd] = base + func_02023eb4(d + 1);
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
