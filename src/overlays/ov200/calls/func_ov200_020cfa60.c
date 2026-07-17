/*
 * func_ov200_020cfa60 -- x3 (ov200/201/271). AI-state tick: fire, aim the pose at the target, and
 * transition.
 * Fire attack 2 (020c9264). If a target is set (state[0x15]!=0): dir = target(+0x190) - *state(+0xb0);
 * build the aim pose at state[0x25..] from data_02042264 and atan2(dir.x,dir.z) (0202f188), then copy
 * that 4-word pose down to state[0x21..] (field-to-field). Always hand off to the 020cfaec state.
 */
struct m4 { int w[4]; };
struct S200 { char pad[0x84]; struct m4 dst; struct m4 src; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_020050b4(int x, int z);
extern void func_0202f188(void *dst, void *k, int angle);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov200_020cfaec(void);
extern int  data_02042264;

void func_ov200_020cfa60(int *self) {
    int *state = (int *)self[1];
    int v[3];

    func_ov107_020c9264(*state, 2, 0);
    if (state[0x15] != 0) {
        VEC_Subtract((void *)(state[0x15] + 0x190), (void *)(*state + 0xb0), v);
        func_0202f188((void *)(state + 0x25), &data_02042264, func_020050b4(v[0], v[2]));
        ((struct S200 *)state)->dst = ((struct S200 *)state)->src;
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020cfaec);
}
