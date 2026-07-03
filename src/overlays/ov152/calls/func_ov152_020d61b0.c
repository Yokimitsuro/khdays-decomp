extern void func_ov107_020c9264();
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov152_020d64b4[];
extern void func_ov152_020d6274(void);
void func_ov152_020d61b0(int *node) {
    int *state = (int *)node[1];
    unsigned short buf[2];
    unsigned short *pp;
    void (*cb)();
    if (state[5] >= 0x100) return;
    pp = buf;
    pp[1] = data_ov152_020d64b4[5];
    pp[0] = data_ov152_020d64b4[4];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[4] = v / 10;
    }
    func_ov107_020c9264(*state, 5, 0);
    state[0xc] = 0;
    *(signed char *)((char *)state + 0x4c) = 0;
    func_ov107_020c5af8(*state, 0x14f, 4, *(int *)(*state + 0x394) + 0x14);
    func_0203c634(node, *(signed char *)(node + 8), func_ov152_020d6274);
}
