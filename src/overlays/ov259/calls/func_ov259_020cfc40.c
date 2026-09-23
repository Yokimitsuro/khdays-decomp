/* Down tick of the ov259 actor: the +0x68 timer accumulates the frame rate; with no health left
 * (+0x21a) bits 0-1 of +0x1ae are set; the cue pulses once at 0x3b8 (020cd2c8 2, +0xac bit 0).
 * Past 0x550 the timer restarts, pose 0x1b plays and the node moves on to 020cfce4. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cfce4(void);

void func_ov259_020cfc40(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (*(short *)(*state + 0x200 + 0x1a) <= 0) {
        *(u16 *)(*state + 0x100 + 0xae) |= 3;
    }
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x3b8) {
        *((u8 *)state + 0xac) |= 1;
        func_ov259_020cd2c8(*state, 2);
    }
    if (state[0x1a] <= 0x550) {
        return;
    }
    state[0x1a] = 0;
    func_ov107_020c9264(*state, 0x1b, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cfce4);
}
