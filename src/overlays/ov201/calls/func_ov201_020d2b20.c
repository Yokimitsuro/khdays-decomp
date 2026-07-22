/*
 * func_ov201_020d2b20 -- x3. AI-state tick: wait out a timer, aim at the target, fire, reroll a delay.
 * state[0x14] += owner_delta; while under 0x6ee return. Once past: target = acquire(*state, 0) ->
 * state[2]. If found, build a look-at matrix toward target(+0x74) (0203cd7c, state[0x13], const
 * data_02042264), convert to the orientation quaternion state[0x25..0x28] (0202ea48) and copy that down
 * to state[0x21..0x24]. Clear hw60.hi bit 0x80, fire attack 0 (020c9264). Reroll state[0x20] to a
 * random value in [*(state[0]+0x224), *(state[0]+0x228)] and hand off to the 020cefdc state.
 *
 * The one byte that kept this parked was the source register of the `state[2] =` store: the ROM
 * stores the acquire result straight out of r0 and keeps the flag-setting copy in r1 for
 * `target + 0x74`, while `target = acquire(...); state[2] = target;` stores r1. Writing the store
 * FIRST and then binding the local from the slot -- `state[2] = acquire(...); target = state[2];` --
 * gives the ROM's register split. mwcc forwards the value, so there is no reload and no size cost;
 * the earlier note's "+4B" came from re-reading state[2] down inside the branch instead.
 */
struct q4 { int a, b, c, d; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203cd7c(void *out, int a, int b, void *c);
extern void func_0202ea48(void *quat, void *mtx);
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_02023eb4(int scale);
extern void func_0203c634(int self, int idx, int cb);
extern int  data_02042264;
extern void func_ov201_020d2c1c(void);

void func_ov201_020d2b20(int *self) {
    int *state = (int *)self[1];
    int v[9];
    int target;
    int a, d;

    state[0x14] += *(int *)(*self + 0x2c);
    if (state[0x14] < 0x6ee) {
        return;
    }
    state[2] = func_ov107_020cab14(*state, 0);
    target = state[2];
    if (target != 0) {
        func_0203cd7c(v, target + 0x74, state[0x13], &data_02042264);
        func_0202ea48((void *)(state + 0x25), v);
        *(struct q4 *)(state + 0x21) = *(struct q4 *)(state + 0x25);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    func_ov107_020c9264(*state, 0, 0);
    a = *(int *)(*state + 0x224);
    d = *(int *)(*state + 0x228) - a;
    if (d < 0) {
        d = -d;
    }
    state[0x20] = a + func_02023eb4(d + 1);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov201_020d2c1c);
}
