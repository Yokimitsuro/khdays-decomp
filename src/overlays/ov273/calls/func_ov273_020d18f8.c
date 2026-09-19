/* Approach tick: scales the +0x50 velocity by 0.9 (0xe66), publishes it as the +0xc velocity,
 * sets the +0x48 rate to 30/10 of the frame step and, unless the +8 flag byte is set, writes
 * pose kind 7 into the actor's +0x1c7 and dispatches with a null handler. */
struct v3 { int a, b, c; };
extern void func_01ffa724(int scale, void *v, void *out);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov273_020d18f8(int *node) {
    int *state = (int *)node[1];
    func_01ffa724(0xe66, state + 0x14, state + 0x14);
    *(struct v3 *)(state + 3) = *(struct v3 *)(state + 0x14);
    state[0x12] = *(int *)(node[0] + 0x2c) * 30 / 10;
    if (*(unsigned char *)state[2] != 0) return;
    *(signed char *)(*state + 0x1c7) = 7;
    func_0203c634(node, *(signed char *)(node + 8), (void *)0);
}
