struct hw60 { unsigned short lo : 8, hi : 8; };
struct v3 { int a, b, c; };
extern void func_0203c634(void *obj, int idx, void *value);
extern int data_02041dc8[];

void func_ov215_020d1164(int *node) {
    int *state = (int *)node[1];
    if ((((struct hw60 *)(*state + 0x60))->lo & 1) == 0) return;
    state[0x15] = 0;
    state[0x16] = 0;
    state[0x17] = 0;
    state[0x18] = 0;
    state[0x19] = 0;
    state[0x1a] = 0;
    *(struct v3 *)(state + 5) = *(struct v3 *)data_02041dc8;
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634(node, *(signed char *)(node + 8), (void *)0);
}
