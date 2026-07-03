extern void func_ov107_020c9264();
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov142_020d2610[];
extern void func_ov142_020d13f0(void);
void func_ov142_020d132c(int *node) {
    int *state = (int *)node[1];
    unsigned short buf[2];
    unsigned short *pp;
    void (*cb)();
    if (state[5] >= 0x100) return;
    pp = buf;
    pp[1] = data_ov142_020d2610[5];
    pp[0] = data_ov142_020d2610[4];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[4] = v / 10;
    }
    func_ov107_020c9264(*state, 5, 0);
    state[0xc] = 0;
    *(signed char *)((char *)state + 0x48) = 0;
    func_ov107_020c5af8(*state, 0x11e, 4, *(int *)(*state + 0x394) + 0x14);
    func_0203c634(node, *(signed char *)(node + 8), func_ov142_020d13f0);
}
