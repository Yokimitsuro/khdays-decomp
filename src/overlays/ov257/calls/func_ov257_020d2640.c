/* Re-arm tick of an ov257 part: once its rig is idle (+0xad), animation channels 0, 2, 4 and 1 are
 * restarted looped (0203b9fc), the +8 target clears and the tick hands over to
 * func_ov257_020d26c8. */
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d26c8(int *node);

void func_ov257_020d2640(int *node)
{
    int *state = (int *)node[1];

    if (*(unsigned char *)(*state + 0xad) == 0) {
        func_0203b9fc(*state, 0, 1, 1);
        func_0203b9fc(*state, 2, 1, 1);
        func_0203b9fc(*state, 4, 1, 1);
        func_0203b9fc(*state, 1, 1, 1);
        state[2] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d26c8);
        return;
    }
}
