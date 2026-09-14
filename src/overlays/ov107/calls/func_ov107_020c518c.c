/* func_ov107_020c518c -- AiState callback (+0x4c slot, installed by
 * func_ov107_020c3c74): overlap test between two creatures' hit shapes.
 *
 * Walks every enabled hit shape of self against every enabled hit shape of
 * other (list at +0x144). Pairs whose bounding boxes overlap are tested by
 * shape kind (0 = sphere, 1 = capsule, 2 = oriented box). On the first pair
 * that intersects, the separation direction (normalised) and the overlap depth
 * are handed to func_ov107_020c4efc, which pushes the two creatures apart, and
 * the function returns 1. Returns 0 when nothing overlaps or neither creature
 * has a nonzero field_54 push weight.
 *
 * Where a reach (sum of two radii) is compared, `dist = reach - dist` turns
 * the distance into the overlap depth in place. A fresh `depth` local gets
 * forwarded into the call and keeps reach live across the vector calls; the
 * in-place redefinition is what puts the subtraction ahead of them, as in
 * ROM. */

typedef unsigned char u8;
typedef int fx32;
typedef long long fx64;

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

typedef struct Box {
    VecFx32 center;
    VecFx32 axis[3];
    fx32 halfExtent[3];
} Box;

typedef struct HitShape {
    u8 mode : 4;             /* 0 sphere, 1 capsule, 2 box */
    u8 flags : 4;            /* bit 0: shape takes part in the test */
    char pad001[0x3c - 1];
    VecFx32 boundsMin;       /* +0x3c */
    VecFx32 boundsMax;       /* +0x48 */
    char pad054[0x68 - 0x54];
    VecFx32 sphereCenter;    /* +0x68 */
    fx32 sphereRadius;       /* +0x74 */
    Segment capsuleAxis;     /* +0x78 */
    union {
        fx32 capsuleRadius;  /* +0x94, mode 1 */
        Box box;             /* +0x94, mode 2 */
    } shape;
} HitShape;

/* Partial AiState; pads are not claims about the object. */
typedef struct AiState {
    u8 pad000[0x54];
    int field_54;            /* push weight, see func_ov107_020c4efc */
    u8 pad058[0x144 - 0x58];
    u8 hitShapes[0x28];      /* list of HitShape *, walked by func_01fffd70/8c */
} AiState;

extern HitShape **func_01fffd70(void *list);
extern HitShape **func_01fffd8c(void *list);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx32 func_01ff8d18(VecFx32 *source, VecFx32 *destination);
extern fx32 FX_Sqrt(fx32 x);
extern void func_01ffa724(fx32 factor, VecFx32 *src, VecFx32 *dst);
extern fx32 func_02036304(VecFx32 *point, Segment *seg, fx64 *outDist);
extern fx32 func_02036494(Segment *a, Segment *b, fx64 *outDistA, fx64 *outDistB);
extern fx32 func_02037188(VecFx32 *point, Box *box, fx32 *outX, fx32 *outY, fx32 *outZ);
extern fx32 func_02039700(Segment *seg, Box *box, fx32 *outDist,
                          fx32 *outX, fx32 *outY, fx32 *outZ);
extern int func_02039ba0(Box *a, Box *b);
extern void func_ov107_020c4efc(fx32 depth, VecFx32 *dir, AiState *a, AiState *b);

int func_ov107_020c518c(AiState *self, AiState *other)
{
    HitShape **itemA;
    HitShape **itemB;
    HitShape *b;
    HitShape *a;

    if (self->field_54 == 0 && other->field_54 == 0) {
        return 0;
    }

    for (itemA = func_01fffd70(self->hitShapes); itemA != 0;
         itemA = func_01fffd8c(self->hitShapes)) {
        a = *itemA;
        if (!(a->flags & 1)) {
            continue;
        }
        switch (a->mode) {
        case 0:
            for (itemB = func_01fffd70(other->hitShapes); itemB != 0;
                 itemB = func_01fffd8c(other->hitShapes)) {
                b = *itemB;
                if (!(b->flags & 1)) continue;
                if (a->boundsMax.x < b->boundsMin.x) continue;
                if (a->boundsMin.x > b->boundsMax.x) continue;
                if (a->boundsMax.y < b->boundsMin.y) continue;
                if (a->boundsMin.y > b->boundsMax.y) continue;
                if (a->boundsMax.z < b->boundsMin.z) continue;
                if (a->boundsMin.z > b->boundsMax.z) continue;
                switch (b->mode) {
                case 0: {
                    VecFx32 delta;
                    fx32 dist;
                    fx32 reach;

                    VEC_Subtract(&a->sphereCenter, &b->sphereCenter, &delta);
                    dist = func_01ff8d18(&delta, &delta);
                    reach = a->sphereRadius + b->sphereRadius;
                    if (dist <= reach) {
                        func_ov107_020c4efc(reach - dist, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                case 1: {
                    fx64 along;
                    VecFx32 point;
                    VecFx32 delta;
                    fx32 dist;
                    fx32 reach;

                    dist = FX_Sqrt(func_02036304(&a->sphereCenter, &b->capsuleAxis, &along));
                    reach = a->sphereRadius + b->shape.capsuleRadius;
                    if (dist <= reach) {
                        dist = reach - dist;
                        point.x = (fx32)((along * b->capsuleAxis.dir.x + 0x80000000LL) >> 32);
                        point.y = (fx32)((along * b->capsuleAxis.dir.y + 0x80000000LL) >> 32);
                        point.z = (fx32)((along * b->capsuleAxis.dir.z + 0x80000000LL) >> 32);
                        VEC_Add(&b->capsuleAxis.p0, &point, &point);
                        VEC_Subtract(&a->sphereCenter, &point, &delta);
                        func_01ff8d18(&delta, &delta);
                        func_ov107_020c4efc(dist, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                case 2: {
                    fx32 x;
                    fx32 y;
                    fx32 z;
                    VecFx32 boxPoint;
                    VecFx32 delta;
                    fx32 dist;
                    fx32 depth;

                    dist = FX_Sqrt(func_02037188(&a->sphereCenter, &b->shape.box, &x, &y, &z));
                    depth = a->sphereRadius;
                    if (dist <= depth) {
                        depth -= dist;
                        boxPoint.x = x;
                        boxPoint.y = y;
                        boxPoint.z = z;
                        VEC_Subtract(&a->sphereCenter, &boxPoint, &delta);
                        func_01ff8d18(&delta, &delta);
                        func_ov107_020c4efc(depth, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                }
            }
            break;
        case 1:
            for (itemB = func_01fffd70(other->hitShapes); itemB != 0;
                 itemB = func_01fffd8c(other->hitShapes)) {
                b = *itemB;
                if (!(b->flags & 1)) continue;
                if (a->boundsMax.x < b->boundsMin.x) continue;
                if (a->boundsMin.x > b->boundsMax.x) continue;
                if (a->boundsMax.y < b->boundsMin.y) continue;
                if (a->boundsMin.y > b->boundsMax.y) continue;
                if (a->boundsMax.z < b->boundsMin.z) continue;
                if (a->boundsMin.z > b->boundsMax.z) continue;
                switch (b->mode) {
                case 0: {
                    fx64 along;
                    VecFx32 point;
                    VecFx32 delta;
                    fx32 dist;
                    fx32 reach;

                    dist = FX_Sqrt(func_02036304(&b->sphereCenter, &a->capsuleAxis, &along));
                    reach = a->shape.capsuleRadius + b->sphereRadius;
                    if (dist <= reach) {
                        dist = reach - dist;
                        point.x = (fx32)((along * a->capsuleAxis.dir.x + 0x80000000LL) >> 32);
                        point.y = (fx32)((along * a->capsuleAxis.dir.y + 0x80000000LL) >> 32);
                        point.z = (fx32)((along * a->capsuleAxis.dir.z + 0x80000000LL) >> 32);
                        VEC_Add(&a->capsuleAxis.p0, &point, &point);
                        VEC_Subtract(&point, &b->sphereCenter, &delta);
                        func_01ff8d18(&delta, &delta);
                        func_ov107_020c4efc(dist, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                case 1: {
                    fx64 alongA;
                    fx64 alongB;
                    VecFx32 delta;
                    VecFx32 pointA;
                    VecFx32 pointB;
                    fx32 dist;
                    fx32 reach;

                    dist = FX_Sqrt(func_02036494(&a->capsuleAxis, &b->capsuleAxis, &alongA, &alongB));
                    reach = a->shape.capsuleRadius + b->shape.capsuleRadius;
                    if (dist <= reach) {
                        dist = reach - dist;
                        pointA.x = (fx32)((alongA * a->capsuleAxis.dir.x + 0x80000000LL) >> 32);
                        pointA.y = (fx32)((alongA * a->capsuleAxis.dir.y + 0x80000000LL) >> 32);
                        pointA.z = (fx32)((alongA * a->capsuleAxis.dir.z + 0x80000000LL) >> 32);
                        VEC_Add(&a->capsuleAxis.p0, &pointA, &pointA);
                        pointB.x = (fx32)((alongB * b->capsuleAxis.dir.x + 0x80000000LL) >> 32);
                        pointB.y = (fx32)((alongB * b->capsuleAxis.dir.y + 0x80000000LL) >> 32);
                        pointB.z = (fx32)((alongB * b->capsuleAxis.dir.z + 0x80000000LL) >> 32);
                        VEC_Add(&b->capsuleAxis.p0, &pointB, &pointB);
                        VEC_Subtract(&pointA, &pointB, &delta);
                        func_01ff8d18(&delta, &delta);
                        func_ov107_020c4efc(dist, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                case 2: {
                    fx32 along;
                    fx32 x;
                    fx32 y;
                    fx32 z;
                    VecFx32 point;
                    VecFx32 boxPoint;
                    VecFx32 delta;
                    fx32 dist;
                    fx32 depth;

                    dist = FX_Sqrt(func_02039700(&a->capsuleAxis, &b->shape.box, &along, &x, &y, &z));
                    depth = a->shape.capsuleRadius;
                    if (dist <= depth) {
                        depth -= dist;
                        boxPoint.x = x;
                        boxPoint.y = y;
                        boxPoint.z = z;
                        func_01ffa724(along, &a->capsuleAxis.dir, &point);
                        VEC_Add(&a->capsuleAxis.p0, &point, &point);
                        VEC_Subtract(&boxPoint, &point, &delta);
                        func_01ff8d18(&delta, &delta);
                        func_ov107_020c4efc(depth, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                }
            }
            break;
        case 2:
            for (itemB = func_01fffd70(other->hitShapes); itemB != 0;
                 itemB = func_01fffd8c(other->hitShapes)) {
                b = *itemB;
                if (!(b->flags & 1)) continue;
                if (a->boundsMax.x < b->boundsMin.x) continue;
                if (a->boundsMin.x > b->boundsMax.x) continue;
                if (a->boundsMax.y < b->boundsMin.y) continue;
                if (a->boundsMin.y > b->boundsMax.y) continue;
                if (a->boundsMax.z < b->boundsMin.z) continue;
                if (a->boundsMin.z > b->boundsMax.z) continue;
                switch (b->mode) {
                case 0: {
                    fx32 x;
                    fx32 y;
                    fx32 z;
                    VecFx32 boxPoint;
                    VecFx32 delta;
                    fx32 dist;
                    fx32 depth;

                    dist = FX_Sqrt(func_02037188(&b->sphereCenter, &a->shape.box, &x, &y, &z));
                    depth = b->sphereRadius;
                    if (dist <= depth) {
                        depth -= dist;
                        boxPoint.x = x;
                        boxPoint.y = y;
                        boxPoint.z = z;
                        VEC_Subtract(&boxPoint, &b->sphereCenter, &delta);
                        func_01ff8d18(&delta, &delta);
                        func_ov107_020c4efc(depth, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                case 1: {
                    fx32 along;
                    fx32 x;
                    fx32 y;
                    fx32 z;
                    VecFx32 point;
                    VecFx32 boxPoint;
                    VecFx32 delta;
                    fx32 dist;
                    fx32 depth;

                    dist = FX_Sqrt(func_02039700(&b->capsuleAxis, &a->shape.box, &along, &x, &y, &z));
                    depth = b->shape.capsuleRadius;
                    if (dist <= depth) {
                        depth -= dist;
                        boxPoint.x = x;
                        boxPoint.y = y;
                        boxPoint.z = z;
                        func_01ffa724(along, &b->capsuleAxis.dir, &point);
                        VEC_Add(&b->capsuleAxis.p0, &point, &point);
                        VEC_Subtract(&boxPoint, &point, &delta);
                        func_01ff8d18(&delta, &delta);
                        func_ov107_020c4efc(depth, &delta, self, other);
                        return 1;
                    }
                    break;
                }
                case 2:
                    if (func_02039ba0(&a->shape.box, &b->shape.box)) {
                        fx32 x;
                        fx32 y;
                        fx32 z;
                        VecFx32 pointA;
                        VecFx32 pointB;
                        VecFx32 delta;

                        func_02037188(&b->shape.box.center, &a->shape.box, &x, &y, &z);
                        pointA.x = x;
                        pointA.y = y;
                        pointA.z = z;
                        func_02037188(&a->shape.box.center, &b->shape.box, &x, &y, &z);
                        pointB.x = x;
                        pointB.y = y;
                        pointB.z = z;
                        VEC_Subtract(&pointB, &pointA, &delta);
                        func_ov107_020c4efc(func_01ff8d18(&delta, &delta), &delta, self, other);
                        return 1;
                    }
                    break;
                }
            }
            break;
        }
    }
    return 0;
}
