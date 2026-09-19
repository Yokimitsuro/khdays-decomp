/* Roar wait tick: counts the +0x28 timer up by the scene step. While the actor is grounded
 * (+0x17a bit 0) and each rider is either mounted (+0x1ac bit 1) or holding its +0x3c0 / +0x3d4
 * bit 0, and the +4 child's +0xad byte is still set, nothing happens until the timer passes
 * 6.5. Then both riders get mode 2 from 020c5c14; past 6.5 bit 0 of +0x52 clears, the actor's
 * +0x3bd latch is set, both riders are released (020d0750 with 0 / 1), the +0x14 word clears
 * and pose request 0xa is queued; otherwise, when the actor's +0x3bc bit 0 is set, the timer
 * and the +0x51 latch reset, pose 0x16 plays and the node moves to 020d0a80, else the +0x14 word
 * clears and pose request 2 is queued. */
struct Bits17a { unsigned char b0 : 1; };
struct Bits3bc { unsigned char b0 : 1; };
struct Flags3c0 { int b0 : 1; };
extern void func_ov107_020c5c14(int obj, int mode);
extern void func_ov236_020d0750(int actor, int rider);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov236_020d0a80(void);

void func_ov236_020d0900(int *node) {
    int *state = (int *)node[1];
    int actor = *state;
    int riderA = *(int *)(actor + 0x3b4);
    int riderB = *(int *)(actor + 0x3b8);

    state[0xa] += *(int *)(*node + 0x2c);
    if (((struct Bits17a *)(*state + 0x17a))->b0 != 0 &&
        ((*(unsigned short *)(riderA + 0x100 + 0xac) & 2) != 0 || ((struct Flags3c0 *)(riderA + 0x3c0))->b0 != 0) &&
        ((*(unsigned short *)(riderB + 0x100 + 0xac) & 2) != 0 || ((struct Flags3c0 *)(riderB + 0x3d4))->b0 != 0) &&
        *(unsigned char *)(state[1] + 0xad) == 0) {
        /* ready: fall through (the empty branch keeps the ROM's branch layout) */
    } else if (state[0xa] < 0x6800) {
        return;
    }
    func_ov107_020c5c14(*(int *)(*state + 0x3b4), 2);
    func_ov107_020c5c14(*(int *)(*state + 0x3b8), 2);
    if (state[0xa] >= 0x6800) {
        *((unsigned char *)state + 0x52) &= ~1;
        *(unsigned char *)(*state + 0x3bd) = 1;
        func_ov236_020d0750(*(int *)(*state + 0x3b4), 0);
        func_ov236_020d0750(*(int *)(*state + 0x3b8), 1);
        state[5] = 0;
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (((struct Bits3bc *)(*state + 0x3bc))->b0 != 0) {
        state[0xa] = 0;
        *((unsigned char *)state + 0x51) = 0;
        func_ov107_020c9264(*state, 0x16, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov236_020d0a80);
        return;
    }
    state[5] = 0;
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
