/* Cached Q27 segment intersection with a triangle or quad face. */
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef s32 fx32;
typedef struct VecFx16 { s16 x, y, z; } VecFx16;
typedef struct VecFx32 { fx32 x, y, z; } VecFx32;
typedef struct CollisionPlane {
    VecFx16 normal;
    u16 padding06;
    fx32 distance;
} CollisionPlane;
typedef struct CollisionFace88 {
    u8 pad00[16];
    u16 flags10, vertexCount12;
    CollisionPlane plane;
    CollisionPlane edges[4];
    u8 pad50[56];
} CollisionFace88;
typedef struct CollCastState {
    u8 pad00[16];
    VecFx32 vRayStart;
    VecFx32 vDir;
    u8 pad28[44];
    VecFx32 vRayEnd;
    VecFx32 vCandidateHit;
    s32 nCandidateT;
    const CollisionPlane *pCachedPlane;
    s32 nRadius;
    s32 nNearestHit;
} CollCastState;
extern s32 func_0201f844(const void *left, const void *right, s32 count);
extern void FX_DivAsync(s32 numerator, s32 denominator);
extern s64 func_01ff8ab0(void);
extern void func_01ffd0e8(s32 factor, const VecFx32 *direction,
                         const VecFx32 *origin, VecFx32 *result);

#pragma inline_max_size(1300)
static inline fx32 PlaneDot(const VecFx16 *normal, const VecFx32 *point)
{
    return (fx32)(((s64)point->x * normal->x +
                   (s64)point->y * normal->y +
                   (s64)point->z * normal->z + 0x800) >> 12);
}
static inline void WaitDivider(void)
{
    while (*(volatile u16 *)0x04000280 & 0x8000) {
    }
}

s32 func_01ffd184(const CollisionFace88 *face, CollCastState *query)
{
    s32 startDot, endDot;
    s32 denominator, t;
    if (!query->pCachedPlane ||
        func_0201f844(query->pCachedPlane, &face->plane, sizeof(CollisionPlane))) {
        const VecFx16 *normal = &face->plane.normal;
        query->pCachedPlane = &face->plane;
        if (face->flags10 & 2) {
            startDot = query->vRayStart.y;
            endDot = query->vRayEnd.y;
        } else {
            startDot = PlaneDot(normal, &query->vRayStart);
            endDot = PlaneDot(normal, &query->vRayEnd);
        }
        if (startDot <= endDot) goto reject;
        if (startDot - face->plane.distance < -128) goto reject;
        if (endDot - face->plane.distance > 128) goto reject;
        denominator = startDot - endDot;
        /* Preserve the original projection until the denominator is formed.
         * From this point startDot is the signed distance to the face plane. */
        FX_DivAsync(startDot -= face->plane.distance, denominator);
        if (startDot >= (s32)(((s64)query->nNearestHit * denominator) >> 27)) {
            WaitDivider();
            goto reject;
        }
        if (startDot < 0) {
            query->vCandidateHit = query->vRayStart;
            t = 0;
            WaitDivider();
        } else if (startDot >= denominator) {
            query->vCandidateHit = query->vRayEnd;
            t = 1 << 27;
            WaitDivider();
        } else {
            t = (s32)(func_01ff8ab0() >> 5);
            func_01ffd0e8(t, &query->vDir, &query->vRayStart, &query->vCandidateHit);
        }
        query->nCandidateT = t;
    } else {
        if (query->nCandidateT < 0) return -4096;
        if (query->nCandidateT >= query->nNearestHit) goto reject;
    }
    {
        /* Retain wide coordinates across the repeated edge-plane products. */
        s64 z = query->vCandidateHit.z;
        s64 x = query->vCandidateHit.x;
#define EDGE_TEST(n) \
        if ((s32)((x * face->edges[n].normal.x + z * face->edges[n].normal.z + 0x800) >> 12) < face->edges[n].distance - 128) return -4096
        EDGE_TEST(0);
        EDGE_TEST(1);
        EDGE_TEST(2);
        if (face->vertexCount12 == 4) { EDGE_TEST(3); }
#undef EDGE_TEST
    }
    return query->nNearestHit = query->nCandidateT;
reject:
    query->nCandidateT = -4096;
    return -4096;
}
