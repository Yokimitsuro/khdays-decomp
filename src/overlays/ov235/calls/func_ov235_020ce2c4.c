/* Target check of an ov235 state: the nearest target (020cab14) becomes +0x5c; without one
 * sub-state 2 is requested and the tick ends. Otherwise animation 4 plays, the +0x3a8 part plays
 * motion 3, reaction +0x3c8 (as a halfword) mode 2 fires at the +4 point and the tick hands over to
 * func_ov235_020ce354. */
extern int func_ov107_020cab14(int obj, int kind);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020ce354(int *node);

void func_ov235_020ce2c4(int *node)
{
    int *state = (int *)node[1];

    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*state, 4, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 3, 0);
    func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 2, (void *)state[1]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020ce354);
}
