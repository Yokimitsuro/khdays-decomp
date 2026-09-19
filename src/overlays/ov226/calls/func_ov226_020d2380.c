/* Steering of the ov221 enemy: with a +0x78 target the +0x14 step is the sine/cosine of the
 * given heading scaled 0x100, otherwise the +0x3fc part's +0x2c offset rotated by it
 * (MTX_RotY33_). The +8 point plus the step is subtracted from the target's +0x190, flattened
 * and normalised, and +0x58 takes its heading. Unless grounded (+0x17a bit 0) the heading turns
 * towards +0x58 (0203d040) by rate x 40 / 100 (or 0 when the target is closer than 0x350a; x 300
 * without a target). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
struct Bit0 { unsigned char bit0 : 1; };

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_0203d040(int cur, int target, int step, int flag);
extern const short data_0203d210[];

void func_ov226_020d2380(int *node, int rad)
{
    int *state = (int *)node[1];
    Mtx33 m;
    Vec3 d;
    unsigned short idx;
    int len;
    int step;

    if (state[0x1e] != 0) {
        idx = FX_RadToIdx(rad);
        state[5] = data_0203d210[(idx >> 4) * 2];
        state[6] = 0;
        state[7] = data_0203d210[(idx >> 4) * 2 + 1];
        func_01ffa724(0x100, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    } else {
        idx = FX_RadToIdx(rad);
        MTX_RotY33_(&m, data_0203d210[(idx >> 4) * 2], data_0203d210[(idx >> 4) * 2 + 1]);
        MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x3fc) + 0x2c), &m, (Vec3 *)(state + 5));
    }
    VEC_Add((Vec3 *)state[2], (Vec3 *)(state + 5), &d);
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x3e8) + 0x190), &d, &d);
    d.y = 0;
    len = func_01ff8d18(&d, &d);
    state[0x16] = func_020050b4(d.x, d.z);
    if (((struct Bit0 *)(*state + 0x17a))->bit0 != 0) {
        return;
    }
    if (state[0x1e] != 0) {
        step = len < 0x350a ? 0 : 40;
    } else {
        step = 300;
    }
    state[0x14] = func_0203d040(state[0x14], state[0x16], *(int *)(node[0] + 0x2c) * step / 100, 0);
}
