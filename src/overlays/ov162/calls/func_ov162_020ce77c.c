extern void func_0203b9fc();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov162_020ce7dc(void);
void func_ov162_020ce77c(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x310) == 0xa) return;
    func_0203b9fc(state[1], 2, 1, 0);
    func_0203b9fc(state[1], 0, 2, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov162_020ce7dc);
}
