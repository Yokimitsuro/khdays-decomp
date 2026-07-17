/*
 * func_ov187_020d4980 -- x3 (ov185/186/187). AI-state tick: seed a randomized strafe and dispatch.
 * state[0xa] = owner_delta*30/10. Fire attack 1 (020c9264, flag 1). Roll a random sign
 * state[0x17] = RandNextScaled(2) ? -1 : 1, and a random duration state[0x18] = RandNextScaled(0x101)
 * + 0x200. Hand off to the 020cefa8 state.
 */
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_02023eb4();  /* K&R decl: needed for the rand `+ (v - v)` copy artifact */
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov187_020d4a08(void);

void func_ov187_020d4980(int *self) {
    int *state = (int *)self[1];
    int v = *(int *)(*self + 0x2c);

    state[0xa] = v * 0x1e / 10;
    func_ov107_020c9264(*state, 1, 1);
    /* +(v-v) forces `adds r0,r0,#0` (rand result copied+tested); +0 would fold away */
    state[0x17] = (func_02023eb4(2) + (v - v)) != 0 ? -1 : 1;
    state[0x18] = func_02023eb4(0x101) + 0x200;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov187_020d4a08);
}
