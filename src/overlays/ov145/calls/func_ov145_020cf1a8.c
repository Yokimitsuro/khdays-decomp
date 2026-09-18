/* Charge decision of the ov144 enemy (and its byte-identical twin): with a +0x39c target and a
 * +0x3b8 anchor and the +0x40 charge at or below 0x100 the tick hands off to cd450 directly;
 * otherwise (no target/anchor, or charge above 0x100) the actor plays animation 0 and hands off
 * to cd41c. */
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov145_020cf26c(int *node);
extern void func_ov145_020cf238(int *node);

void func_ov145_020cf1a8(int *node)
{
    int *state = (int *)node[1];
    int actor = *state;

    if (*(int *)(actor + 0x39c) != 0 && *(int *)(actor + 0x3b8) != 0) {
        if (state[0x10] <= 0x100) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov145_020cf26c);
            return;
        }
        func_ov107_020c9264(actor, 0, 1);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov145_020cf238);
        return;
    }
    func_ov107_020c9264(actor, 0, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov145_020cf26c);
}
