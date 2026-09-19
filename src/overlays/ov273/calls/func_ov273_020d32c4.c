/* Attack entry: sets the +0x48 rate to 30/5 of the frame step, plays pose 4, clears the +0x6a
 * latch and +0x70 timer, re-acquires the lock-on target into +0x24 and, when one exists, builds
 * the aim pose at +0x38 from data_02042264 and atan2 of the flattened, normalised direction from
 * the +4 anchor to the target's +0x74 position (data_02042258 when degenerate); then moves the
 * node to 020cf768. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern int  func_020050b4(int x, int z);
extern void func_0202f188(void *dst, void *k, int angle);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov273_020d33a8(void);
extern int  data_02042258;
extern int  data_02042264;
struct v3 { int a, b, c; };

void func_ov273_020d32c4(int *self) {
    int *state = (int *)self[1];
    int target;
    struct v3 v;

    state[0x12] = *(int *)(self[0] + 0x2c) * 30 / 5;
    func_ov107_020c9264(*state, 4, 0);
    *((unsigned char *)state + 0x6a) = 0;
    state[0x1c] = 0;
    target = func_ov107_020cab14(*state, 0);
    state[9] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)state[1], &v);
        v.b = 0;
        if (func_01ff8d18(&v, &v) == 0) {
            v = *(struct v3 *)&data_02042258;
        }
        func_0202f188((void *)(state + 0xe), &data_02042264, func_020050b4(v.a, v.c));
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d33a8);
}
