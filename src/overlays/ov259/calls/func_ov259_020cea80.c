/* Guard end tick of the ov259 actor: the aim refreshes (020cdcac) and the +0x68 timer accumulates
 * the frame rate. Grounded (+0x17a bit 0) past 0xff0 a pending move (+0xad) is taken; otherwise
 * a d100 roll of 50 or more (or a +0x4c request) clears +0x84 and the next move is 2. */
typedef unsigned char u8;
struct Flag17a { u8 b0 : 1; };

extern void func_ov259_020cdcac(int *node);
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov259_020cea80(int *node)
{
    int *state = (int *)node[1];
    signed char pending;

    func_ov259_020cdcac(node);
    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (!((struct Flag17a *)(*state + 0x17a))->b0) {
        return;
    }
    if (state[0x1a] <= 0xff0) {
        return;
    }
    pending = *((signed char *)state + 0xad);
    if (pending != -1) {
        *(signed char *)(*state + 0x1c7) = pending;
        *((signed char *)state + 0xad) = -1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (func_02023eb4(0x65) + (pending - pending) >= 0x32 || state[0x13] != 0) {
        state[0x21] = 0;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
