/* func_ov253_020d1078 -- wait tick: the +0x18 speed follows twice the frame step (30 / 15);
 * once the +8 item's animation is free the +0x2c delay is drawn between the actor's +0x224 and
 * +0x228 bounds, a cleared sub-state (-1) becomes 2 and the node slot is released. */
struct Ov253Sub { char pad[0x1c7]; signed char sub; };

extern int func_02023eb4(int scale);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov253_020d1078(int *node) {
    int *state = (int *)node[1];
    int lo;
    int span;

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 0xf;
    if (*(unsigned char *)state[2] != 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    span = *(int *)(*state + 0x228) - lo;
    if (span < 0) {
        span = -span;
    }
    state[0xb] = lo + func_02023eb4(span + 1);
    if (((struct Ov253Sub *)*state)->sub == -1) {
        ((struct Ov253Sub *)*state)->sub = 2;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
