extern void func_0203b9fc(int obj, int idx, int a, int b);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov149_020d05dc(void);
extern void func_ov149_020d0718(void);
void func_ov149_020d0648(int *node) {
    void *cb = (void *)func_ov149_020d05dc;
    int *state = (int *)node[1];
    int sub = *(int *)(*(int *)(*state + 0x390));
    state[1] = sub;
    *(void **)(state[1] + 0x6c) = cb;
    *(int **)(state[1] + 0x84) = state;
    func_0203b9fc(state[1], 0, 0, 0);
    func_0203b9fc(state[1], 4, 0, 0);
    func_0203b9fc(state[1], 1, 0, 0);
    func_0203b9fc(state[1], 2, 0, 0);
    *(unsigned int *)(state[1] + 0x5c) &= ~2;
    func_0203c634(node, *(signed char *)(node + 8), func_ov149_020d0718);
}
