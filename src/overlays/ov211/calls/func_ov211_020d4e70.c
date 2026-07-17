/*
 * func_ov211_020d4e70 -- x3 (ov210/211/282). Twin of Ov210_AimPerpStrafe (020d2d38) with the cross
 * product scaled by -0x100 (strafe the opposite way).
 */
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void VEC_CrossProduct(void *a, void *b, void *c);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203c634(int self, int idx, int cb);
extern int  data_02042264;

void func_ov211_020d4e70(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int target = func_ov107_020cab14(*state, 0);

    state[4] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
        v[1] = 0;
        func_01ff8d18(v, v);
        state[0xa] = func_020050b4(v[0], v[2]);
        VEC_CrossProduct(&data_02042264, v, (void *)(state + 5));
        func_01ffa724(-0x100, (void *)(state + 5), (void *)(state + 5));
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    *(char *)(*state + 0x1c7) = 2;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
