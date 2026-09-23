/* Sweep recovery tick of the ov259 actor: the +0x68 timer accumulates the frame rate; past 0x2a8 a
 * live sweep (+0x50) ends (020d17fc on the +0x384 body). Once the +4 item's +0xad byte clears any
 * live sweep ends and the next move is 2. */
typedef unsigned char u8;

extern void func_ov259_020d17fc(int body);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov259_020d0d28(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (state[0x1a] > 0x2a8 && state[0x14] != 0) {
        func_ov259_020d17fc(*(int *)(*state + 0x384));
        state[0x14] = 0;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x14] != 0) {
        func_ov259_020d17fc(*(int *)(*state + 0x384));
        state[0x14] = 0;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
