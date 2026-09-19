/*
 * func_ov125_020ce998 -- aim wind-up tick. Recompute the aim point (anchor midpoint pulled 0x100
 * towards the player's +0x7c) and the +0x30 timer accumulates the owner's rate; the state[4]
 * sub-node is placed at the aim point and grows with the timer (2t/0x2000 + 1 on x/y, 1 on z).
 * Once the timer reaches 0x2000 the release fires: state[4] gets bit 1, state[2] loses it, is
 * placed at the aim point and scaled 4/4/1; the +0x18 direction is the owner's +0xa0 basis turned
 * by data_02042258, zero-scaled and offset from the aim point, copied to +0x24; state[1] loses bit 1,
 * is scaled 2/0/2, given the direction's pose (ed60 by data_02042240 + normalise) and placed at
 * the aim point; the timer is cleared and the 020ceb74 state registered.
 */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Add(void *a, void *b, void *out);
extern void func_01ffa724(int scale, void *in, void *out);
extern int *OS_IsThreadAvailable_0x020c9848(void);
extern int FX_Inv(int num, int den);
extern void func_0203ca30(void *p, void *v);
extern void func_0203ca50(void *placement, int x, int y, int z);
extern void func_0202f384(void *out, void *pose, void *k);
extern void func_0202ed60(void *dst, void *src, void *m);
extern void func_0202f4a4(void *out, void *in);
extern void func_0203c9d0(void *pose, void *q);
extern void func_0203c634(int self, int idx, int cb);
extern int data_02042258;
extern int data_02042240;
extern void func_ov125_020ceb74(void);

void func_ov125_020ce998(int *self) {
    int *state = (int *)self[1];
    Vec3 v;
    Vec3 dir;
    Vec3 w;
    Vec3 pose;
    int q[4];
    int t;

    VEC_Add((void *)(*(int *)(*state + 0x394) + 0x14), (void *)(*(int *)(*state + 0x398) + 0x14), &v);
    func_01ffa724(0x800, &v, &v);
    func_01ffa724(-0x100, (void *)(*OS_IsThreadAvailable_0x020c9848() + 0x7c), &w);
    VEC_Add(&v, &w, &dir);
    state[0xc] += *(int *)(self[0] + 0x2c);
    t = FX_Inv(state[0xc], 0x2000);
    func_0203ca30((void *)(state[4] + 4), &dir);
    func_0203ca50((void *)(state[4] + 4), t * 2 + 0x1000, t * 2 + 0x1000, 0x1000);
    if (state[0xc] < 0x2000) {
        return;
    }
    *(int *)(state[4] + 0x5c) |= 2;
    *(int *)(state[2] + 0x5c) &= ~2;
    func_0203ca30((void *)(state[2] + 4), &dir);
    func_0203ca50((void *)(state[2] + 4), 0x4000, 0x4000, 0x1000);
    func_0202f384(&pose, (char *)*state + 0xa0, &data_02042258);
    func_01ffa724(0, &pose, state + 6);
    VEC_Add(&v, state + 6, state + 6);
    *(Vec3 *)(state + 9) = *(Vec3 *)(state + 6);
    *(int *)(state[1] + 0x5c) &= ~2;
    func_0203ca50((void *)(state[1] + 4), 0x2000, 0, 0x2000);
    func_0202ed60(q, &data_02042240, &pose);
    func_0202f4a4(q, q);
    func_0203c9d0((void *)(state[1] + 4), q);
    func_0203ca30((void *)(state[1] + 4), &v);
    state[0xc] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov125_020ceb74);
}
