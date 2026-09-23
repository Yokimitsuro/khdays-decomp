/* Circle tick of the ov218 enemy (the ov220 d2b08 wander with its state one word further): a negative
 * distance to the target ends the state; within 0x8000 the +0x10 yaw turns by pi (copied to +0x4c
 * unless the +0x60 flag is set), the +0x5c side flips, the +0x54 rate is re-rolled to 0x8000 +
 * rand(0x10000), the +0x58 speed is 0x4000, bit 15 of +0x50 is cleared, the tick hands off to the
 * flight state (020cd098) and runs it at once, and the actor wants animation 1; beyond it a finished
 * idle countdown (020cc7f8) just returns, else animation 0 is wanted. A wanted animation different
 * from the +0x48 one is played. */
typedef unsigned char u8;

extern int func_ov218_020cc900(int *node);
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov218_020cd098(int *node);
extern int func_ov218_020cc7f8(int *node, int value);
extern void func_ov107_020c9264(int actor, int anim, int flag);

void func_ov218_020ccfa8(int *node)
{
    int *state = (int *)node[1];
    int dist;
    int anim;

    dist = func_ov218_020cc900(node);
    if (dist < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist < 0x8000) {
        state[4] += 0x3244;
        if (state[0x18] == 0) {
            state[0x13] = state[4];
        }
        *(u8 *)(state + 0x17) ^= 1;
        state[0x15] = func_02023eb4(0x10000) + 0x8000;
        state[0x16] = 0x4000;
        state[0x14] &= 0x7fff;
        anim = 1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020cd098);
        func_ov218_020cd098(node);
    } else {
        if (func_ov218_020cc7f8(node, dist) != 0) {
            return;
        }
        anim = 0;
    }
    if (anim < 0) {
        return;
    }
    if (state[0x12] != anim) {
        state[0x12] = anim;
        func_ov107_020c9264(*state, anim, 1);
    }
}
