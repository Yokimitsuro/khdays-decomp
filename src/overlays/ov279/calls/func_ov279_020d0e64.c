/*
 * func_ov279_020d0e64 -- x3. AI-state entry: reconfigure flags, set the turn rate, spawn effect 0x48.
 * hw60.hi |= 0x82 then hw60.hi &= ~0xc on the +0x60 flags; set bit0 of the halfword at state[0]+0x1ae;
 * clear bit0 of the low byte of the word at *(state[0]+0x388)+8. Set turn rate state[0xb] =
 * owner_delta * 30 / 10; state[0x14] = 0. Spawn via 020c5af8(state[0], 0, 0x48, state[0x13]), then hand
 * off to the 020cd314 state.
 */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov279_020d0f54(void);

void func_ov279_020d0e64(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 0x82 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    state[0xb] = *(int *)(*self + 0x2c) * 0x1e / 10;
    state[0x14] = 0;
    func_ov107_020c5af8(*state, 0, 0x48, state[0x13]);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov279_020d0f54);
}
