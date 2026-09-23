/* Wind-up tick of an ov235 state: the +0x54 timer accumulates the owner's rate; past 0x333,
 * once (+0x65), reaction +0x3c8 (as a halfword) mode 0xb fires at the +4 point. Once the +0xc
 * idle byte clears, animation 0x11 plays, the flag clears and the tick hands over to
 * func_ov235_020cf700. */
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020cf700(int *node);

void func_ov235_020cf664(int *node)
{
    int *state = (int *)node[1];

    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x65) == 0 && state[0x15] >= 0x333) {
        func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0xb, (void *)state[1]);
        *((unsigned char *)state + 0x65) = 1;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x11, 0);
    *((unsigned char *)state + 0x65) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020cf700);
}
