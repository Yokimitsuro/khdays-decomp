extern int func_ov262_020d402c(int *state, int flag);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov262_020d484c(void);

void func_ov262_020d47f0(int *node) {
    int *state = (int *)node[1];
    if (*(int *)(*state + 0x3a8) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x1c] = func_ov262_020d402c(state, *(unsigned char *)(*state + 0x3ac));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov262_020d484c);
}
