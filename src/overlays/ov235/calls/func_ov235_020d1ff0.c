/* Ramp-up tick of an ov235 part: the +0x10 timer accumulates the owner's rate; at 3.0 animation
 * channels 0, 2, 4 and 1 are stopped (0203b9fc mode 2), the timer clears and the tick hands over to
 * func_ov235_020d2084. */
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d2084(int *node);

void func_ov235_020d1ff0(int *node)
{
    int *state = (int *)node[1];

    state[4] += *(int *)(*node + 0x2c);
    if (!(state[4] < 0x3000)) {
        func_0203b9fc(state[1], 0, 2, 0);
        func_0203b9fc(state[1], 2, 2, 0);
        func_0203b9fc(state[1], 4, 2, 0);
        func_0203b9fc(state[1], 1, 2, 0);
        state[4] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d2084);
        return;
    }
}
