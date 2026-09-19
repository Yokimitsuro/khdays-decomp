/* Enter the ov125 enemy's recover state: seed the +0x3c counter with twice the owner's +0x2c
 * rate (30/15), drop the +0xc speed to 0x200 while the +0x13c height is under 0x4000, and
 * unless the +0x28 target's flag byte is set send the data_ov125_020d03cc[4..5] message pair
 * to the +0x24 hook (arg 4), fire action 4/1, reset the +0x2c timer, clear bit 1 of +0x34 and
 * register the recover think callback.
 *
 * `obj = *state` is a local declared right after `state`: that keeps the state load at the top
 * (merged with node[0] into the ROM's `ldm`) and lets the *state load float above the +0x3c
 * store; the later uses still read *state directly. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov125_020d03cc[];
extern void func_ov125_020cde04(void);

void func_ov125_020cdd3c(int *node) {
    int *state = (int *)node[1];
    int obj = *state;
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();

    state[0xf] = *(int *)(node[0] + 0x2c) * 0x1e / 15;
    if (*(int *)(obj + 0x13c) < 0x4000) {
        state[3] = 0x200;
    }
    if (*(unsigned char *)state[0xa] != 0) {
        return;
    }
    pp = pair;
    pp[1] = data_ov125_020d03cc[5];
    pp[0] = data_ov125_020d03cc[4];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    func_ov107_020c9264(*state, 4, 1);
    state[0xb] = 0;
    *(unsigned char *)(state + 0xd) &= ~2;
    func_0203c634(node, *(signed char *)(node + 8), func_ov125_020cde04);
}
