extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov196_020d67d8[];
extern void func_ov196_020d5ab0(void);
void func_ov196_020d5a48(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    func_ov107_020c9264(*state, 6, 0);
    pp = pair;
    pp[1] = data_ov196_020d67d8[1];
    pp[0] = data_ov196_020d67d8[0];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    func_0203c634(node, *(signed char *)(node + 8), func_ov196_020d5ab0);
}
