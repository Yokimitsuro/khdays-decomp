extern void func_ov298_020d404c(void *node);
extern void func_ov107_020c9264(int obj, int arg1, int arg2);
extern int func_02023e80(void);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov298_020d4834(void);

void func_ov298_020d47c0(int node) {
    int *state = *(int **)(node + 4);

    func_ov298_020d404c((void *)node);
    func_ov107_020c9264(*state, 1, 0);
    state[0x14] = 0x900;
    state[0x23] = 0;
    state[0xc] = state[0xc] + state[0xa];
    state[0xd] = state[0xc];
    state[0x15] = 0x1fe0;
    state[0x17] = func_02023e80() + 0xff0;
    func_0203c634((void *)node, *(signed char *)(node + 0x20), func_ov298_020d4834);
}
