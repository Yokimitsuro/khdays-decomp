/*
 * NON-MATCHING: size-exact (368B) and structurally byte-exact -- the hw60 conditional (bitfield
 * `->hi |= 2` / `->hi &= ~2` with the ROM's `cmp #0x1000; bgt` branch layout and the &=~2 u16-trunc),
 * the dispatch-4 out-of-line block, and every FX call reproduce. Two matching devices are already in:
 * `owner = *state` cached (forces the r6/r7 four-callee-saved allocation) and a volatile v[0] reload
 * before the <=0x800 test (the ROM re-reads v[0] there). Residual: `node` and `owner` land in swapped
 * callee-saved registers -- ROM node=r7/owner=r6, mwcc 3.0/139 node=r6/owner=r7 -- and state[1]=node
 * stores from r0 (ROM) vs r6 (mwcc). Reordering the radius addition and the declarations did not flip
 * it. A node/owner register-allocation tie; result identical.
 */
/*
 * func_ov185_020cefa8 -- x3 (ov185/...). Home in on the acquired target and steer toward it.
 * state = *(self+4). Acquire the target relative vector into v via 020cab14(*state, v); if nothing was
 * acquired, store the (null) handle and bail. Distance = FX_Sqrt(v[0]) minus both radii; keep it in
 * v[0]. Set hw60 bit 9 when within 0x1000, clear it otherwise. If the distance exceeds the max reach
 * *(*state+0x2d8), stop. Otherwise refresh the aim (020ce6fc) and build the desired heading
 * (0202f384 with data_02042258): very close (<=0x800) just scales the stored dir by half the speed;
 * out of the mid-window (>0x1000) latches attack state 4 and hands off (0203c634); in between, cross
 * with data_02042264, add, normalise and scale by speed*timer.
 */
extern int func_ov107_020cab14(int owner, int *out);
extern int FX_Sqrt(int x);
extern void func_ov185_020ce6fc(int *state, int *rig);
extern void func_0202f384(unsigned int *out, int *in, void *basis);
extern void func_01ffa724(int scale, int *v, unsigned int *out);
extern void VEC_CrossProduct(int *a, void *b, int *out);
extern void VEC_Add(int *a, int *b, int *out);
extern int func_01ff8d18(unsigned int *v, int *out);
extern void func_0203c634(int self, int idx, int cb);
extern int data_02042258;
extern int data_02042264;

struct hw16 { unsigned short lo : 8, hi : 8; };

void func_ov185_020cefa8(int self, int p2, int p3, int p4) {
    int *state = *(int **)(self + 4);
    int v[7];
    int node = func_ov107_020cab14(*state, v);
    int owner;
    int dist;

    state[1] = node;
    if (node == 0) {
        return;
    }
    owner = *state;
    dist = FX_Sqrt(v[0]) - (*(int *)(node + 0x80) + *(int *)(owner + 0x80));
    v[0] = dist;
    if (dist <= 0x1000) {
        ((struct hw16 *)(*state + 0x60))->hi |= 2;
    } else {
        ((struct hw16 *)(*state + 0x60))->hi &= ~2;
    }
    if (dist > *(int *)(*state + 0x2d8)) {
        return;
    }
    func_ov185_020ce6fc(state, state + 6);
    func_0202f384((unsigned int *)&v[4], state + 2, &data_02042258);
    if (*(volatile int *)v <= 0x800) {
        func_01ffa724(state[0x18] / 2, &v[4], (unsigned int *)(state + 0xb));
        return;
    }
    if (v[0] <= 0x1000) {
        VEC_CrossProduct(&v[4], &data_02042264, &v[1]);
        VEC_Add(&v[1], &v[4], state + 0xb);
        func_01ff8d18((unsigned int *)(state + 0xb), state + 0xb);
        func_01ffa724(state[0x18] * state[0x17], state + 0xb, (unsigned int *)(state + 0xb));
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
