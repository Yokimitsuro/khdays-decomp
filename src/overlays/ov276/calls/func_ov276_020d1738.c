extern int func_02023eb4(int max);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov276_020d0cdc(int a, int b);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov276_020d1808(void);

void func_ov276_020d1738(int *node) {
    int *state = (int *)node[1];
    state[20] = func_02023eb4(3) + 1;
    switch (state[23]) {
    case 0:
        func_ov107_020c9264(*state, 2, 0);
        func_ov276_020d0cdc(*state, 1);
        break;
    case 2:
        func_ov107_020c9264(*state, 8, 0);
        func_ov276_020d0cdc(*state, 6);
        break;
    case 3:
        func_ov107_020c9264(*state, 5, 0);
        func_ov276_020d0cdc(*state, 4);
        break;
    case 1:
        func_ov107_020c9264(*state, 0xb, 0);
        func_ov276_020d0cdc(*state, 8);
        break;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov276_020d1808);
}
