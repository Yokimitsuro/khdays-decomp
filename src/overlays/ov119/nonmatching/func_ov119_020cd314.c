/*
 * func_ov119_020cd314 -- x3. AI-state tick: wait out a timer, then re-aim at the target and fire.
 * state[0x14] += owner_delta; while under 0x6ee return. Once past: target = acquire(*state, 0) ->
 * state[2]. If a target exists, build a look-at matrix toward target(+0x74) (0203cd7c with state[0x13]
 * and const data_02042264), convert it to the orientation quaternion state[7..10] (0202ea48) and copy
 * that down to state[3..6]. Clear hw60.hi bit 0x80, fire attack 0 (020c9264, flag 0), and hand off to
 * the 020cd3ec state.
 *
 * NON-MATCHING: 1-byte register-coloring tie on the state[2] store. The `if (target != 0)` emits a
 * flag-setting `movs r1, r0` that leaves `target` live in BOTH r0 and r1; the ROM stores state[2] from
 * r0 (the fresh acquire return) and keeps r1 for the `target + 0x74` inside the branch, while mwcc
 * stores from r1. Everything else -- the timer gate, the matrix/quaternion build, the hw60 clear, the
 * fire and handoff -- is byte-exact and the size is exact (216B). Tried: store-in-condition merge,
 * chained `state[2] = target = acquire(...)` -- neither flips the store's source register. Checklist
 * clean (ARM; acquire 2-arg, cd7c 4-arg, ea48 2-arg, 020c9264 3-arg, c634 3-arg -- all correct).
 */
struct q4 { int a, b, c, d; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203cd7c(void *out, int a, int b, void *c);
extern void func_0202ea48(void *quat, void *mtx);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern int  data_02042264;
extern void func_ov119_020cd3ec(void);

void func_ov119_020cd314(int *self) {
    int *state = (int *)self[1];
    int target;
    int v[9];

    state[0x14] += *(int *)(*self + 0x2c);
    if (state[0x14] < 0x6ee) {
        return;
    }
    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target != 0) {
        func_0203cd7c(v, target + 0x74, state[0x13], &data_02042264);
        func_0202ea48((void *)(state + 7), v);
        *(struct q4 *)(state + 3) = *(struct q4 *)(state + 7);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov119_020cd3ec);
}
