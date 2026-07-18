/*
 * func_ov245_020ced68 -- x3. AI-state entry: reset flags and seed the aim vector, dispatch.
 * Clear *(state[0]+0x38c)=0; set hw60.hi |= 0x80 then hw60.hi &= ~1 on the +0x60 flags; clear bit0 of
 * the low byte of the word at *(state[0]+0x388)+8. Copy the const vec data_02041dc8 into state[3..5],
 * then hand off to the 020cee24 state.
 *
 * NON-MATCHING: struct-copy load-hoist scheduling tie (size-exact, all bitfield ops and the copy are
 * semantically exact). The ROM loads the const vec (ldm) early, HOLDS it in r0-r2 across the three
 * hw60/byte RMW blocks (so it pushes r4,r5,r6 for the RMW scratch), and commits the store (stm to
 * state+0xc) last. mwcc keeps the ldm/stm adjacent: copy-last -> both late (no hoist, pushes {r4,lr});
 * copy-first -> both early; a local `struct vec3 tmp` spills (+20B). No C form splits the load from the
 * store the way the ROM's scheduler did. Checklist clean (ARM, c634 3-arg, all offsets/constants exact).
 */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };
extern struct vec3 data_02041dc8;
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov245_020cee24(void);

void func_ov245_020ced68(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;

    *(int *)(*state + 0x38c) = 0;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    *(struct vec3 *)(state + 3) = data_02041dc8;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov245_020cee24);
}
