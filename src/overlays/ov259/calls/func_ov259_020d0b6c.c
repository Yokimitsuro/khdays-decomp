/* Slam tick of the ov259 actor: the +0x68 timer accumulates the frame rate, the ground test
 * (020cdc20) zeroes the x/z drift once grounded and the aim refreshes. At 0xc38 the impact lands once
 * (+0x50): sound 0x172/0x19 at the +0x10 point unless muted (+0x428), the +0x384 rig shakes
 * (020d17b8) and +0x94 = 400. The cue pulses at 0x330 (bit 0, 2) and 0x1650 (bit 1, 3). Once the
 * partner has no queued move the timer restarts, pose 0x16 plays and the node moves on to 020d0cb4. */
typedef unsigned char u8;

extern int func_ov259_020cdc20(int *node);
extern void func_ov259_020cdcac(int *node);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_ov259_020d17b8(char *self);
extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d0cb4(void);

void func_ov259_020d0b6c(int *node)
{
    int *state = (int *)node[1];
    int ground;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    ground = func_ov259_020cdc20(node);
    func_ov259_020cdcac(node);
    if (ground <= 0) {
        state[5] = 0;
        state[7] = 0;
    }
    if (state[0x1a] >= 0xc38 && state[0x14] == 0) {
        if (*(int *)(*state + 0x428) == 0) {
            func_ov259_020cd3c4(*state, 0x172, 0x19, (void *)state[4]);
        }
        func_ov259_020d17b8(*(char **)(*state + 0x384));
        state[0x25] = 0x190;
        state[0x14] = 1;
    }
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x330) {
        *((u8 *)state + 0xac) |= 1;
        func_ov259_020cd2c8(*state, 2);
    }
    if ((*((u8 *)state + 0xac) & 2) == 0 && state[0x1a] >= 0x1650) {
        *((u8 *)state + 0xac) |= 2;
        func_ov259_020cd2c8(*state, 3);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    state[0x1a] = 0;
    func_ov107_020c9264(*state, 0x16, 0);
    func_ov259_020cd524(node, 0x16, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d0cb4);
}
