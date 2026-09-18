/* Attack tick of the ov219 enemy: the +0x24 velocity is the +0x394 item's +0x2c vector rotated
 * by the +0xc yaw. Once the +4 item is idle the actor plays animation 7 (looped) and publishes a
 * zero vector with mode 2; the +0x14 timer becomes 0x7000 after sub-state 8, 0x3000 while the
 * +0x21a stamina is positive, else 0x4b000 scaled by 1.5 per +0x18 phase; the +0x3e flag is
 * cleared and the tick hands off to the guard state. */
typedef unsigned char u8;
typedef short s16;
struct Vecx32 { int x, y, z; };

extern void MTX_RotY33_(void *mtx, int sin, int cos);
extern void MTX_MultVec33(int *out, void *mtx, int *in);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const struct Vecx32 data_02041dc8;
extern void func_ov219_020d14dc(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov219_020d134c(int *node)
{
    int *state = (int *)node[1];
    int mtx[9];
    int idx;
    int i;

    idx = (unsigned short)((0x28BE60DB9391LL * state[3] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    MTX_RotY33_(mtx, data_0203d210[(idx >> 4) << 1], data_0203d210[((idx >> 4) << 1) + 1]);
    MTX_MultVec33((int *)(*(int *)(*state + 0x394) + 0x2c), mtx, state + 9);
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 7, 1);
    func_ov107_020c0b90(*state, 2, data_02041dc8, 0);
    if (*(signed char *)(*state + 0x1c6) == 8) {
        state[5] = 0x7000;
    } else if (*(s16 *)(*state + 0x21a) > 0) {
        state[5] = 0x3000;
    } else {
        state[5] = 0x4b000;
        for (i = 0; i < state[6]; i++) {
            state[5] = FX_Mul(state[5], 0x1800);
        }
    }
    *(u8 *)((char *)state + 0x3e) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov219_020d14dc);
}
