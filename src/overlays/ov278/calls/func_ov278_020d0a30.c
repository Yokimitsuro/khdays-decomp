/* Roar tick: counts the +0x28 timer up by the scene step; once past 0x6aaa (once, latched at
 * +0x51) effect 0x166 of kind 0x13 fires at the +0x38 anchor. When the +4 child's +0xad byte
 * clears, the +0x14 word resets, bit 0 of the actor's +0x1ae clears, pose request 2 is queued
 * and the node dispatches null. */
typedef unsigned short u16;
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov278_020d0a30(int *node) {
    int *state = (int *)node[1];

    state[0xa] += *(int *)(*node + 0x2c);
    if (*((unsigned char *)state + 0x51) == 0) {
        if (state[0xa] >= 0x6aaa) {
            *((unsigned char *)state + 0x51) = 1;
            func_ov107_020c5af8(*state, 0x166, 0x13, (void *)state[0xe]);
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    state[5] = 0;
    *(u16 *)(*state + 0x100 + 0xae) &= ~1;
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
