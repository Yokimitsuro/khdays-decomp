/* Aim the ov283 actor's +0x10 velocity: a diagonal unit step turned by the +0x44 heading, normalised and
 * scaled to 0.25; both headings (+0x38, +0x40) point along it. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov283_020ccbe0(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    state[4] = 0x1000;
    state[5] = 0;
    state[6] = 0x1000;
    {
        int idx = ANG2IDX(state[0x11]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(state + 4), &rot, (Vec3 *)(state + 4));
    func_01ff8d18((Vec3 *)(state + 4), (Vec3 *)(state + 4));
    func_01ffa724(0x400, (Vec3 *)(state + 4), (Vec3 *)(state + 4));
    state[0xe] = state[0x10] = func_020050b4(state[4], state[6]);
}
