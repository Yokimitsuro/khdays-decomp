extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov195_020d2b98[];
extern void func_ov195_020d1e70(void);
void func_ov195_020d1e08(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    func_ov107_020c9264(*state, 6, 0);
    pp = pair;
    pp[1] = data_ov195_020d2b98[1];
    pp[0] = data_ov195_020d2b98[0];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    func_0203c634(node, *(signed char *)(node + 8), func_ov195_020d1e70);
}
