/*
 * func_ov208_020d1e84 -- x3 (ov208/209/268). AI-state tick: face the target and fire, branching the
 * attack on whether we're aligned.
 * state[0x18] = owner_delta*30/10. Acquire target (020d0ea4) -> state[4]; none -> mark
 * *state[0]+0x1c7=2 and bail (0203c634 cb=0). Else clear state[0xb] and the state+0x49 byte, build a
 * heading vec {sin,0,cos} from state[0xc] (Q12 rad -> sin/cos table, computed inline per component),
 * dir = normalise(target(+0x190) - state[2]); state[0xd] = atan2(dir.x, dir.z). If heading . dir >=
 * 0xf00 fire attack 3 and go to the 020d215c state; else fire attack 9 and go to 020d2024.
 */
struct vec { int x, y, z; };
extern int  func_ov208_020d0ea4(int obj, void *p);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern int  VEC_DotProduct(void *a, void *b);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov208_020d215c(void);
extern void func_ov208_020d2024(void);
extern short data_0203d210;

void func_ov208_020d1e84(int *self) {
    int *state = (int *)self[1];
    struct vec v;
    struct vec dir;
    int target;

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    target = func_ov208_020d0ea4(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    state[0xb] = 0;
    *(char *)((int)state + 0x49) = 0;
    dir.x = (&data_0203d210)[
        ((unsigned short)((state[0xc] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4) * 2];
    dir.y = 0;
    dir.z = (&data_0203d210)[
        ((unsigned short)((state[0xc] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4) * 2 + 1];
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[2], &v);
    func_01ff8d18(&v, &v);
    state[0xd] = func_020050b4(v.x, v.z);
    if (VEC_DotProduct(&dir, &v) >= 0xf00) {
        func_ov107_020c9264(*state, 3, 0);
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov208_020d215c);
        return;
    }
    func_ov107_020c9264(*state, 9, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov208_020d2024);
}
