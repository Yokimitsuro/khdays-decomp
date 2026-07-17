/*
 * func_ov211_020d33a4 -- x3. AI-state tick: set up flags, kick a sub-node, dispatch.
 * Set bits 0xcc in the hi byte of the +0x60 hw flags; set bit0 of the halfword at state[0]+0x1ae;
 * clear bit0 of the low byte of the word at *(state[0]+0x3b0)+8. Kick the sub-node via
 * 020d3ffc(deep_ptr, 1, &state[0xd]) where deep_ptr = *(**(state[0]+0x3d4) + 0x194). Clear
 * state[0xb] = 0 and hand off to the 020d162c state.
 */
struct b8 { unsigned f : 8; };
extern void func_ov211_020d5e1c(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov211_020d344c(void);

void func_ov211_020d33a4(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw = (unsigned short *)(*state + 0x60);
    unsigned int h = *hw;

    /* hw60.hi |= 0xcc -- explicit shifts, not a `hi:8` bitfield (the bitfield form adds a
     * redundant 16-bit mask, +8B; see deferred-ties.md) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0xcc) << 0x18) >> 0x10);
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*state + 0x3b0) + 8))->f &= ~1;
    func_ov211_020d5e1c(*(int *)(*(int *)(*(int *)(*state + 0x3d4)) + 0x194), 1, (int)(state + 0xd));
    state[0xb] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov211_020d344c);
}
