extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov145_020cf028(void);
extern void func_ov145_020cec28(void);
extern void func_ov145_020ceea0(void);

void func_ov145_020cebbc(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    state[2] = *state + 0xb0;
    func_0203c634(node, 1, func_ov145_020cf028);
    func_0203c634(node, 0, func_ov145_020cec28);
    func_0203c634(node, 2, func_ov145_020ceea0);
}
