/* func_ov253_020ce210 -- roar tick: the +0x1c timer runs up by the frame step; past 5.047 each
 * remaining +0x38 shot fires reaction 0x16b/0xb at the actor's +0xb0. Once the +4 item's
 * animation is free pose 9 (flag 1) plays, the timer restarts at 10.0 and the node moves to
 * 020ce2a8. */
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020ce2a8(void);

void func_ov253_020ce210(int *node) {
    int *state = (int *)node[1];

    state[7] += *(int *)(node[0] + 0x2c);
    if (state[7] >= 0x50c0 && *((unsigned char *)state + 0x38) != 0) {
        *((unsigned char *)state + 0x38) -= 1;
        func_ov107_020c5af8(*state, 0x16b, 0xb, (void *)(*state + 0xb0));
    }
    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 9, 1);
    state[7] = 0xa000;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020ce2a8);
}
