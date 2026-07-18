/*
 * func_ov235_020d1a88 -- x3. AI-state entry: reset flags, clear hit regions, snapshot the pose,
 * register two handlers. Clear bit1 of *(state[0]+0x5c), then set its bit0. Disable hit regions
 * 0,2,4,1 via 0203b9fc(state[0], region, 0, 0). Copy the 11-word source block *(state[1]) into
 * state[0]+0x30 (the pose). Register handlers 1/2 via 0203c634 -> 020d1b98, 020d1b6c.
 *
 * NON-MATCHING: the documented "struct-copy >16B ip<->r4 swap" register-allocation tie (see
 * deferred-ties.md). Every value, the two +0x5c bit ops, all four b9fc calls and both c634 handoffs
 * are exact and the size is exact (204B). The only diff is the 11-word (44B) block copy: the ROM
 * colors src(state[1])->ip, dst(*state+0x30)->r4 in the ldm!/stm! chain; mwcc colors src->r4,
 * dst->ip. Tried: explicit src/dst pointer locals, dst-first, src-only pointer -- none flip the
 * coloring. Checklist clean (ARM, b9fc 4-arg, all constants/offsets exact).
 */
struct b1 { unsigned b0 : 1; };
struct s11 { int w[11]; };
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov235_020d1b98(void);
extern void func_ov235_020d1b6c(void);

void func_ov235_020d1a88(int *self) {
    int *state = (int *)self[1];

    *(int *)(*state + 0x5c) &= ~2;
    ((struct b1 *)(*state + 0x5c))->b0 = 1;
    func_0203b9fc(*state, 0, 0, 0);
    func_0203b9fc(*state, 2, 0, 0);
    func_0203b9fc(*state, 4, 0, 0);
    func_0203b9fc(*state, 1, 0, 0);
    *(struct s11 *)(*state + 0x30) = *(struct s11 *)state[1];
    func_0203c634((int)self, 1, (int)&func_ov235_020d1b98);
    func_0203c634((int)self, 2, (int)&func_ov235_020d1b6c);
}
