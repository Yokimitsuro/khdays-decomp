extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov298_020d54cc(void);

void func_ov298_020d5484(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 0, 1);
    state[0x14] = 0x900;
    state[0xe] = 0x27d8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov298_020d54cc);
}
