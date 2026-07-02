struct pair { unsigned short a, b; };
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern struct pair data_ov154_020d1ca0;
extern void func_ov154_020d1b04(void);
void func_ov154_020d1a54(int *node) {
    int *state = (int *)node[1];
    struct pair buf;
    void (*cb)();
    func_ov107_020c9264(*state, 3, 0);
    *(unsigned short *)(*state + 0x1ae) |= 0x40;
    state[7] = 0;
    *(signed char *)((char *)state + 0x24) = 0;
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[8] = v / 40;
    }
    buf = data_ov154_020d1ca0;
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, &buf, 4);
    func_0203c634(node, *(signed char *)(node + 8), func_ov154_020d1b04);
}
