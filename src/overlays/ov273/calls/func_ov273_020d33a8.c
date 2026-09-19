/* Attack wind-up tick: sets the +0x48 rate to 30/5 of the frame step; while the +0x6a latch is
 * clear the +0x70 timer runs and past 0xbbb the latch is set and effect 0x162 (kind 0xb) is
 * spawned at the +4 anchor. Unless the +8 flag byte is set, pose 0x15 plays and the node moves
 * to 020cf81c. */
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov273_020d345c(void);

void func_ov273_020d33a8(int *node) {
    int *state = (int *)node[1];
    state[0x12] = *(int *)(node[0] + 0x2c) * 30 / 5;
    if (*((unsigned char *)state + 0x6a) == 0) {
        state[0x1c] += *(int *)(node[0] + 0x2c);
        if (state[0x1c] >= 0xbbb) {
            *((unsigned char *)state + 0x6a) = 1;
            func_ov107_020c5af8(state[0], 0x162, 0xb, (void *)state[1]);
        }
    }
    if (*(unsigned char *)state[2] != 0) return;
    func_ov107_020c9264(*state, 0x15, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov273_020d345c);
}
