/*
 * func_ov209_020d3e44 -- x3 (ov208/209/268). AI-state tick: face the cached target, fire attack 0xa
 * once the owner ready-byte clears.
 * state[0x18] = owner_delta*30/10; dir = target(state[4]+0x190) - state[2]; state[0xd] =
 * atan2(dir.x, dir.z). While the ready byte *(u8)(state[1]+0xad) is set, return; once clear fire
 * attack 0xa (020c9264) and hand off to the 020d20c0 state.
 */
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov209_020d3ee0(void);

void func_ov209_020d3e44(int *self) {
    int *state = (int *)self[1];
    int v[3];

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[2], v);
    state[0xd] = func_020050b4(v[0], v[2]);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xa, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov209_020d3ee0);
}
