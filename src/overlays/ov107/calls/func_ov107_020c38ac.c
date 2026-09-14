typedef int fx32;
typedef long long fx64;
typedef unsigned char u8;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct SegmentQuery {
    VecFx32 start;
    VecFx32 dir;
    fx32 length;
    fx32 radius;
} SegmentQuery;

typedef struct Segment {
    VecFx32 p0;
    VecFx32 dir;
    fx32 scale;
} Segment;

typedef struct HitShape {
    u8 mode : 4;
    char pad001[0x68 - 1];
    VecFx32 sphereCenter;
    fx32 sphereRadius;
    Segment capsuleAxis;
    union {
        fx32 capsuleRadius;
        u8 boxData[0x100];
    } shape;
} HitShape;

extern fx32 func_02036304(VecFx32 *point, Segment *seg, fx64 *outDist);
extern fx32 FX_Sqrt(fx32 x);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx32 func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern void func_01ffa724(fx32 factor, VecFx32 *src, VecFx32 *dst);
extern fx32 func_02036494(Segment *a, Segment *b, fx64 *outDistA, fx64 *outDistB);
extern fx32 func_02039700(Segment *seg, void *box, fx32 *outDist,
                          fx32 *outX, fx32 *outY, fx32 *outZ);

int func_ov107_020c38ac(HitShape *self, SegmentQuery *query, VecFx32 *out)
{
    switch (self->mode) {
    case 0: {
        fx64 along;
        fx32 distance;

        distance = FX_Sqrt(func_02036304(&self->sphereCenter,
                                         (Segment *)query, &along));
        if (distance <= self->sphereRadius + query->radius) {
            if (out != 0) {
                VecFx32 point;
                VecFx32 delta;
                fx32 separation;
                fx32 offset;

                point.x = (fx32)((along * query->dir.x + 0x80000000LL) >> 32);
                point.y = (fx32)((along * query->dir.y + 0x80000000LL) >> 32);
                point.z = (fx32)((along * query->dir.z + 0x80000000LL) >> 32);
                VEC_Add(&query->start, &point, &point);
                VEC_Subtract(&self->sphereCenter, &point, &delta);
                separation = func_01ff8d18(&delta, &delta);
                offset = (separation - self->sphereRadius)
                       + ((self->sphereRadius + query->radius - distance) >> 1);
                func_01ffa724(offset, &delta, &delta);
                VEC_Add(&point, &delta, out);
            }
            return 1;
        }
        break;
    }
    case 1: {
        fx64 selfAlong;
        fx64 queryAlong;
        fx32 distance;

        distance = func_02036494(&self->capsuleAxis,
                                 (Segment *)query,
                                 &selfAlong, &queryAlong);
        if (distance <= (fx32)(((fx64)self->shape.capsuleRadius
                                * self->shape.capsuleRadius + 0x800) >> 12)
                     + (fx32)(((fx64)query->radius * query->radius + 0x800) >> 12)) {
            if (out != 0) {
                VecFx32 selfPoint;
                VecFx32 queryPoint;
                VecFx32 delta;
                fx32 separation;
                fx32 offset;

                selfPoint.x = (fx32)((selfAlong * self->capsuleAxis.dir.x
                                      + 0x80000000LL) >> 32);
                selfPoint.y = (fx32)((selfAlong * self->capsuleAxis.dir.y
                                      + 0x80000000LL) >> 32);
                selfPoint.z = (fx32)((selfAlong * self->capsuleAxis.dir.z
                                      + 0x80000000LL) >> 32);
                VEC_Add(&self->capsuleAxis.p0, &selfPoint, &selfPoint);

                queryPoint.x = (fx32)((queryAlong * query->dir.x
                                       + 0x80000000LL) >> 32);
                queryPoint.y = (fx32)((queryAlong * query->dir.y
                                       + 0x80000000LL) >> 32);
                queryPoint.z = (fx32)((queryAlong * query->dir.z
                                       + 0x80000000LL) >> 32);
                VEC_Add(&query->start, &queryPoint, &queryPoint);

                VEC_Subtract(&queryPoint, &selfPoint, &delta);
                separation = func_01ff8d18(&delta, &delta);
                offset = (separation - self->shape.capsuleRadius)
                       + ((self->shape.capsuleRadius + query->radius
                           - FX_Sqrt(distance)) >> 1);
                func_01ffa724(offset, &delta, &delta);
                VEC_Add(&selfPoint, &delta, out);
            }
            return 1;
        }
        break;
    }
    case 2: {
        fx32 along;
        fx32 boxX;
        fx32 boxY;
        fx32 boxZ;
        fx32 distance;

        distance = FX_Sqrt(func_02039700((Segment *)query, self->shape.boxData,
                                         &along, &boxX, &boxY, &boxZ));
        if (distance <= query->radius) {
            if (out != 0) {
                VecFx32 boxPoint;
                VecFx32 point;
                VecFx32 delta;
                fx32 separation;
                fx32 offset;

                boxPoint.x = boxX;
                boxPoint.y = boxY;
                boxPoint.z = boxZ;
                func_01ffa724(along, &query->dir, &point);
                VEC_Add(&query->start, &point, &point);
                VEC_Subtract(&point, &boxPoint, &delta);
                separation = func_01ff8d18(&delta, &delta);
                offset = (separation - query->radius)
                       + ((query->radius - distance) >> 1);
                func_01ffa724(offset, &delta, &delta);
                VEC_Add(&point, &delta, out);
            }
            return 1;
        }
        break;
    }
    }
    return 0;
}
