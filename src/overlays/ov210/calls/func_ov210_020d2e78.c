/*
 * func_ov210_020d2e78 -- x3 (ov210/211/282). Twin of Ov210_StrafeSameTarget (020d2b60) with the cross
 * product scaled by -0x100, attack 0x10, and the 020d2f5c continuation.
 */
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void VEC_CrossProduct(void *a, void *b, void *c);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern int  data_02042264;
extern void func_ov210_020d2f5c(void);

void func_ov210_020d2e78(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int target = func_ov107_020cab14(*state, 0);

    if (state[4] != target) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], v);
    v[1] = 0;
    func_01ff8d18(v, v);
    state[0xa] = func_020050b4(v[0], v[2]);
    VEC_CrossProduct(&data_02042264, v, (void *)(state + 5));
    func_01ffa724(-0x100, (void *)(state + 5), (void *)(state + 5));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x10, 1);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov210_020d2f5c);
}
