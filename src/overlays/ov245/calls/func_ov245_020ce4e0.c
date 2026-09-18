/* func_ov245_020ce4e0 -- rise tick: the state's +0x14 height follows +0x20 and the +0x3c limit is
 * 5.0; once the node's +8 origin plus that height reaches the limit plus 15.0 the actor's +0x438 child is
 * released (020d488c), pose 7 plays, the +0x4c8 anchor's motion 1 starts and the node moves to
 * 020ce560. */
extern void func_ov245_020d488c(int child);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c9ee8(int item, int motion, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020ce560(void);

void func_ov245_020ce4e0(int *node) {
    int *state = (int *)node[1];

    state[5] = state[8];
    state[0xf] = 0x5000;
    if (*(int *)(state[2] + 8) + state[5] < state[0xf] + 0xf000) {
        return;
    }
    func_ov245_020d488c(*(int *)(*state + 0x438));
    func_ov107_020c9264(*state, 7, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x4c8), 1, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020ce560);
}
