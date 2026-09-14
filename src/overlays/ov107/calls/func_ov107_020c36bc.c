typedef int fx32;
typedef long long fx64;
typedef unsigned char u8;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Segment {
    VecFx32 p0;
    VecFx32 dir;
    fx32 scale;
} Segment;

typedef struct HitShape {
    u8 mode : 4;
    char pad001[0x68 - 1];
    VecFx32 sphereCenter;   /* +0x68, mode 0 */
    fx32 sphereRadius;      /* +0x74 */
    Segment capsuleAxis;    /* +0x78, mode 1 */
    fx32 capsuleRadius;     /* +0x94 */
} HitShape;

extern fx32 func_02036304(VecFx32 *point, Segment *seg, fx64 *outDist);
extern fx32 FX_Sqrt(fx32 x);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx32 func_02036494(Segment *a, Segment *b, fx64 *outDistA, fx64 *outDistB);
extern int func_02039700(Segment *seg, void *b, fx32 *outDist, int c, int d, int e);
extern void func_01ffa724(fx32 factor, VecFx32 *src, VecFx32 *dst);

int func_ov107_020c36bc(HitShape *self, Segment *seg, VecFx32 *out)
{
    switch (self->mode) {
    case 0: {
        fx64 t;
        if (FX_Sqrt(func_02036304(&self->sphereCenter, seg, &t)) <= self->sphereRadius) {
            if (out != 0) {
                fx64 along = t;
                out->x = (fx32)((along * seg->dir.x + 0x80000000LL) >> 32);
                out->y = (fx32)((along * seg->dir.y + 0x80000000LL) >> 32);
                out->z = (fx32)((along * seg->dir.z + 0x80000000LL) >> 32);
                VEC_Add(&seg->p0, out, out);
            }
            return 1;
        }
        break;
    }
    case 1: {
        fx64 tSelf;
        fx64 t;
        if (FX_Sqrt(func_02036494(&self->capsuleAxis, seg, &tSelf, &t)) <= self->capsuleRadius) {
            if (out != 0) {
                fx64 along = t;
                out->x = (fx32)((along * seg->dir.x + 0x80000000LL) >> 32);
                out->y = (fx32)((along * seg->dir.y + 0x80000000LL) >> 32);
                out->z = (fx32)((along * seg->dir.z + 0x80000000LL) >> 32);
                VEC_Add(&seg->p0, out, out);
            }
            return 1;
        }
        break;
    }
    case 2: {
        fx32 t;
        if (func_02039700(seg, &self->capsuleRadius, &t, 0, 0, 0) <= 8) {
            if (out != 0) {
                func_01ffa724(t, &seg->dir, out);
                VEC_Add(&seg->p0, out, out);
            }
            return 1;
        }
        break;
    }
    }
    return 0;
}
