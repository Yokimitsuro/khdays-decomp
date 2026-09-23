/* Sequence tail tick of the ov259 actor: the +0x68 timer accumulates the frame rate, the cue pulses
 * once at 0x2288 (+0xac bit 6) and, once the +4 item's +0xad byte clears, the next move is 2. */
typedef unsigned char u8;

extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov259_020d02b8(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0xac) & 0x40) == 0 && state[0x1a] >= 0x2288) {
        *((u8 *)state + 0xac) |= 0x40;
        func_ov259_020cd2c8(*state, 0);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
