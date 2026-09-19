/* func_ov253_020cf2c0 -- charge wait tick: the +0x18 speed follows twice the frame step
 * (30 / 15); once the +8 item's animation is free and the actor's +0x17a bit 0 is set the +0x2c
 * delay is drawn between the actor's +0x224 and +0x228 bounds, sub-state 2 is requested and the
 * node slot released. */
struct Bit0 { unsigned char b0 : 1; };

extern int func_02023eb4(int scale);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov253_020cf2c0(int *node) {
    int *state = (int *)node[1];
    int lo;
    int span;

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 0xf;
    if (*(unsigned char *)state[2] != 0) {
        return;
    }
    if (!((struct Bit0 *)(*state + 0x17a))->b0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    span = *(int *)(*state + 0x228) - lo;
    if (span < 0) {
        span = -span;
    }
    state[0xb] = lo + func_02023eb4(span + 1);
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
