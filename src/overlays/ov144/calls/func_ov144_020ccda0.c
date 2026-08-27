extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov144_020cd20c(void);
extern void func_ov144_020cce0c(void);
extern void func_ov144_020cd084(void);

void func_ov144_020ccda0(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    state[2] = *state + 0xb0;
    func_0203c634(node, 1, func_ov144_020cd20c);
    func_0203c634(node, 0, func_ov144_020cce0c);
    func_0203c634(node, 2, func_ov144_020cd084);
}
