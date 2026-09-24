/* Ramp-up tick of an ov255 part: the +0xc timer accumulates the owner's rate; at 3.0 animation
 * channels 0, 2, 4 and 1 are stopped (0203b9fc mode 2), the timer clears and the tick hands over to
 * func_ov255_020d13a8. */
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020d13a8(int *node);

void func_ov255_020d1314(int *node)
{
    int *state = (int *)node[1];

    state[3] += *(int *)(*node + 0x2c);
    if (!(state[3] < 0x3000)) {
        func_0203b9fc(state[0], 0, 2, 0);
        func_0203b9fc(state[0], 2, 2, 0);
        func_0203b9fc(state[0], 4, 2, 0);
        func_0203b9fc(state[0], 1, 2, 0);
        state[3] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020d13a8);
        return;
    }
}
