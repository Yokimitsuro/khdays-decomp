/* Alert wait tick: runs the +0x1c timer up to 0x1aaa, then re-acquires the lock-on target into
 * +0x24 and, when one exists, builds the aim pose at +0x28 from data_02042264 and atan2 of the
 * flattened, normalised direction from the +4 anchor to the target's +0x74 position
 * (data_02042258 when degenerate) and copies it up to +0x38. Flags 0x82 clear in the actor's
 * +0x60 high byte, pose 0x1a plays and the node moves to 020cda00. */
typedef unsigned short u16;
struct m4 { int w[4]; };
struct S213 { char pad[0x28]; struct m4 lo; struct m4 hi; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern int  func_020050b4(int x, int z);
extern void func_0202f188(void *dst, void *k, int angle);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov213_020cda00(void);
extern int  data_02042258;
extern int  data_02042264;
struct v3 { int a, b, c; };

void func_ov213_020cd8ec(int *self) {
    int *state = (int *)self[1];
    int target;
    struct v3 v;

    state[7] += *(int *)(self[0] + 0x2c);
    if (state[7] < 0x1aaa) return;
    target = state[9] = func_ov107_020cab14(*state, 0);
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)state[1], &v);
        v.b = 0;
        if (func_01ff8d18(&v, &v) == 0) {
            v = *(struct v3 *)&data_02042258;
        }
        func_0202f188((void *)(state + 0xa), &data_02042264, func_020050b4(v.a, v.c));
        ((struct S213 *)state)->hi = ((struct S213 *)state)->lo;
    }
    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0x1a, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov213_020cda00);
}
