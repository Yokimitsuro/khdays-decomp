extern void func_01ffa724();
extern void func_01ff8bc4();
extern void func_ov107_020c5c54();
extern void func_ov107_020c9264();
extern void func_ov276_020d0cdc();
extern void func_0203c634(void *obj, int idx, void *value);
extern short data_0203d210[];
extern void func_ov276_020d2644(void);
void func_ov276_020d2540(int *node) {
    int *state = (int *)node[1];
    if (state[2] != 0) {
        int vec[3];
        int angle = (int)(((unsigned)(((long long)(int)(unsigned)state[0x10] * 0x28be60db9391LL +
                           0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
        vec[0] = (int)data_0203d210[angle * 2];
        vec[1] = 0;
        vec[2] = (int)data_0203d210[angle * 2 + 1];
        func_01ffa724(*(int *)(*state + 0x480), vec, vec);
        func_01ff8bc4(state[2] + 0x190, vec, vec);
        func_ov107_020c5c54(*state, vec);
        state[2] = 0;
    }
    func_ov107_020c9264(*state, 0x13, 0);
    func_ov276_020d0cdc(*state, 0xd);
    state[0x13] = 0;
    *(signed char *)((char *)state + 0x61) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov276_020d2644);
}
