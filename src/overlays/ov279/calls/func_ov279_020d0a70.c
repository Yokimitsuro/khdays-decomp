/*
 * func_ov279_020d0a70 -- x3. AI-state entry: initialise the sub-state and register three handlers.
 * Clear *(u8)(state[0]+0x1c6)=0, set *(u8)(state[0]+0x1c7)=-1; clear bit0 of the low byte of the word
 * at *(state[0]+0x388)+8; set hw60.hi |= 6 on the +0x60 flags; cache anchors state[0x13]=state[0]+0x74,
 * state[0x12]=state[0]+0xb0. Register handlers 1/0/2 via 0203c634 -> 020cd144, 020ccef4, 020cd0f0.
 */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov279_020d0d84(void);
extern void func_ov279_020d0b34(void);
extern void func_ov279_020d0d30(void);

void func_ov279_020d0a70(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;

    *(char *)(*state + 0x1c6) = 0;
    *(char *)(*state + 0x1c7) = -1;
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 6 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    state[0x13] = *state + 0x74;
    state[0x12] = *state + 0xb0;
    func_0203c634((int)self, 1, (int)&func_ov279_020d0d84);
    func_0203c634((int)self, 0, (int)&func_ov279_020d0b34);
    func_0203c634((int)self, 2, (int)&func_ov279_020d0d30);
}
