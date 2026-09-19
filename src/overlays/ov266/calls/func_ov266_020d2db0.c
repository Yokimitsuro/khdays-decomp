/* Orbit step of the ov266 sub-actor. Mode 0 zeroes the +8 velocity; modes 1/2 set it to 0.5
 * along the +0x14 direction and, while the +0x24 phase has not passed the +0x28 span (and the
 * span is non-zero), tilt it: the phase as a fraction of the span picks a cosine, scaled by
 * 0x138c (16-bit) and by the +0x30 amplitude into a yaw, and the velocity is turned by it
 * along with a 0.5 forward step scaled to the frame (rate / 0x88) whose z advances the phase,
 * clamped at the span while still below it. The velocity is published to the actor's +0xf0. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02020400(int a, int b);
extern void MTX_RotY33_(MtxFx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const MtxFx33 *m, Vec3 *out);
extern int FX_Inv(int num, int den);
extern const Vec3 data_02041dc8;
extern const short data_0203d210[];

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov266_020d2db0(int *node)
{
    int *state = (int *)node[1];
    MtxFx33 m;
    Vec3 v;
    int i;
    int k;
    unsigned short idx;

    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        *(Vec3 *)(state + 2) = data_02041dc8;
        break;
    case 1:
    case 2:
        func_01ffa724(0x800, (Vec3 *)(state + 5), (Vec3 *)(state + 2));
        if (state[9] > state[10] || state[10] == 0) {
            break;
        }
        i = func_02020400(state[9] << 15, state[10]) >> 4;
        k = data_0203d210[i * 2 + 1] * (short)0x138c / 0x1000;
        idx = FX_RadToIdx(state[0xc] * k);
        MTX_RotY33_(&m, data_0203d210[(idx >> 4) * 2], data_0203d210[(idx >> 4) * 2 + 1]);
        MTX_MultVec33((Vec3 *)(state + 2), &m, (Vec3 *)(state + 2));
        v.z = 0x800;
        v.x = 0;
        v.y = 0;
        MTX_MultVec33(&v, &m, &v);
        func_01ffa724(FX_Inv(*(int *)(node[0] + 0x2c), 0x88), &v, &v);
        if (state[9] < state[10]) {
            state[9] += v.z;
            if (state[9] > state[10]) {
                state[9] = state[10];
            }
        } else {
            state[9] += v.z;
        }
        break;
    }
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 2);
}
