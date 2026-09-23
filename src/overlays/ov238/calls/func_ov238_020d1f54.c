/* Stomp tick of the ov238 actor: +0x20 accumulates the frame rate; at 1.73 the stomp lands once
 * (+0x2e): the +0x384 rig shakes (020d261c) and sound 0x12e/0xe plays at the +8 point. Once the
 * partner holds no queued move the next move is 2 and the node ends. */
extern void func_ov238_020d261c(int rig);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov238_020d1f54(int *node)
{
    int *state = (int *)node[1];

    state[8] += *(int *)(node[0] + 0x2c);
    if (state[8] >= 0xdd0 && *((unsigned char *)state + 0x2e) == 0) {
        *((unsigned char *)state + 0x2e) += 1;
        func_ov238_020d261c(*(int *)(*state + 0x384));
        func_ov107_020c5af8(*state, 0x12e, 0xe, (void *)state[2]);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
