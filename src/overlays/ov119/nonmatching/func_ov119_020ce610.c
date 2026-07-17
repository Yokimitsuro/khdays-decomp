/*
 * func_ov119_020ce610 -- x3. AI-state tick: wait out a timer, then re-seed and dispatch.
 * state[0x14] += owner_delta; while under 0x1000 return. Once past: reset state[0x14]=0,
 * set state[0x19] = 0xffff6216 (a fixed offset), roll state[0x1a] = RandNextScaled(0x1001) + 0x2000,
 * and hand off to the 020ce674 state.
 *
 * NON-MATCHING: scheduling tie (x3: ov119/272/279, all byte-identical modulo relocs). Semantics,
 * every register and both pool constants (r1=0xffff6216, r0=0x1001) are exact and the size is exact
 * (100B). The only diff is a 1-instruction reorder at 0x28: mwcc's -O4,p scheduler hoists the
 * independent `ldr r1,=0xffff6216` one slot ABOVE the `str r0,[state+0x50]` zero-store, whereas the
 * ROM emits the store first. Tried: +0x2000+rng order, comma-sequenced stores, local temp for the
 * const, mvn-form (-0x9dea) -- all reproduce the same hoist. The store cannot be forced ahead of the
 * non-aliasing pool load in C. Pre-park checklist clean (ARM, rng 1-arg genuine, c634 3-arg, no
 * dropped/misplaced constant).
 */
extern int  func_02023eb4(int scale);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov119_020ce674(void);

void func_ov119_020ce610(int *self) {
    int *state = (int *)self[1];

    state[0x14] += *(int *)(*self + 0x2c);
    if (state[0x14] < 0x1000) {
        return;
    }
    state[0x14] = 0;
    state[0x19] = 0xffff6216;
    state[0x1a] = func_02023eb4(0x1001) + 0x2000;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov119_020ce674);
}
