/* Charge wind-up tick: counts the +0x1c timer up by the scene step; once past 0x55a0 (latched
 * at +9) effect 0x165 of kind 7 fires at the actor's +0x3d8 item's +0x14 point. When the +0x30
 * child's byte clears, the timer resets, bit 16 of +0x18 clears, pose 1 plays (looping) and the
 * node moves to 020d0b10. */
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov277_020d0aa8(void);

void func_ov277_020d09fc(int *node) {
    int *state = (int *)node[1];
    int zero;

    state[7] += *(int *)(*node + 0x2c);
    if (*((unsigned char *)state + 9) == 0) {
        if (state[7] >= 0x55a0) {
            func_ov107_020c5af8(*state, 0x165, 7, (void *)(*(int *)(*state + 0x3d8) + 0x14));
            *((unsigned char *)state + 9) = 1;
        }
    }
    if (*(unsigned char *)state[0xc] != 0) {
        return;
    }
    zero = 0;
    state[7] = zero;
    state[6] &= zero - 0x10000;
    func_ov107_020c9264(*state, 0, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov277_020d0aa8);
}
