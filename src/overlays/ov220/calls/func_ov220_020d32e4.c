extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov107_020c9264(int actor, int mode, int flag);
extern int func_ov220_020d2448(void *node);
extern void func_ov220_020d333c(void);

void func_ov220_020d32e4(int node)
{
    int *state = *(int **)(node + 4);

    if (func_ov220_020d2448((void *)node) < 0) {
        func_0203c634((void *)node, *(signed char *)(node + 0x20), 0);
        return;
    }

    state[3] = state[4];
    func_ov107_020c9264(*state, 6, 0);
    func_0203c634((void *)node, *(signed char *)(node + 0x20), func_ov220_020d333c);
}
