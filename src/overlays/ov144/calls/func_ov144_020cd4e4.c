/* Recover entry of the ov144 enemy (and its byte-identical twin): with the previous sub-state
 * (+0x1c6) equal to 4 the actor plays animation 6 and hands off to the cd560 state; otherwise it
 * plays animation 1 (looped), reruns the +0x394 item's action 0 and hands off to cd5b8. */
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c9ee8(void *item, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov144_020cd560(int *node);
extern void func_ov144_020cd5b8(int *node);

void func_ov144_020cd4e4(int *node)
{
    int *state = (int *)node[1];

    if (*(signed char *)(*state + 0x1c6) == 4) {
        func_ov107_020c9264(*state, 6, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov144_020cd560);
        return;
    }
    func_ov107_020c9264(*state, 1, 1);
    func_ov107_020c9ee8(*(void **)(*state + 0x394), 0, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov144_020cd5b8);
}
