extern void func_0203b9fc(void *child, int cmd, int arg, int flag);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov162_020ce45c(void);
extern void func_ov162_020ce59c(void);

void func_ov162_020ce4b4(int *node) {
    int *state = (int *)node[1];
    state[1] = *(int *)(*(int *)(*state + 0x3c4) + 0x20);
    *(void **)(state[1] + 0x6c) = func_ov162_020ce45c;
    *(int **)(state[1] + 0x84) = state;
    *(int *)(state[1] + 0x5c) &= ~2;
    state[3] = 6;
    func_0203b9fc((void *)state[1], 0, 0, 1);
    func_0203b9fc((void *)state[1], 2, 0, 1);
    func_0203b9fc((void *)state[1], 4, (short)state[3], 1);
    state[2] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov162_020ce59c);
}
