/* Play anim 7, send the cue at data_ov277_020d36bc entry 9 through the actor's +0x24 hook,
 * clear the low nibble of the actor's +0x420 word, the +0x1c word and the +9 byte, then
 * dispatch to 020d04b4. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov277_020d36bc[];
extern void func_ov277_020d044c(void);

void func_ov277_020d03c8(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();

    func_ov107_020c9264(*state, 7, 0);
    pp = pair;
    pp[1] = data_ov277_020d36bc[19];
    pp[0] = data_ov277_020d36bc[18];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    *(int *)(*state + 0x420) &= ~0xf;
    state[7] = 0;
    *((unsigned char *)state + 9) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov277_020d044c);
}
