/*
 * func_ov235_020d1c20 -- x3. AI-state tick: hold the hit regions for a while, then reconfigure them.
 * state[2] += owner_delta; while under 0xc00 return. Once past: reconfigure hit regions 0,2,4,1 via
 * 0203b9fc(state[0], region, 2, 0) (four calls), reset state[2] = 0, hand off to the 020d1cb4 state.
 *
 * NON-MATCHING: c634-after-zero-store arg-order scheduling tie (size-exact, all 4 b9fc calls and every
 * value exact). The final `state[2]=0` store uses r0, so for the 0203c634 tail the ROM materializes
 * r1(idx)+r2(cont) first and defers `mov r0,self` to last; mwcc sets r0=self first. Tried: precompute
 * the idx into a local (fixed the SAME swap in the sibling func_ov235_020d1b98 but not here -- register
 * pressure from the (region,2,0) calls differs), precompute cont, cache self in a local. One-instruction
 * swap, no C form flips it. Checklist clean (ARM, b9fc 4-arg, all constants/offsets exact).
 */
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov235_020d1cb4(void);

void func_ov235_020d1c20(int *self) {
    int *state = (int *)self[1];

    state[2] += *(int *)(*self + 0x2c);
    if (state[2] < 0xc00) {
        return;
    }
    func_0203b9fc(*state, 0, 2, 0);
    func_0203b9fc(*state, 2, 2, 0);
    func_0203b9fc(*state, 4, 2, 0);
    func_0203b9fc(*state, 1, 2, 0);
    state[2] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov235_020d1cb4);
}
