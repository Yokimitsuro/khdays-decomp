/* func_02029810 -- hit test of a falling segment against the top of a room box, MAIN. The segment
 * runs from p0 (+0x10) down to p1 (+0x54) with delta +0x1c; the box top is pos.y + height. When
 * the segment crosses the top (with 0x80 of slack) closer than the best hit so far (+0x78, a 1.27
 * ratio), the crossing ratio is divided out on the hardware divider and the crossing point is
 * interpolated (func_01ffd0e8), clamped to the segment ends. The point must lie inside the box's
 * XZ bounds and, for a box not turned by a multiple of 90 degrees, inside its rotated footprint.
 * Returns the new ratio (also stored as the best hit) or -1.0 when there is no better hit. */
typedef short s16;
typedef int fx32;
typedef long long s64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef volatile unsigned short vu16;
typedef u64 REGType64;           /* the SDK register type is not volatile */

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _10, _11; } MtxFx22;
typedef struct { fx32 x, z; } XZ;

#define REG_DIVCNT     (*(vu16 *)0x04000280)
#define REG_DIV_NUMER  (*(REGType64 *)0x04000290)
#define REG_DIV_DENOM  (*(REGType64 *)0x04000298)
#define FX32_ONE       0x1000

static inline void CP_SetDivImm64_64(u64 numer, u64 denom)
{
    REG_DIV_NUMER = numer;
    REG_DIV_DENOM = denom;
}

static inline void CP_WaitDiv(void)
{
    while (REG_DIVCNT & 0x8000) {
    }
}

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
    char pad60[0x78 - 0x60];
    fx32 best;                          /* +0x78 */
} RoomSegment;

extern const short data_0203d210[];     /* FX_SinCosTable_ */
extern s64 func_01ff8ab0(void);         /* CP_GetDivResult64 */
extern void func_01ffd0e8(fx32 t, const VecFx32 *delta, const VecFx32 *base, VecFx32 *out);
extern void MTX_Rot22_(MtxFx22 *m, fx32 sinVal, fx32 cosVal);

fx32 func_02029810(const RoomBox *box, RoomSegment *seg)
{
    VecFx32 p;
    MtxFx22 rot;
    fx32 y0 = seg->p0.y;
    fx32 y1 = seg->p1.y;
    fx32 top = box->pos.y + box->height;
    fx32 d0;
    fx32 dh;
    fx32 ratio;

    if (y0 <= y1) {
        return -FX32_ONE;
    }
    d0 = y0 - top;
    if (d0 < -0x80) {
        return -FX32_ONE;
    }
    if (y1 - top > 0x80) {
        return -FX32_ONE;
    }
    dh = y0 - y1;
    CP_SetDivImm64_64((u64)d0 << 32, (u32)dh);
    if (d0 >= (fx32)(((s64)seg->best * dh) >> 27)) {
        CP_WaitDiv();
        return -FX32_ONE;
    }
    if (d0 < 0) {
        p = seg->p0;
        ratio = 0;
        CP_WaitDiv();
    } else if (d0 >= dh) {
        p = seg->p1;
        ratio = 1 << 27;
        CP_WaitDiv();
    } else {
        ratio = (fx32)((u64)func_01ff8ab0() >> 5);
        func_01ffd0e8(ratio, &seg->delta, &seg->p0, &p);
    }
    if (p.x < box->min.x || p.x > box->max.x || p.z < box->min.z || p.z > box->max.z) {
        return -FX32_ONE;
    }
    if (box->angle & 0x3fff) {
        int idx = box->angle >> 4;
        fx32 hw = box->width / 2;
        fx32 hd = box->depth / 2;
        fx32 dx;
        fx32 dz;
        fx32 lx;
        fx32 lz;

        MTX_Rot22_(&rot, -data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        dx = p.x - box->pos.x;
        dz = p.z - box->pos.z;
        lx = (fx32)(((s64)dx * rot._00 + (s64)dz * rot._10) >> 12);
        lz = (fx32)(((s64)dx * rot._01 + (s64)dz * rot._11) >> 12);
        if (lx < -hw || lx > hw || lz < -hd || lz > hd) {
            return -FX32_ONE;
        }
    }
    seg->best = ratio;
    return ratio;
}
