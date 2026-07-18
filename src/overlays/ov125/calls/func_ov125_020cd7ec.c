/*
 * func_ov125_020cd7ec -- x3. AI-state tick: fire, roll a random strafe sign, dispatch.
 * Fire attack 1 (020c9264, flag 1). state[0x1e] = RandNextScaled(2) ? -1 : 1 (random sign);
 * state[0xb] = 0. Hand off to the 020cf828 state.
 */
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_02023eb4();  /* K&R decl: needed for the rand `+ (v - v)` copy artifact */
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov125_020cd840(void);

void func_ov125_020cd7ec(int *self) {
    int *state = (int *)self[1];
    int v;

    func_ov107_020c9264(*state, 1, 1);
    /* +(v-v) forces `adds r0,r0,#0` (rand result copied+tested); +0 would fold away */
    state[0x1e] = (func_02023eb4(2) + (v - v)) != 0 ? -1 : 1;
    state[0xb] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov125_020cd840);
}
