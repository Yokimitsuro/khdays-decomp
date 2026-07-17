/*
 * NONMATCHING -- 196/196 size-exact, diff @0x64: the blx/pt-callback scheduling residue (3rd of its
 * class after ov200_020cfcfc/020cff54). The ROM hoists `add r1,sp,#0` (&pt) and orders the
 * state[0x14]=0x6000 store before the DAT-pointer load; mwcc schedules the DAT load first and defers
 * &pt into the `if (fp)` block. The pt store order (pt.b before pt.a) IS load-bearing and correct
 * here. Everything else is byte-exact. This whole "notify via *state+0x24 callback" shape ties on
 * scheduling -- do not grind; the fix is a scheduler lever not yet found.
 *
 * func_ov210_020d32a0 -- x3 (ov210/211/282). AI-state enter: fire, face the target, notify, reset.
 * Fire attack 0x18 (020c9264). Acquire target (020cab14) -> state[4]; if found, state[0xa] =
 * atan2(dir) of target(+0x190) - state[1]. Clear state[0xb], set timer state[0x14] = 0x6000. Load the
 * two config halfwords (data_ov210_020d46ec +4/+6) into a scratch point and, if the owner has a
 * callback at *state+0x24, invoke it (fp(*state, &pt, 4)). Clear state[0x18] and the state+0x66 byte,
 * then hand off to the 020d3364 state.
 */
struct pt { unsigned short a, b; };
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_ov107_020cab14(int obj, void *out);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_020050b4(int x, int z);
extern void func_0203c634(int self, int idx, int cb);
extern unsigned short data_ov210_020d46ec[];
extern void func_ov210_020d3364(void);

void func_ov210_020d32a0(int *self) {
    int *state = (int *)self[1];
    int v[3];
    struct pt pt;
    void (*fp)(int, void *, int);
    int target;

    func_ov107_020c9264(*state, 0x18, 0);
    target = func_ov107_020cab14(*state, 0);
    state[4] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
        state[0xa] = func_020050b4(v[0], v[2]);
    }
    state[0xb] = 0;
    state[0x14] = 0x6000;
    pt.b = data_ov210_020d46ec[3];
    pt.a = data_ov210_020d46ec[2];
    fp = *(void (**)(int, void *, int))(*state + 0x24);
    if (fp != 0) {
        fp(*state, &pt, 4);
    }
    state[0x18] = 0;
    *(char *)((int)state + 0x66) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov210_020d3364);
}
