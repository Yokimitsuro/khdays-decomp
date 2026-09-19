/* Spawns a projectile of the mission enemy from a descriptor unless the actor carries flag
 * bit 27. The placement is the descriptor's +0x1c offset rotated by the actor's heading and
 * added to its +0x48c position, its scale is the descriptor's id and its direction the
 * descriptor's +0x28 vector rotated and normalised. `flag` marks a kind-1/2 shot and bit 1 of
 * the descriptor's +0x14 adds mode bit 0. Always 0. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;
typedef struct {
    Vec3 pos;
    short sx, sy, sz, scale;
    int f14, f18, f1c, f20, f24, f28;
} Placement;

struct ShotDesc {
    int nId;                  /* 0x00 */
    char pad004[0x10];
    unsigned char nFlags14;   /* 0x14 */
    char pad015[7];
    Vec3 vOffset;             /* 0x1c */
    Vec3 vDir;                /* 0x28 */
};

struct b2 { unsigned char b0 : 1, b1 : 1; };

extern void MTX_RotY33_(MtxFx33 *, int, int);
extern void MTX_MultVec33(const Vec3 *, const MtxFx33 *, Vec3 *);
extern void VEC_Add(const Vec3 *, const Vec3 *, Vec3 *);
extern int VEC_Mag(const Vec3 *);
extern int func_01ff8d18(const Vec3 *, Vec3 *);
extern void func_ov022_02091324(char *, Placement *);
extern const short data_0203d210[];

int func_ov062_020b634c(char *self, Vec3 *pos, struct ShotDesc *desc, int flag)
{
    Placement req;
    Vec3 dir;
    MtxFx33 mtx;
    int i;

    if ((*(unsigned long long *)self & 0x8000000) == 0) {
        i = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
        MTX_RotY33_(&mtx, -data_0203d210[i * 2], -data_0203d210[i * 2 + 1]);
        MTX_MultVec33(&desc->vOffset, &mtx, &dir);
        req.scale = desc->nId;
        VEC_Add((Vec3 *)(self + 0x8c + 0x400), &dir, &req.pos);
        MTX_MultVec33(&desc->vDir, &mtx, &dir);
        if (VEC_Mag(&dir) != 0) {
            func_01ff8d18(&dir, &dir);
        }
        req.sx = dir.x;
        req.sy = dir.y;
        req.sz = dir.z;
        req.f14 = 0;
        req.f18 = 0;
        req.f1c = 0;
        req.f20 = 0;
        req.f28 = 0;
        req.f24 = 0;
        if (flag != 0) {
            req.f18 = 1;
            req.f20 |= 2;
        }
        if (((struct b2 *)&desc->nFlags14)->b1 != 0) {
            req.f20 |= 1;
        }
        func_ov022_02091324(self, &req);
    }
    return 0;
}
