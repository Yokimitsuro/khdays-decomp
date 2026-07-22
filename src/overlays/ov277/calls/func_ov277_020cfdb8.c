/* Enemy hurt hook: cancel the current action (mode 1), send the second pair of
 * knockback values from the table as a 4-byte message to the model's handler at
 * +0x24 (when it has one), clear the hit accumulator at +0x1c and register the
 * recovery handler. */
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov277_020d36bc[];
extern void func_ov277_020cfe28(void);

void func_ov277_020cfdb8(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();

    func_ov107_020c9264(*state, 1, 0);

    pp = pair;
    pp[1] = data_ov277_020d36bc[3];
    pp[0] = data_ov277_020d36bc[2];

    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);

    state[7] = 0;

    func_0203c634(node, *(signed char *)(node + 8), func_ov277_020cfe28);
}
