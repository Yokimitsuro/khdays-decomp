/* Wind-down tick of an ov255 part: the +8 timer accumulates the owner's rate; at 0.75 animation
 * channels 0, 2, 4 and 1 are stopped (0203b9fc mode 2), the timer clears and the tick hands over to
 * func_ov255_020d0fec. */
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020d0fec(int *node);

void func_ov255_020d0f58(int *node)
{
    int *state = (int *)node[1];

    state[2] += *(int *)(*node + 0x2c);
    if (!(state[2] < 0xc00)) {
        func_0203b9fc(*state, 0, 2, 0);
        func_0203b9fc(*state, 2, 2, 0);
        func_0203b9fc(*state, 4, 2, 0);
        func_0203b9fc(*state, 1, 2, 0);
        state[2] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020d0fec);
        return;
    }
}
