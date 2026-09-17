/* Start this enemy's flight along the shared rig's flight block (+0x2cd4 of the object): the
 * flight mode at +0x14 picks the pattern (1: lift on, timer 0, 6 laps; 2: 3 laps; 3: 1 lap with a
 * 0x6000 timer; anything else does nothing). The flight then starts from the enemy's current
 * position (020ad44c) heading along its facing (unit vector of (0, 0, 0x1000) turned by the
 * angle at +0x80 of the +0x20 node), with the lap count at +0x2fdc, progress 0, the owner id
 * from +0x66 and the running flag at +0x2fe4. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void func_ov022_020ad44c(Vec3 *pOut, char *self);
extern void MTX_RotY33_(Mtx33 *m, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern char *data_ov039_020b5600;
extern short data_0203d210[];

void func_ov039_020b4820(char *self)
{
    Vec3 vDir;
    Mtx33 mFacing;
    Vec3 vFrom;
    char *flight = data_ov039_020b5600 + 0xd4 + 0x2c00;
    int bStart = 1;
    int nLaps;
    int nIndex;

    switch (*(int *)(flight + 0x14)) {
    case 1:
        *(int *)(flight + 0x338) = 1;
        *(int *)(flight + 0x318) = 0;
        nLaps = 6;
        break;
    case 2:
        *(int *)(flight + 0x338) = 0;
        *(int *)(flight + 0x318) = 0;
        nLaps = 3;
        break;
    case 3:
        *(int *)(flight + 0x338) = 0;
        nLaps = 1;
        *(int *)(flight + 0x318) = 0x6000;
        break;
    default:
        bStart = 0;
        break;
    }
    if (bStart == 0) {
        return;
    }
    func_ov022_020ad44c(&vFrom, self);
    *(Vec3 *)(flight + 0x31c) = vFrom;
    nIndex = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
    MTX_RotY33_(&mFacing, -data_0203d210[nIndex * 2], -data_0203d210[nIndex * 2 + 1]);
    vDir.x = 0;
    vDir.y = 0;
    vDir.z = 0x1000;
    MTX_MultVec33(&vDir, &mFacing, &vDir);
    if (VEC_Mag(&vDir) == 0) {
        *(Vec3 *)(flight + 0x328) = vDir;
    } else {
        func_01ff8d18(&vDir, (Vec3 *)(flight + 0x328));
    }
    *(int *)(flight + 0x308) = nLaps;
    *(int *)(flight + 0x30c) = 0;
    *(char *)(flight + 0x334) = (char)*(short *)(self + 0x66);
    *(int *)(flight + 0x310) = 1;
}
