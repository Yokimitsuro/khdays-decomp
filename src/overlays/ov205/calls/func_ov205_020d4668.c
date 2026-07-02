extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov205_020d46c4(void);
void func_ov205_020d4668(int *node) {
    int v = *(int *)(*node + 0x2c) * 0x1e;
    int *state = (int *)node[1];
    state[15] = v / 5;
    func_ov107_020c9264(*state, 1, 1);
    func_0203c634(node, *(signed char *)(node + 8), func_ov205_020d46c4);
}
