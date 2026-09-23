/* Turn `vec` by the fixed-point heading `angle` (Y rotation from the shared trig table), in place,
 * and copy it to *out. Twin of ov256 020cd054. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec)
{
    Mtx33 rot;

    {
        int idx = ANG2IDX(angle) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33(vec, &rot, vec);
    *out = *vec;
}
