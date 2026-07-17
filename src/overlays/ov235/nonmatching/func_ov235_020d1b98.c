/*
 * func_ov235_020d1b98 -- x3. AI-state tick: once ready, arm four hit regions and advance.
 * Gate: if *(u8)(state[0]+0xad) != 0 still busy, return. Else enable hit regions 0,2,4,1 via
 * 0203b9fc(state[0], region, 1, 1) (four calls), clear state[2] = 0, hand off to the 020d1c20 state.
 *
 * NON-MATCHING: mwcc arg-materialization scheduling tie (size-exact, all args correct). Calls 1-3
 * (region != 1) match exactly. The 4th call is the degenerate case region==1, so the flag arg and
 * both trailing 1s share one register (mov r1,#1; mov r2,r1; mov r3,r1) -- and the ROM materializes
 * `mov r1,#1` BEFORE the `ldr r0,[state]`, while mwcc emits the load first. Same instructions,
 * swapped by one slot; no C form flips it (tried: local `int one=1`, hoisting `one` across all four
 * calls, cached *state). A second swap in the 0203c634 tail (r0=self scheduled first vs last, because
 * the preceding `state[2]=0` store leaves r0 free) IS steerable -- precomputing the idx arg into a
 * local fixes it -- but the call-4 swap remains. Checklist clean: ARM, b9fc 4-arg, all constants and
 * offsets exact.
 */
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov235_020d1c20(void);

void func_ov235_020d1b98(int *self) {
    int *state = (int *)self[1];

    if (*(unsigned char *)(*state + 0xad) != 0) {
        return;
    }
    func_0203b9fc(*state, 0, 1, 1);
    func_0203b9fc(*state, 2, 1, 1);
    func_0203b9fc(*state, 4, 1, 1);
    func_0203b9fc(*state, 1, 1, 1);
    state[2] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov235_020d1c20);
}
