/*
 * func_ov137_020cdd74 -- x3. AI-state entry: reconfigure flags, spawn effect 0x4a, dispatch.
 * hw60.hi &= ~1 then hw60.hi |= 0x86 on the +0x60 flags; set bits 0x3 in the halfword at
 * state[0]+0x1ae; clear bit0 of the low byte of the word at *(state[0]+0x384)+8. Spawn via
 * 020c5af8(state[0], 0, 0x4a, state[0x14]). Clear *(u8)(state[0]+0x1c7), hand off via 0203c634 (cb=0).
 */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);

void func_ov137_020cdd74(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;

    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 0x86 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    *(unsigned short *)(*state + 0x1ae) |= 3;
    ((struct b8 *)(*(int *)(*state + 0x384) + 8))->f &= ~1;
    func_ov107_020c5af8(*state, 0, 0x4a, state[0x14]);
    *(char *)(*state + 0x1c7) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
