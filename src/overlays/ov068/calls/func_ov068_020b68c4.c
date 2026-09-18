/* Spawns the ov049 enemy's next effect (x4: ov049/068/087/104) when the rig's countdown at
 * +0x2e10 runs out: the countdown is re-armed to 0x3000 plus a shrinking bonus (0x6000 minus
 * 0x266 per spawn so far, floored at 0), the spawn count at +0x2e0c advances, and one of the
 * offsets of the 16-entry table (10 entries while +0x2e14 is clear) is picked at random,
 * rotated by the actor's heading, scaled by 5, added to the actor origin and jittered on x/z;
 * the point is raised to the ground and handed to the spawner with the rig. */
typedef long long s64;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 v[16]; } OffsetTable;

extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);         /* ScaleVec3Fx12 */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020307f4(int n);                                        /* Session_RandNextScaled */
extern int func_0203084c(void);                                         /* Session_RandNext */
extern void func_ov068_020b6b04(Vec3 *src, Vec3 *out);
extern void func_ov068_020b6a7c(char *self, char *rig, Vec3 *src);
extern short data_0203d210[];
extern OffsetTable data_ov068_020b7358;
extern char *data_ov068_020b7500;

void func_ov068_020b68c4(char *self, int dt)
{
    OffsetTable table;
    Vec3 out;
    Mtx33 m;
    char *rig = data_ov068_020b7500 + 0xfc + 0x2c00;
    int bonus;
    int count;
    int idx;
    int randomOffset;

    *(int *)(rig + 0x114) -= dt;
    if (*(int *)(rig + 0x114) > 0) {
        return;
    }
    bonus = 0x6000 - *(int *)(rig + 0x110) * 0x266;
    if (bonus < 0) {
        bonus = 0;
    }
    *(int *)(rig + 0x114) = bonus + 0x3000;
    *(int *)(rig + 0x110) += 1;
    table = data_ov068_020b7358;
    count = 16;
    if (*(int *)(rig + 0x118) == 0) {
        count -= 6;
    }
    idx = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
    MTX_RotY33_(&m, -data_0203d210[idx * 2], -data_0203d210[idx * 2 + 1]);
    MTX_MultVec33(&table.v[func_020307f4(count)], &m, &out);
    func_01ffa724(0x5000, &out, &out);
    VEC_Add((Vec3 *)(self + 0x8c + 0x400), &out, &out);
    randomOffset = func_0203084c() - 0x800;
    out.x += (int)(((s64)randomOffset * 0x333 + 0x800) >> 12);
    out.y = *(int *)(self + 0x490);
    randomOffset = func_0203084c() - 0x800;
    out.z += (int)(((s64)randomOffset * 0x333 + 0x800) >> 12);
    func_ov068_020b6b04(&out, &out);
    func_ov068_020b6a7c(self, rig, &out);
}
