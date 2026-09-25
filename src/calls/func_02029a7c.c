/* func_02029a7c = RoomBox_HitSides -- hit test of a moving sphere against the side faces of a room box, MAIN. The
 * segment (p0 +0x10 -> p1 +0x54) must overlap the box's height range. Both ends are taken into the
 * box's frame (quarter turns are done with swaps and negations, other angles with MTX_Rot22) and
 * given an outcode against the box's XZ footprint grown by the sphere radius (+0x74): 4/8 = beyond
 * -X/+X, 1/2 = beyond -Z/+Z (the start end counts the boundary as outside). A start inside the
 * footprint is an immediate hit at ratio 0 (side -1) unless the end is outside; otherwise the
 * crossing ratio of each face the start is beyond is divided out and the latest crossing wins,
 * recording the face (0 -Z, 1 +Z, 2 -X, 3 +X) at +0x80. The hit only counts when it is closer
 * than the best hit so far (+0x78); returns the ratio, or -1.0. */
typedef int fx32;
typedef long long s64;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _10, _11; } MtxFx22;
typedef struct { fx32 x, z; } XZ;

#define FX32_ONE 0x1000

typedef struct RoomBox {
    char pad00[0xc];
    XZ min;                             /* +0x0c */
    XZ max;                             /* +0x14 */
    char pad1c[0x2c - 0x1c];
    VecFx32 pos;                        /* +0x2c */
    fx32 width;                         /* +0x38 */
    fx32 height;                        /* +0x3c */
    fx32 depth;                         /* +0x40 */
    int angle;                          /* +0x44 */
} RoomBox;

typedef struct RoomSegment {
    char pad00[0x10];
    VecFx32 p0;                         /* +0x10 */
    VecFx32 delta;                      /* +0x1c */
    char pad28[0x54 - 0x28];
    VecFx32 p1;                         /* +0x54 */
    char pad60[0x74 - 0x60];
    fx32 radius;                        /* +0x74 */
    fx32 best;                          /* +0x78 */
    int pad7c;
    int side;                           /* +0x80 */
} RoomSegment;

extern const short data_0203d210[];     /* FX_SinCosTable_ */
extern s64 func_01ff8a14(fx32 numer, fx32 denom);
extern void MTX_Rot22_(MtxFx22 *m, fx32 sinVal, fx32 cosVal);

#define CROSS_RATIO(n, d) ((fx32)(func_01ff8a14(n, d) >> 5))

fx32 func_02029a7c(const RoomBox *box, RoomSegment *seg)
{
    fx32 ratio;
    MtxFx22 rot;
    fx32 x0, z0, x1, z1;
    unsigned short code0, code1;
    fx32 minX, maxX, minZ, maxZ;
    fx32 bottom, top, y0, y1;
    fx32 t;
    int side;

    bottom = box->pos.y;
    y0 = seg->p0.y;
    y1 = seg->p1.y;
    if (bottom > y0 && bottom > y1) {
        return -FX32_ONE;
    }
    top = bottom + box->height;
    if (top < y0 && top < y1) {
        return -FX32_ONE;
    }
    x0 = seg->p0.x - box->pos.x;
    z0 = seg->p0.z - box->pos.z;
    x1 = seg->p1.x - box->pos.x;
    z1 = seg->p1.z - box->pos.z;
    switch (box->angle) {
    case 0:
        break;
    case 0x4000:
        t = x0;
        x0 = -z0;
        z0 = t;
        t = x1;
        x1 = -z1;
        z1 = t;
        break;
    case 0x8000:
        x0 = -x0;
        z0 = -z0;
        x1 = -x1;
        z1 = -z1;
        break;
    case 0xc000:
        t = x0;
        x0 = z0;
        z0 = -t;
        t = x1;
        x1 = z1;
        z1 = -t;
        break;
    default: {
        int idx = box->angle >> 4;
        s64 tz0;
        s64 tx1;
        s64 m10;     /* rot._10 and rot._11 are each used twice: read once, in this order */
        fx32 m11;

        MTX_Rot22_(&rot, -data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        m11 = rot._11;
        m10 = rot._10;
        tz0 = z0;
        z0 = (fx32)(((s64)x0 * rot._01 + (s64)z0 * m11) >> 12);
        x0 = (fx32)(((s64)x0 * rot._00 + tz0 * m10) >> 12);
        tx1 = x1;
        x1 = (fx32)(((s64)x1 * rot._00 + (s64)z1 * m10) >> 12);
        z1 = (fx32)((tx1 * rot._01 + (s64)z1 * m11) >> 12);
        break;
    }
    }

    minX = -box->width / 2 - seg->radius;
    maxX = seg->radius + box->width / 2;
    minZ = -box->depth / 2 - seg->radius;
    maxZ = seg->radius + box->depth / 2;

    if (x0 <= minX) {
        code0 = 4;
    } else if (x0 >= maxX) {
        code0 = 8;
    } else {
        code0 = 0;
    }
    if (z0 <= minZ) {
        code0 |= 1;
    } else if (z0 >= maxZ) {
        code0 |= 2;
    }
    if (x1 < minX) {
        code1 = 4;
    } else if (x1 > maxX) {
        code1 = 8;
    } else {
        code1 = 0;
    }
    if (z1 < minZ) {
        code1 |= 1;
    } else if (z1 > maxZ) {
        code1 |= 2;
    }
    if (code0 & code1) {
        return -FX32_ONE;
    }
    if (code0 == 0) {
        if (code1 != 0) {
            return -FX32_ONE;
        }
        seg->side = -1;
        return seg->best = 0;
    }
    switch (code0) {
    case 1:
        ratio = CROSS_RATIO(minZ - z0, z1 - z0);
        side = 0;
        break;
    case 2:
        ratio = CROSS_RATIO(maxZ - z0, z1 - z0);
        side = 1;
        break;
    case 4:
        ratio = CROSS_RATIO(minX - x0, x1 - x0);
        side = 2;
        break;
    case 8:
        ratio = CROSS_RATIO(maxX - x0, x1 - x0);
        side = 3;
        break;
    case 5:
        ratio = CROSS_RATIO(minZ - z0, z1 - z0);
        t = CROSS_RATIO(minX - x0, x1 - x0);
        if (t > ratio) {
            side = 2;
            ratio = t;
        } else {
            side = 0;
        }
        break;
    case 9:
        ratio = CROSS_RATIO(minZ - z0, z1 - z0);
        t = CROSS_RATIO(maxX - x0, x1 - x0);
        if (t > ratio) {
            side = 3;
            ratio = t;
        } else {
            side = 0;
        }
        break;
    case 6:
        ratio = CROSS_RATIO(maxZ - z0, z1 - z0);
        t = CROSS_RATIO(minX - x0, x1 - x0);
        if (t > ratio) {
            side = 2;
            ratio = t;
        } else {
            side = 1;
        }
        break;
    case 10:
        ratio = CROSS_RATIO(maxZ - z0, z1 - z0);
        t = CROSS_RATIO(maxX - x0, x1 - x0);
        if (t > ratio) {
            side = 3;
            ratio = t;
        } else {
            side = 1;
        }
        break;
    }
    if (ratio < 0) {
        ratio = 0;
    }
    if (seg->best <= ratio) {
        return -FX32_ONE;
    }
    seg->side = side;
    seg->best = ratio;
    return ratio;
}
