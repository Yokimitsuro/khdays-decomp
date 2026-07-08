extern void func_ov297_020d4168(void *node);
extern void func_ov107_020c9264(int obj, int arg1, int arg2);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov297_020d4964(void);

void func_ov297_020d48fc(int node) {
    int *state = *(int **)(node + 4);

    func_ov297_020d4168((void *)node);
    func_ov107_020c9264(*state, 1, 0);
    state[0x14] = 0x900;
    state[0x22] = 0;
    state[0xc] = state[0xc] + state[0xa];
    state[0xd] = state[0xc];
    state[0x15] = 0x1fe0;
    func_0203c634((void *)node, *(signed char *)(node + 0x20), func_ov297_020d4964);
}
