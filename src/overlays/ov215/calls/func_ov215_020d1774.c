/*
 * Airborne step: drift the actor along its heading, and on landing hand off or bail out.
 */

struct Vecx32 { int x, y, z; };

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned char hasLanding : 1;
} LandingFlag;

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern void func_01ffa724(int scale, void *v, void *dst);
extern void VEC_Add(void *a, void *b, void *dst);
extern void func_ov107_020c0b90(int obj, int a, struct Vecx32 v, int b);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_ov107_020c5af8(int obj, int id, int a, void *v);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov215_020d0a84(int *state, int a, int b);
extern void func_ov215_020d1930(void);
extern short data_0203d210[];

void func_ov215_020d1774(int *self) {
    int *state = (int *)self[1];
    struct Vecx32 dir;
    int idx;
    short kind;

    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[0x11] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    kind = *(short *)(*(int *)(*(int *)(*state + 0x420) + 0x88) + 2);
    VEC_Set(&dir, (int)data_0203d210[idx * 2], 0, (int)data_0203d210[idx * 2 + 1]);
    func_01ffa724(state[0x12] / 40, &dir, state + 8);
    VEC_Add(state + 8, (void *)(*state + 0x424), state + 8);
    if (kind != 3) {
        return;
    }

    ((Hw60 *)(*state + 0x60))->hi &= ~0x40;
    if (((LandingFlag *)(*state + 0x17a))->hasLanding) {
        *(struct Vecx32 *)(state + 0xe) = *(struct Vecx32 *)(*state + 0x180);
        state[0xf] -= *(int *)(*state + 0x80);
        func_ov107_020c0b90(*state, 3, *(struct Vecx32 *)(state + 0xe), 0);
        func_ov107_020c9264(*state, 5, 0);
        func_ov107_020c5af8(*state, 0x129, 7, state + 0xe);
        state[0x14] = 0;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), func_ov215_020d1930);
    } else {
        func_ov215_020d0a84(state, 1, 0);
    }
}
