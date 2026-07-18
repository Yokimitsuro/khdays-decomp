/*
 * func_ov271_020d2630 -- x3. AI-state entry: aim the sub-node at the anchor midpoint, arm it, dispatch.
 * v = (state[0x12] + state[0x13]) scaled by 0x800 (midpoint of two anchors). Clear bit1 of
 * *(state[3]+0x5c); orient the sub-node matrix at state[3]+4 toward v (0203ca30). Enable hit regions
 * 0,2,4 via 0203b9fc(state[3], region, 0, 1). Zero state[0xd]/[0xf]/[0x10] and the *(u8)(state+0x44)
 * flag, then hand off to the 020d0878 state.
 */
extern void VEC_Add(void *a, void *b, void *out);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203ca30(int p, void *v);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov271_020d26ec(void);

void func_ov271_020d2630(int *self) {
    int *state = (int *)self[1];
    int v[3];

    VEC_Add((void *)state[0x12], (void *)state[0x13], v);
    func_01ffa724(0x800, v, v);
    *(int *)(state[3] + 0x5c) &= ~2;
    func_0203ca30(state[3] + 4, v);
    func_0203b9fc(state[3], 0, 0, 1);
    func_0203b9fc(state[3], 2, 0, 1);
    func_0203b9fc(state[3], 4, 0, 1);
    state[0xd] = 0;
    state[0xf] = 0;
    state[0x10] = 0;
    *(char *)((int)state + 0x44) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov271_020d26ec);
}
