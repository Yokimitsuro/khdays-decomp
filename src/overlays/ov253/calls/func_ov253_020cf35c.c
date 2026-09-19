/* func_ov253_020cf35c -- idle entry: sets pose 0 (flag 1), arms the +0x1c timer with 5.0 plus a
 * random 5.0, raises bit 0 of the +0x3b4 item's +8 low byte, clears the actor's +0x3bc and moves
 * the node to 020cf3d8. */
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern int func_02023eb4(int scale);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020cf3d8(void);

void func_ov253_020cf35c(int *node) {
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0, 1);
    state[7] = func_02023eb4(0x5001) + 0x5000;
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo |= 1;
    *(int *)(*state + 0x3bc) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020cf3d8);
}
