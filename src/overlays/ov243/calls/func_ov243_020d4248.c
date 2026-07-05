struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *node, int idx, void *value);

void func_ov243_020d4248(int *node) {
    int *state = (int *)node[1];
    if (!(((struct hw60 *)(*state + 0x60))->lo & 1)) return;
    state[7] = state[9] * 0x14 + *(int *)(*state + 0x398);
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
