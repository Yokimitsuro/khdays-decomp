/* Wait tick of the ov252 actor: the +0x64 timer accumulates the frame rate; once the partner holds no
 * queued move, after 5.0 the next move is 0xa when the target is within 16.0 (020cdfe8) else 0xd and
 * the node ends; before that pose 0 restarts. */
extern int func_ov252_020cdfe8(int *node, int a, int b);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov252_020d0334(int *node)
{
    int *state = (int *)node[1];

    state[0x19] += *(int *)(node[0] + 0x2c);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x19] >= 0x5000) {
        if (func_ov252_020cdfe8(node, 0, 0) < 0x10000) {
            *(signed char *)(*state + 0x1c7) = 0xa;
        } else {
            *(signed char *)(*state + 0x1c7) = 0xd;
        }
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*state, 0, 0);
}
