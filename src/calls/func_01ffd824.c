typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;

typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

typedef struct CollisionEdgePlane {
    s16 x;
    s16 pad02;
    s16 z;
    s16 pad06;
    s32 distance;
} CollisionEdgePlane;

typedef struct CollisionPlane {
    s16 x;
    s16 y;
    s16 z;
    s16 pad06;
    s32 distance;
} CollisionPlane;

typedef struct CollisionFace88 {
    s32 bound00;
    s32 bound04;
    s32 bound08;
    s32 bound0c;
    u16 flags10;
    u16 vertexCount12;
    CollisionPlane plane14;
    CollisionEdgePlane edges20[4];
    VecFx32 vertices50[4];
    u32 tail80[2];
} CollisionFace88;

typedef struct CollisionRayQuery {
    u32 flags00;
    void *faceArray04;
    u32 pad08[2];
    s32 x10;
    s32 y14;
    s32 z18;
    u32 pad1c[6];
    s32 bound34;
    s32 bound38;
    s32 bound3c;
    s32 bound40;
    u32 pad44[5];
    s32 endY58;
    u32 pad5c[4];
    s32 hitFraction6c;
    const CollisionPlane *cachedPlane70;
    u32 pad74;
    s32 bestFraction78;
} CollisionRayQuery;

typedef union CollisionObjectView {
    CollisionFace88 face;
    CollisionRayQuery query;
} CollisionObjectView;

extern u32 func_0201f844(const void *, const void *, int);
extern void FX_DivAsync(s32 numerator, s32 denominator);
extern s64 func_01ff8ab0(void);

#define CollisionEdgePlane_Evaluate(edge, px, pz) \
    ((s32)(((s64)(px) * (edge)->x + (s64)(pz) * (edge)->z + 0x800) >> 12))

#define face (&faceObject->face)
#define query (&queryObject->query)

int func_01ffd824(CollisionObjectView *faceObject,
                  CollisionObjectView *queryObject)
{
    s64 horizontalDot;
    s32 endPlaneValue;
    u32 edgeValue;
    s32 startPlaneValue;
    const CollisionPlane *plane;
    volatile u16 *regDivCnt = (volatile u16 *)0x04000280;

    if (query->bound3c < face->bound00 ||
        query->bound40 < face->bound04) {
        goto bounds_reject;
    }
    if (query->bound34 <= face->bound08 &&
        query->bound38 <= face->bound0c) {
        goto bounds_accept;
    }

bounds_reject:
    return -0x1000;

bounds_accept:

    if (query->cachedPlane70 == 0) {
        goto recompute_plane;
    }
    if (func_0201f844(query->cachedPlane70, &face->plane14, 0xc) == 0) {
        goto cached_plane;
    }

recompute_plane:
    {
        s32 endOffset;
        s32 scaledBest;
        s32 distance;

        plane = &face->plane14;
        query->cachedPlane70 = plane;

        if ((face->flags10 & 2) != 0) {
            startPlaneValue = query->y14;
            endPlaneValue = query->endY58;
        } else {
            horizontalDot =
                (s64)plane->x * query->x10 +
                (s64)plane->z * query->z18;
            startPlaneValue =
                (s32)((horizontalDot +
                       (s64)plane->y * query->y14 + 0x800) >> 12);
            endPlaneValue =
                (s32)((horizontalDot +
                       (s64)plane->y * query->endY58 + 0x800) >> 12);
        }

        if (startPlaneValue <= endPlaneValue) {
            goto no_hit;
        }

        {
            distance = face->plane14.distance;
            endOffset = -0x80;
            if (startPlaneValue - distance < endOffset) {
                goto no_hit;
            }
            endOffset = endPlaneValue - distance;
            if (endOffset > 0x80) {
                goto no_hit;
            }
            endPlaneValue = startPlaneValue - endPlaneValue;
            startPlaneValue = startPlaneValue - distance;
            FX_DivAsync(startPlaneValue, endPlaneValue);

            scaledBest =
                (s32)(((s64)query->bestFraction78 * endPlaneValue) >> 27);
            if (startPlaneValue < scaledBest) {
                goto closer_hit;
            }

            while ((*regDivCnt & 0x8000) != 0) {
            }
            goto no_hit;

closer_hit:
            if (startPlaneValue < 0) {
                query->hitFraction6c = 0;
                while ((*regDivCnt & 0x8000) != 0) {
                }
            } else if (startPlaneValue > endPlaneValue) {
                query->hitFraction6c = 0x08000000;
                while ((*regDivCnt & 0x8000) != 0) {
                }
            } else {
                query->hitFraction6c = (s32)(func_01ff8ab0() >> 5);
            }
            goto test_edges;
        }
    }

cached_plane:
    {
        if (query->hitFraction6c < 0) {
            return -0x1000;
        }
        if (query->hitFraction6c >= query->bestFraction78) {
            goto no_hit;
        }
    }

test_edges:
    edgeValue = CollisionEdgePlane_Evaluate(&face->edges20[0],
                                            query->x10, query->z18);
    if ((s32)edgeValue < face->edges20[0].distance - 0x80) {
        return -0x1000;
    }
    edgeValue = CollisionEdgePlane_Evaluate(&face->edges20[1],
                                            query->x10, query->z18);
    if ((s32)edgeValue < face->edges20[1].distance - 0x80) {
        return -0x1000;
    }
    edgeValue = CollisionEdgePlane_Evaluate(&face->edges20[2],
                                            query->x10, query->z18);
    if ((s32)edgeValue < face->edges20[2].distance - 0x80) {
        return -0x1000;
    }
    if (face->vertexCount12 == 4) {
        edgeValue = CollisionEdgePlane_Evaluate(&face->edges20[3],
                                                query->x10, query->z18);
        if ((s32)edgeValue < face->edges20[3].distance - 0x80) {
            return -0x1000;
        }
    }

    return query->bestFraction78 = query->hitFraction6c;

no_hit:
    query->hitFraction6c = -0x1000;
    return -0x1000;
}

#undef query
#undef face
