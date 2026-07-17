/*
 * func_ov274_020d1e08 -- x4 (ov206/207/274/275). AI-state tick: face a re-acquired target, and if
 * roughly aligned, fire the transition.
 * Acquire the target (020cab14); cache at state[4]. If none: mark *state[0]+0x1c7 = 2 and bail
 * (0203c634, cb=0). Else: dir = normalise(target_pos(+0x190) - state[1]); state[0xf] = delta*30/20;
 * state[0x11] = atan2(dir.x, dir.z); build a heading vec {sin,0,cos} from state[0x10] (Q12 rad ->
 * sin/cos table); copy the const vec3 data_02041dc8 into state[5..7]; if the heading and dir agree
 * (VEC_DotProduct >= 0xf00) clear *(*state[0]+0x384)+0xa8 and fire the transition (0203c634 with
 * the 020ce328 continuation); otherwise keep waiting.
 */
struct vec { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern int  VEC_DotProduct(void *a, void *b);
extern void func_ov274_020d1f68(void);
extern short data_0203d210;
extern int  data_02041dc8;

void func_ov274_020d1e08(int *self) {
    int *state = (int *)self[1];
    struct vec v;
    struct vec dir;
    int target;

    target = func_ov107_020cab14(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], &v);
    func_01ff8d18(&v, &v);
    state[0xf] = *(int *)(*self + 0x2c) * 0x1e / 20;
    state[0x11] = func_020050b4(v.x, v.z);
    {
        unsigned short a =
            (unsigned short)((state[0x10] * 0x28be60db9391LL + 0x80000000000LL) >> 44);
        int idx = a >> 4;
        dir.x = (&data_0203d210)[idx * 2];
        dir.y = 0;
        dir.z = (&data_0203d210)[idx * 2 + 1];
    }
    *(struct vec *)(state + 5) = *(struct vec *)&data_02041dc8;
    if (VEC_DotProduct(&dir, &v) < 0xf00) {
        return;
    }
    *(char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov274_020d1f68);
}
