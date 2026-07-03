extern void func_01ffa724();
extern void func_0203c634(void *obj, int idx, void *value);
extern short data_0203d210[];
extern void func_ov143_020d4a5c(void);
void func_ov143_020d4988(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    int angle = (int)(((unsigned)(((long long)(int)(unsigned)state[2] * 0x28be60db9391LL +
                       0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    buf[0] = (int)data_0203d210[angle * 2];
    buf[1] = 0;
    buf[2] = (int)data_0203d210[angle * 2 + 1];
    func_01ffa724(0x300, buf, state + 6);
    {
        int t = state[0xc] + *(int *)(*node + 0x2c);
        state[0xc] = t;
        if (t < 0x1000) return;
    }
    *(char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov143_020d4a5c);
}
