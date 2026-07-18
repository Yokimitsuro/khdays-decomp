/*
 * func_ov271_020d2000 -- x3. AI-state entry: set flags, spawn effect 0x49, dispatch.
 * hw60.hi |= 6 on the +0x60 flags; set bit0 of the halfword at state[0]+0x1ae; clear bit0 of the low
 * byte of the word at *(state[0]+0x388)+8; hw60.hi |= 0x40. Spawn via 020c5af8(state[0], 0, 0x49,
 * state[0x13]). Clear state[0x14] = 0 and hand off to the 020d0250 state.
 */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov271_020d20c4(void);

void func_ov271_020d2000(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 6 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 0x40 */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    func_ov107_020c5af8(*state, 0, 0x49, state[0x13]);
    state[0x14] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov271_020d20c4);
}
