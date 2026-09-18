/* Wander tick of the ov220 enemy: a negative distance to the target ends the state; within 0x6000
 * the +0x10 yaw turns by pi (copied to +0x48 unless the +0x5c flag is set), the +0x58 side flips,
 * the +0x50 range is re-rolled to 0xd000 + rand(0x8000), the +0x54 height is 0x2800, bit 15 of
 * +0x4c is cleared, the tick hands off to the approach state and runs it at once, and the actor
 * wants animation 1; beyond it the idle countdown may end the state, else animation 0 is wanted.
 * A wanted animation different from the +0x44 one is played. */
typedef unsigned char u8;

extern int func_ov220_020d2448(int *node);
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov220_020d2c0c(int *node);
extern int func_ov220_020d2384(int *node, int value);
extern void func_ov107_020c9264(int actor, int anim, int flag);

void func_ov220_020d2b08(int *node)
{
    int *state = (int *)node[1];
    int dist;
    int anim;

    dist = func_ov220_020d2448(node);
    if (dist < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist < 0x6000) {
        state[4] += 0x3244;
        if (state[0x17] == 0) {
            state[0x12] = state[4];
        }
        *(u8 *)(state + 0x16) ^= 1;
        state[0x14] = func_02023eb4(0x8000) + 0xd000;
        state[0x15] = 0x2800;
        state[0x13] &= 0x7fff;
        anim = 1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov220_020d2c0c);
        func_ov220_020d2c0c(node);
    } else {
        if (func_ov220_020d2384(node, dist) != 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        anim = 0;
    }
    if (anim < 0) {
        return;
    }
    if (state[0x11] != anim) {
        state[0x11] = anim;
        func_ov107_020c9264(*state, anim, 1);
    }
}
