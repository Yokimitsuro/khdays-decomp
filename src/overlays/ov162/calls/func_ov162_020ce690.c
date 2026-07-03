extern void func_0203b9fc();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov162_020ce648(void);
extern void func_ov162_020ce738(void);
void func_ov162_020ce690(int *node) {
    int *state = (int *)node[1];
    int sub = *(int *)(*(int *)(*state + 0x3c4));
    state[1] = sub;
    *(void **)(sub + 0x6c) = func_ov162_020ce648;
    *(int **)(state[1] + 0x84) = state;
    *(unsigned int *)(state[1] + 0x5c) &= 0xfffffffd;
    func_0203b9fc(state[1], 2, 0, 0);
    func_0203b9fc(state[1], 0, 0, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov162_020ce738);
}
