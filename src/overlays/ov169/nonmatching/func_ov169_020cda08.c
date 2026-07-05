/* NONMATCHING: equivalent C, 1 redundant-move tie (count=5, 380B). 379/380
 * bytes byte-exact (VEC pipeline, abs-diff 0x24 adjust, 0x5c countdown, rand-
 * gated 0x1c7 state, advance -- ALL match). The ONLY diff: in the rand gate the
 * original emits a redundant `add r1,r0,#0` (copies rnd->r1 to free r0 for the
 * `holder->0x5c=0` store), then compares r1; mwcc keeps rnd in r0 and puts the
 * 0 in r1 (1 instr shorter). Can't force mwcc to emit the wasteful move -- no
 * source form (rnd var, comma-store, store reorder) reproduces it. Array decl
 * order matters: declare b BEFORE a so a gets sp[0]/b gets sp[0xc] (mwcc lays
 * first-declared at the higher offset). VEC_CrossProduct=func_01ff8c34,
 * VEC_Add=func_01ff8b90 canonicalized; func_01ffa724/func_01ff8d18 raw-valid. */
extern int func_ov107_020cab14(int node, int flag);
extern int func_0203c634();
extern int func_ov169_020cca34(int this_, int *out);
extern int func_01ffa724();
extern int VEC_CrossProduct();
extern int func_01ff8d18();
extern int VEC_Add();
extern int func_02023eb4(int x);
extern int func_ov169_020ccacc(int this_);
extern int data_02042264;

void func_ov169_020cda08(int this_) {
    int holder = *(int *)(this_ + 4);
    int b[3];
    int a[3];
    int r;
    int st;

    r = func_ov107_020cab14(*(int *)holder, 0);
    *(int *)(holder + 0xc) = r;
    if (r == 0) {
        *(signed char *)(*(int *)holder + 0x1c7) = 2;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }

    r = func_ov169_020cca34(this_, b);
    if (r > 0x100) r = 0x180;
    func_01ffa724(r, b, holder + 0x20);
    VEC_CrossProduct(&data_02042264, b, a);
    func_01ff8d18(a, a);
    func_01ffa724(*(int *)(holder + 0x60) * 0x180, a, a);
    VEC_Add(holder + 0x20, a, holder + 0x20);

    {
        int p = *(int *)(*(int *)(holder + 0xc) + 0x78);
        int q = *(int *)(*(int *)(holder + 8) + 4);
        int d = p - q;
        if ((d < 0 ? -d : d) > 0x80) {
            if (p < q)
                *(int *)(holder + 0x24) -= 0x60;
            else
                *(int *)(holder + 0x24) += 0x60;
        }
    }

    *(int *)(holder + 0x5c) -= *(int *)(*(int *)this_ + 0x2c);
    if (*(int *)(holder + 0x5c) > 0) return;

    r = func_02023eb4(0x65);
    *(int *)(holder + 0x5c) = 0;
    if (r < 0x3c && func_ov169_020ccacc(this_) != 0)
        st = 8;
    else
        st = 5;
    *(signed char *)(*(int *)holder + 0x1c7) = st;
    if (*(signed char *)(*(int *)holder + 0x1c7) == -1) return;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
