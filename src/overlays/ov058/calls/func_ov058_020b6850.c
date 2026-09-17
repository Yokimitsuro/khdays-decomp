/* Compute one of this enemy's attack anchor points into `out`: the plain offset {0, 0x2000,
 * 0xfae} while the shared rig's +0x2cd4 flag is clear, otherwise the left/right offset picked
 * by `side` ({-0xc00, 0x2000, 0xfae} / {0xc00, 0x2000, 0xfd7}); the offset is turned by the
 * enemy's facing (angle at +0x80 of the +0x20 node, biased by 0x8000, /16 into the sin/cos
 * table, both components negated) and added to the enemy's origin at +0x48c. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 v[2]; } Ov039SidePair;

extern void MTX_RotY33_(Mtx33 *m, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern char *data_ov058_020b7e00;
extern const Vec3 data_ov058_020b7b90;               /* the plain anchor offset */
extern const Ov039SidePair data_ov058_020b7bb0;      /* the left/right anchor offsets */
extern short data_0203d210[];

void func_ov058_020b6850(char *self, int side, Vec3 *out)
{
    Mtx33 mFacing;
    Vec3 vDefault;
    Ov039SidePair sides;
    int nIndex;

    vDefault = data_ov058_020b7b90;
    sides = data_ov058_020b7bb0;

    if (*(int *)(data_ov058_020b7e00 + 0x2000 + 0xcd4) == 0) {
        out->x = vDefault.x;
        out->y = vDefault.y;
        out->z = vDefault.z;
    } else {
        out->x = sides.v[side].x;
        out->y = sides.v[side].y;
        out->z = sides.v[side].z;
    }
    nIndex = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
    MTX_RotY33_(&mFacing, -data_0203d210[nIndex * 2], -data_0203d210[nIndex * 2 + 1]);
    MTX_MultVec33(out, &mFacing, out);
    VEC_Add((Vec3 *)(self + 0x8c + 0x400), out, out);
}
