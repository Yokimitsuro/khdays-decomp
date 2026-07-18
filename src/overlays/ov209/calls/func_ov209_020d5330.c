/*
 * func_ov209_020d5330 -- x3. AI-state entry: reconfigure flags, kick a fixed motion, spawn effect 0x49.
 * hw60.hi |= 6; set bit0 of the halfword at state[0]+0x1ae; clear bit0 of the low byte of the words at
 * *(state[0]+0x3b8)+8 and *(state[0]+0x3b4)+8; hw60.hi |= 0x40. Kick via 020c0b90(state[0], 0, *state[3]
 * by value, 0). Spawn via 020c5af8(state[0], 0, 0x49, state[3]). Clear state[0xb] = 0, hand off to the
 * 020d362c state.
 */
struct vec3 { int x, y, z; };
struct b8 { unsigned f : 8; };
extern void func_ov107_020c0b90(int obj, int mode, struct vec3 v, int flag);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov209_020d544c(void);

void func_ov209_020d5330(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 6 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*state + 0x3b8) + 8))->f &= ~1;
    ((struct b8 *)(*(int *)(*state + 0x3b4) + 8))->f &= ~1;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 0x40 */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    func_ov107_020c0b90(*state, 0, *(struct vec3 *)state[3], 0);
    func_ov107_020c5af8(*state, 0, 0x49, state[3]);
    state[0xb] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov209_020d544c);
}
