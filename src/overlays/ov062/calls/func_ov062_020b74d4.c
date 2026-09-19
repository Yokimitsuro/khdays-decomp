/* Swings one request effect of the mission enemy and computes its world offset. The effect's
 * row (+0x2e64 rows of the mission owner, stride 0x240, by the +1 slot byte) sweeps its +0x230
 * angle by the +0x234 speed as a pendulum bounded by +0x220: once the swing leaves the band
 * around zero it is clamped to the bound and the speed reversed. Rows 0/1 yaw by the angle;
 * row 2 yaws by minus three times it and row 3 by three times it, both then pitching by the
 * angle less the bound. The effect's +0x1c offset rotated by the result is written to out. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;

struct SwingRow {
    char pad000[0x220];
    int nBound;               /* 0x220 */
    char pad224[0xc];
    int nAngle;               /* 0x230 */
    int nSpeed;               /* 0x234 */
};

extern void MTX_Identity33_(MtxFx33 *m);
extern void MTX_RotY33_(MtxFx33 *m, int nSin, int nCos);
extern void MTX_RotX33_(MtxFx33 *m, int nSin, int nCos);
extern void MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *out);
extern void MTX_MultVec33(const Vec3 *v, const MtxFx33 *m, Vec3 *out);
extern char *data_ov062_020b80e0;
extern const short data_0203d210[];

void func_ov062_020b74d4(char *pEffect, Vec3 *out)
{
    MtxFx33 m;
    MtxFx33 mPitch;
    MtxFx33 mYaw;
    struct SwingRow *pRow = (struct SwingRow *)(data_ov062_020b80e0 + 0x264 + 0x2c00
                                                + *(signed char *)(pEffect + 1) * 0x240);
    u16 nAngle = pRow->nAngle + pRow->nSpeed;
    u16 nPitch;
    int i;

    if (pRow->nBound <= nAngle && nAngle <= 0xffff - pRow->nBound) {
        if (pRow->nSpeed > 0) {
            nAngle = pRow->nBound;
        } else {
            nAngle = 0xffff - pRow->nBound;
        }
        pRow->nSpeed = -pRow->nSpeed;
    }
    pRow->nAngle = nAngle;
    MTX_Identity33_(&m);
    switch (*(signed char *)(pEffect + 1)) {
    case 0:
    case 1:
        i = nAngle >> 4;
        MTX_RotY33_(&mYaw, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
        MTX_Concat33(&mYaw, &m, &m);
        break;
    case 2:
        i = (u16)(-nAngle * 3) >> 4;
        nPitch = nAngle - pRow->nBound;
        MTX_RotY33_(&mYaw, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
        MTX_Concat33(&mYaw, &m, &m);
        i = nPitch >> 4;
        MTX_RotX33_(&mPitch, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
        MTX_Concat33(&mPitch, &m, &m);
        break;
    case 3:
        i = (u16)(nAngle * 3) >> 4;
        nPitch = nAngle - pRow->nBound;
        MTX_RotY33_(&mYaw, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
        MTX_Concat33(&mYaw, &m, &m);
        i = nPitch >> 4;
        MTX_RotX33_(&mPitch, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
        MTX_Concat33(&mPitch, &m, &m);
        break;
    }
    MTX_MultVec33((Vec3 *)(pEffect + 0x1c), &m, out);
}
