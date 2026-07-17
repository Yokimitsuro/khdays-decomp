/*
 * func_ov209_020d3ee0 -- x3 (ov208/209/268). Twin of Ov208_FaceTargetFireReady (020d2024) with
 * attack 3 and the 020d215c continuation.
 */
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov209_020d3f7c(void);

void func_ov209_020d3ee0(int *self) {
    int *state = (int *)self[1];
    int v[3];

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[2], v);
    state[0xd] = func_020050b4(v[0], v[2]);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 3, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov209_020d3f7c);
}
