/* Chase tick of the ov219 enemy: the +0x24 velocity is the +0x10 yaw's (sin, 0, cos) scaled by
 * 0x800 and the +0x14 clock grows by 0x800 per tick. Below 0x11000 without bit 1 of the actor's
 * +0x17a flags the attack sweep runs (kind 0); otherwise the actor plays animation 5, publishes
 * a zero vector with mode 4 (flag 1) and hands off to the next chase state. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };
struct Flags17a { u8 b0 : 1, b1 : 1; };

extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov219_020d039c(int *state, int kind);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const struct Vecx32 data_02041dc8;
extern void func_ov219_020d1144(int *node);

void func_ov219_020d1028(int *node)
{
    int *state = (int *)node[1];
    int idx;

    idx = (unsigned short)((0x28BE60DB9391LL * state[4] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    state[9] = data_0203d210[(idx >> 4) << 1];                                        /* FX_SinIdx */
    state[10] = 0;
    state[11] = data_0203d210[((idx >> 4) << 1) + 1];                                 /* FX_CosIdx */
    func_01ffa724(0x800, state + 9, state + 9);
    state[5] += 0x800;
    if (state[5] >= 0x11000 || ((struct Flags17a *)(*state + 0x17a))->b1) {
        func_ov107_020c9264(*state, 5, 0);
        func_ov107_020c0b90(*state, 4, data_02041dc8, 1);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov219_020d1144);
        return;
    }
    func_ov219_020d039c(state, 0);
}
