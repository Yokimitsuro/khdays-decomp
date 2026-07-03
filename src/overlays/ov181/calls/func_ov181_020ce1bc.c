extern void func_0202f384();
extern void func_01ffa724();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern int data_02042258[];
extern void func_ov181_020ce24c(void);
void func_ov181_020ce1bc(int *node) {
    int *state = (int *)node[1];
    state[0x1b] = state[0x1b] + *(int *)(*node + 0x2c);
    if (*(unsigned char *)state[3] != 0) return;
    func_0202f384(state + 0x1e, *state + 0xa0, data_02042258);
    func_01ffa724(0x800, state + 0x1e, state + 0x1e);
    state[0x1f] = 0x400;
    func_ov107_020c9264(*state, 0xe, 0);
    state[7] = 0;
    *(signed char *)((char *)state + 0x50) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov181_020ce24c);
}
