/*
 * func_ov119_020cd7f4 -- x3. AI-state tick: fire, then face the target with a look-at orientation.
 * Fire attack 2 (020c9264, flag 0). If the target state[0x16] is null, just dispatch. Else
 * dir = normalise(flatten_y(target(+0x190) - state[0x12])); if the direction is degenerate (normalise
 * returns 0) fall back to the const forward data_02042258. Build the orientation state[7..10] via
 * 0202ed60 (look-at from data_02042258 toward dir) + 0202f4a4, then copy it down to state[3..6].
 * Always hand off via 0203c634 to the 020cd8a8 state.
 */
struct vec3 { int x, y, z; };
struct q4 { int a, b, c, d; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *a, void *b);
extern void func_0202ed60(void *out, void *fwd, void *dir);
extern void func_0202f4a4(void *dst, void *src);
extern struct vec3 data_02042258;
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov119_020cd8a8(void);

void func_ov119_020cd7f4(int *self) {
    int *state = (int *)self[1];
    int target;
    struct vec3 v;

    func_ov107_020c9264(*state, 2, 0);
    target = state[0x16];
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x190), (void *)state[0x12], &v);
        v.y = 0;
        if (func_01ff8d18(&v, &v) == 0) {
            v = data_02042258;
        }
        func_0202ed60((void *)(state + 7), &data_02042258, &v);
        func_0202f4a4((void *)(state + 7), (void *)(state + 7));
        *(struct q4 *)(state + 3) = *(struct q4 *)(state + 7);
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov119_020cd8a8);
}
