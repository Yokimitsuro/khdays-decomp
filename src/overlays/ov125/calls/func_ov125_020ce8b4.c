/*
 * func_ov125_020ce8b4 -- AI-state entry: aim the sub-node at the anchor midpoint, arm it,
 * dispatch. v = ((+0x394)->+0x14 + (+0x398)->+0x14) of the owner scaled by 0x800 (midpoint of
 * two anchors), pulled 0x100 towards the player's +0x7c position. Clear bit 1 of
 * *(state[4]+0x5c); orient the sub-node matrix at state[4]+4 toward v (0203ca30). Enable hit
 * regions 0,2,4 via 0203b9fc(state[4], region, 0, 1). Zero state[0xc], then hand off to the
 * 020ce998 state.
 */
extern void VEC_Add(void *a, void *b, void *out);
extern void func_01ffa724(int scale, void *in, void *out);
extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void func_0203ca30(int p, void *v);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov125_020ce998(void);

void func_ov125_020ce8b4(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int w[3];

    VEC_Add((void *)(*(int *)(*state + 0x394) + 0x14), (void *)(*(int *)(*state + 0x398) + 0x14), v);
    func_01ffa724(0x800, v, v);
    func_01ffa724(-0x100, (void *)(*OS_IsThreadAvailable_0x020c9848() + 0x7c), w);
    VEC_Add(v, w, v);
    *(int *)(state[4] + 0x5c) &= ~2;
    func_0203ca30(state[4] + 4, v);
    func_0203b9fc(state[4], 0, 0, 1);
    func_0203b9fc(state[4], 2, 0, 1);
    func_0203b9fc(state[4], 4, 0, 1);
    state[0xc] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov125_020ce998);
}
