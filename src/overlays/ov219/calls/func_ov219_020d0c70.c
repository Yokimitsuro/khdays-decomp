/* Wander tick of the ov219 enemy (and its byte-identical twin): a negative distance to the target
 * ends the state; within 0x4800 the +0x14 clock resets, the tick hands off to the approach state
 * and runs it at once, and the actor wants animation 1; beyond it the idle countdown may end the
 * state, else animation 0 is wanted. A wanted animation different from the +0x44 one is played. */
extern int func_ov219_020d05f0(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov219_020d0d24(int *node);
extern int func_ov219_020d055c(int *node, int value);
extern void func_ov107_020c9264(int actor, int anim, int flag);

void func_ov219_020d0c70(int *node)
{
    int *state = (int *)node[1];
    int dist;
    int anim;

    dist = func_ov219_020d05f0(node);
    if (dist < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist < 0x4800) {
        state[5] = 0;
        anim = 1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov219_020d0d24);
        func_ov219_020d0d24(node);
    } else {
        if (func_ov219_020d055c(node, dist) != 0) {
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
