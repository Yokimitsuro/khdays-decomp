/* Hop tick of the ov125 enemy: the +0x3c counter is reseeded with 15 times the owner's +0x2c
 * rate and the +0x2c timer counts it down; once it runs out, if both +0x3a0 sub-nodes have bit
 * 0 of their +0x60 word clear the hop ends -- timer cleared, animation 0x11b (mode 4, +0x24
 * blend) requested and the landing think callback registered. Otherwise the pose at +0x68 is
 * spun by the hop rate (30 x rate x 0.196) times the +0x4c count about the +0x40 axis and
 * renormalised. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Owner { char pad[0x3a0]; int nodes[2]; };

extern void func_ov107_020c5af8(int owner, int anim, int mode, int blend);
extern void func_0203c634(int self, int idx, void *cb);
extern int func_02020400(int a, int b);
extern void func_0202f188(void *dst, void *axis, int angle);
extern void func_0202ef54(void *out, void *a, void *b);
extern void func_0202f4a4(void *out, void *in);
extern void func_ov126_020d1de8(void);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov126_020d1cb8(int *self) {
    int *state = (int *)self[1];
    int m[4];
    int i;
    int n;

    state[0xf] = *(int *)(self[0] + 0x2c) * 0x1e / 2;
    state[0xb] -= *(int *)(self[0] + 0x2c);
    if (state[0xb] <= 0) {
        n = 0;
        for (i = 0; i < 2; i++) {
            if ((((struct hw60 *)(((struct Owner *)*state)->nodes[i] + 0x60))->lo & 1) == 0) {
                n++;
            }
            if (n >= 2) {
                state[0xb] = 0;
                func_ov107_020c5af8(*state, 0x11b, 4, state[9]);
                func_0203c634((int)self, *(signed char *)((int)self + 0x20), &func_ov126_020d1de8);
                return;
            }
        }
    }
    func_0202f188(m, state + 0x10, func_02020400(FX_Mul(*(int *)(self[0] + 0x2c) * 0x1e, 0x3244), state[0x13]));
    func_0202ef54(state + 0x1a, state + 0x1a, m);
    func_0202f4a4(state + 0x1a, state + 0x1a);
}
