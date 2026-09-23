/* Stagger tick of the ov218 actor: +0x14 accumulates the frame rate and once past 7.0 the partner's
 * +0xa8 hold clears (once, +0x40); after the partner holds no queued move pose 0xa plays and the node
 * moves on to 020cddc4. */
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov218_020cddc4(void);

void func_ov218_020cdd44(int *node)
{
    int *state = (int *)node[1];

    state[5] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x40) == 0 && state[5] >= 0x7000) {
        *(unsigned char *)(state[1] + 0xa8) = 0;
        *((unsigned char *)state + 0x40) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xa, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020cddc4);
}
