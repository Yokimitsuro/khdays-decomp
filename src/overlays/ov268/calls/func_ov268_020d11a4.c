/*
 * func_ov268_020d11a4 -- x3. AI-state entry: initialise the sub-state and register three handlers.
 * Clear *(u8)(state[0]+0x1c6)=0, set *(u8)(state[0]+0x1c7)=-1; cache anchor pointers state[2]=
 * state[0]+0xb0, state[3]=state[0]+0x74, state[4]=0, state[0x14]=*(state[0]+0x384)+0xad; set bits 0x6
 * in the hi byte of the +0x60 hw flags. Then register handlers 1/0/2 via 0203c634(self, slot, cb) ->
 * 020d15b0, 020d124c, 020d14c4.
 */
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov268_020d15b8(void);
extern void func_ov268_020d1254(void);
extern void func_ov268_020d14cc(void);

void func_ov268_020d11a4(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;

    *(char *)(*state + 0x1c6) = 0;
    *(char *)(*state + 0x1c7) = -1;
    state[2] = *state + 0xb0;
    state[3] = *state + 0x74;
    state[4] = 0;
    state[0x14] = *(int *)(*state + 0x384) + 0xad;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 6 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    func_0203c634((int)self, 1, (int)&func_ov268_020d15b8);
    func_0203c634((int)self, 0, (int)&func_ov268_020d1254);
    func_0203c634((int)self, 2, (int)&func_ov268_020d14cc);
}
