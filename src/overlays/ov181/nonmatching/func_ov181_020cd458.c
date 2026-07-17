/*
 * func_ov181_020cd458 -- UNFINISHED. 288/288 bytes, 72/72 instructions. EXACT TWIN of
 * func_ov182_020cf000 (see that file for the full analysis) -- same shape, same residue.
 * x6 family (worth 6), and with ov182's x6 that is 12 functions on this one register-choice tie.
 *
 * WHAT IT DOES: re-acquire the target (020cab14 returns squared distance via out-param); none ->
 * state 2. dist = FX_Sqrt(distsq) - both radii. state[8] = (owner delta) * 30 / 10 (base *self).
 * Aim from target+0x74 to state[2], atan2 -> state[6]. Transform a const vector (data_02042258) by
 * the owner matrix into state+0x54 and scale by 0x100. Then, if the sub-node byte at state[3] is
 * clear, fire 020c9264 and advance with a callback.
 *
 * The ONLY differences from ov182 are the divisor (10 here, magic 0x66666667 asr#2 = /10, vs
 * ov182's /20 asr#3), the aim base (target+0x74 vs +0x190) and the second VEC_Subtract arg
 * (state[2] vs state[1]). The state[4]-reread crack (VEC_Subtract's first arg is state[4], not the
 * live target) is applied and gives the exact size.
 *
 * THE GAP is identical to ov182: a target/owner register rotation. ROM target=r7, owner=r6; mine
 * target=r6, owner=r7 (and the test-copy `movs r7,r0` / `str r0` become `movs r6,r0` / `str r6`).
 * Same 72 instructions, same order. Both are loaded before FX_Sqrt and live across it, so both
 * need callee-saved registers; the ROM assigns target the HIGHER one though it is defined first,
 * which is the scratch/callee register-choice class -- not decl-order (swept, all 6 identical) and
 * not first-use.
 *
 * RULED OUT this pass (beyond ov182's sweep): loading `owner = *state` before the 020cab14 call
 * (diffs EARLIER, 0x15); using state[4] instead of `target` for the radius (292, +1). Neither
 * moves the rotation.
 *
 * NEXT STEP: none at the source level. If ov182's rotation is ever cracked, apply the same fix
 * here -- it is the same tie, and the two together are worth 12.
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
extern int func_ov181_020cd578;

void func_ov181_020cd458(int *self) {
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
    state[8] = *(int *)(*self + 0x2c) * 0x1e / 10;
    VEC_Subtract((void *)(state[4] + 0x74), (void *)state[2], aim);
    state[6] = func_020050b4(aim[0], aim[2]);
    func_0202f384((void *)(state + 0x15), (void *)(*state + 0xa0), &data_02042258);
    func_01ffa724(0x100, (void *)(state + 0x15), (void *)(state + 0x15));
    if (*(unsigned char *)state[3] == 0) {
        func_ov107_020c9264(*state, 4, 0);
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov181_020cd578);
    }
}
