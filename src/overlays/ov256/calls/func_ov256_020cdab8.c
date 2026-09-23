/* Path probe of the ov256 actor: `dir` is turned by the +0x40 heading; mode 0 probes from its +0x74
 * position along it with a 2.19 radius (01fff8e8), otherwise a floor probe runs there (01fff8b8).
 * Returns whether something was hit. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void *func_01fff8e8(void *collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern void *func_01fff8b8(void *collision, Vec3 *origin, Vec3 *out, int flag);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

int func_ov256_020cdab8(int *node, Vec3 *dir, int mode)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    Vec3 floor;
    int scene;
    void *hit;

    {
        int idx = ANG2IDX(state[0x10]) * 2;

        scene = *(int *)(*state + 4);
        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33(dir, &rot, dir);
    if (mode == 0) {
        hit = func_01fff8e8(*(void **)(scene + 0x7c), (Vec3 *)(*state + 0x74), dir, 0x2300, 0);
    } else {
        hit = func_01fff8b8(*(void **)(scene + 0x7c), (Vec3 *)(*state + 0x74), &floor, 0);
    }
    return hit != 0;
}
