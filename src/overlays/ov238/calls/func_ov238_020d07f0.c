/* Set the ov238 actor's +0xc velocity to `vec` turned by its +0x18 heading. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov238_020d07f0(int *node, Vec3 *vec)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    {
        int idx = ANG2IDX(state[6]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33(vec, &rot, (Vec3 *)(state + 3));
}
