extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov242_020d45d4(void);

void func_ov242_020d4580(int *node) {
    int *n0 = (int *)node[0];
    int *state = (int *)node[1];
    state[0xb] -= n0[0xb];
    if (*(unsigned char *)(*(int *)(*state + 0x384) + 0xad) != 0) return;
    func_ov107_020c9264(*state, 0, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov242_020d45d4);
}
