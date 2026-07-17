/*
 * func_ov182_020cf000 -- UNFINISHED. 288/288 bytes, 72/72 instructions.
 * x6 family (worth 6). Semantically complete; the instruction SHAPE is exact.
 *
 * WHAT IT DOES: re-acquire the target (020cab14 returns squared distance via out-param); none ->
 * state 2 and advance. dist = FX_Sqrt(distsq) - both radii (unused after -- kept live only because
 * &distsq escaped to 020cab14). state[8] = (owner delta at *self+0x2c) * 30 / 20 -- base is *self
 * (the OWNER, self[0]), not state. Then aim from target+0x190 to state[1], atan2 -> state[6];
 * transform a const vector (data_02042258) by the owner matrix into state+0x54 and scale by 0x100;
 * finally, if the sub-node byte at state[3] is clear, fire 020c9264 and advance with a callback.
 *
 * ★ THE ONE REAL CRACK, and it is worth keeping: VEC_Subtract's first arg is `state[4] + 0x190`,
 * NOT `target + 0x190`. They hold the same value, but the ROM RE-READS state[4] from memory here
 * (`ldr r0,[r4,#0x10] ; add r0,r0,#0x190`) rather than keeping the call result live -- because
 * `target` has already died (it was used once, for target+0x80 in the dist calc). Writing
 * `target` keeps mwcc's value in a register and DROPS the reload -> 284 B, one instruction short.
 * Ghidra prints `piVar2[4]`, which is the tell. This is the size crack; with it the function is
 * 288/288.
 *
 * THE GAP: a register-CHOICE rotation of target/owner. ROM target=r7, owner=r6; mine target=r6,
 * owner=r7 (and the test-copy `movs r7,r0` / `str r0` become `movs r6,r0` / `str r6`). Same 72
 * instructions, same order. Both are short-lived callee-saved values around the dist calc.
 *
 * RULED OUT: all 6 declaration orders of (distsq, target, owner) -- byte-identical, diff pinned at
 * 0x1D. Neither declaration order NOR first-use predicts the ROM's pick here (target's first use
 * is BEFORE owner's, yet target gets the HIGHER register), so it is the scratch register-choice
 * class, not the callee-saved-decl-order one. See deferred-ties.md.
 *
 * The division divisor is 20 (magic 0x66666667, asr #3 = /20), NOT the /3 of ov195 or /5 of ov142
 * -- read the magic. Base is *self, same trap as ov195.
 */
extern int func_ov107_020cab14(int obj, int *out);
extern void func_0203c634(int self, int idx, int cb);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern void func_0202f384(void *dst, void *mtx, void *src);
extern void func_01ffa724(int s, void *v, void *d);
extern void func_ov107_020c9264(int a, int b, int c);
extern int data_02042258;
extern int func_ov182_020cf120;

void func_ov182_020cf000(int *self) {
    int *state = (int *)self[1];
    int aim[3];
    int distsq;
    int target;
    int owner;

    target = func_ov107_020cab14(*state, &distsq);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    owner = *state;
    distsq = FX_Sqrt(distsq) - (*(int *)(target + 0x80) + *(int *)(owner + 0x80));
    state[8] = *(int *)(*self + 0x2c) * 0x1e / 20;
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], aim);
    state[6] = func_020050b4(aim[0], aim[2]);
    func_0202f384((void *)(state + 0x15), (void *)(*state + 0xa0), &data_02042258);
    func_01ffa724(0x100, (void *)(state + 0x15), (void *)(state + 0x15));
    if (*(unsigned char *)state[3] == 0) {
        func_ov107_020c9264(*state, 3, 1);
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov182_020cf120);
    }
}
