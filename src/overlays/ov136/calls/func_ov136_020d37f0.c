extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov136_020d39e4[];
extern void func_ov136_020d3858(void);
void func_ov136_020d37f0(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    func_ov107_020c9264(*state, 6, 0);
    pp = pair;
    pp[1] = data_ov136_020d39e4[1];
    pp[0] = data_ov136_020d39e4[0];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    func_0203c634(node, *(signed char *)(node + 8), func_ov136_020d3858);
}
