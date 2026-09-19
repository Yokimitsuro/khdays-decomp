/* Pair-up wait tick: runs the +0x1c timer; until it passes 0x1aaa (or the +0x3dc partner raises
 * bit 1 of its +0x394 word) nothing happens. Then the aim pose at +0x38 is rebuilt from
 * data_02042264 and atan2 of the flattened, normalised direction from the actor to the partner,
 * copied down to +0x28, pose 0xa plays on the actor, flag 0x80 clears in its +0x60 high byte,
 * pose 2 plays on the partner and the node moves to 020cee0c. */
typedef unsigned short u16;
struct m4 { int w[4]; };
struct S213 { char pad[0x28]; struct m4 dst; struct m4 src; };
struct Flags394 { int b0 : 1; int b1 : 1; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern int  func_020050b4(int x, int z);
extern void func_0202f188(void *dst, void *k, int angle);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov213_020cee0c(void);
extern int  data_02042264;

void func_ov213_020cecfc(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int partner;

    state[7] += *(int *)(self[0] + 0x2c);
    partner = *(int *)(*state + 0x3dc);
    if (((struct Flags394 *)(partner + 0x394))->b1 == 0) {
        if (state[7] < 0x1aaa) return;
    }
    VEC_Subtract((void *)(partner + 0x74), (void *)(*state + 0x74), v);
    v[1] = 0;
    func_01ff8d18(v, v);
    func_0202f188((void *)(state + 0xe), &data_02042264, func_020050b4(v[0], v[2]));
    ((struct S213 *)state)->dst = ((struct S213 *)state)->src;
    func_ov107_020c9264(*state, 0xa, 0);
    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*(int *)(*state + 0x3dc), 2, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov213_020cee0c);
}
