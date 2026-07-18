/*
 * func_ov200_020ceee0 -- x3. AI-state tick: wait out a timer, aim at the target, fire, reroll a delay.
 * state[0x14] += owner_delta; while under 0x6ee return. Once past: target = acquire(*state, 0) ->
 * state[2]. If found, build a look-at matrix toward target(+0x74) (0203cd7c, state[0x13], const
 * data_02042264), convert to the orientation quaternion state[0x25..0x28] (0202ea48) and copy that down
 * to state[0x21..0x24]. Clear hw60.hi bit 0x80, fire attack 0 (020c9264). Reroll state[0x20] to a
 * random value in [*(state[0]+0x224), *(state[0]+0x228)] and hand off to the 020cefdc state.
 *
 * NON-MATCHING: 1-byte register-coloring tie on the state[2] store (same class as func_ov119_020cd314).
 * The `if (target != 0)` emits a flag-setting `movs r1, r0` leaving target live in BOTH r0 and r1; the
 * ROM stores state[2] from r0 (the fresh acquire return) and keeps r1 for `target + 0x74` in the branch,
 * while mwcc stores from r1. Everything else -- timer gate, look-at/quaternion build, hw60 clear, fire,
 * the random reroll -- is byte-exact (252B). Tried: chained `state[2] = target = acquire(...)`, reading
 * state[2] for the look-at (adds a reload, +4B). Neither flips the store's source register.
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
extern void func_ov200_020cefdc(void);

void func_ov200_020ceee0(int *self) {
    int *state = (int *)self[1];
    int v[9];
    int target;
    int a, d;

    state[0x14] += *(int *)(*self + 0x2c);
    if (state[0x14] < 0x6ee) {
        return;
    }
    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
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
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020cefdc);
}
