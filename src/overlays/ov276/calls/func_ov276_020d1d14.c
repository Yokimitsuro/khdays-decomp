extern void func_01ff9010();
extern void func_01ff93bc();
extern void func_ov107_020c9264();
extern void func_ov276_020d0cdc();
extern void func_0203c634(void *obj, int idx, void *value);
extern short data_0203d210[];
extern void func_ov276_020d1df8(void);
void func_ov276_020d1d14(int *node) {
    int *state = (int *)node[1];
    int mtx[9];
    int angle;
    state[0x13] = state[0x13] + *(int *)(*node + 0x2c);
    angle = (int)(((unsigned)(((long long)(int)(unsigned)state[0x10] * 0x28be60db9391LL +
                   0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    func_01ff9010(mtx, (int)data_0203d210[angle * 2], (int)data_0203d210[angle * 2 + 1]);
    func_01ff93bc(*(int *)(*state + 0x470) + 0x2c, mtx, state + 4);
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0xd, 0);
        func_ov276_020d0cdc(*state, 10);
        func_0203c634(node, *(signed char *)(node + 8), func_ov276_020d1df8);
    }
}
