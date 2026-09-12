/*
 * func_02036304 -- closest point on a line segment to a query point.
 *
 * The segment runs from seg->p0 to seg->p0 + seg->dir * seg->scale (a Q12
 * fixed-point multiplier, func_01ffa724). The point-p0 vector is projected
 * onto the scaled direction and the projection is clamped to the segment
 * (dot <= 0 clamps to p0, dot >= |scaledDir|^2 clamps to the far end,
 * otherwise a 64-bit division, func_020201b8, gives the interior fraction).
 * If outDist is non-NULL it receives the signed distance travelled along
 * the axis as a Q32 64-bit fixed value. Returns the squared distance
 * (Q12) from the point to the resulting closest point.
 *
 * ARM.
 */

typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    VecFx32 p0;
    VecFx32 dir;
    fx32 scale;
} Segment;

extern void func_01ffa724(int factor, int *src, int *dst);
extern void VEC_Subtract(int *a, int *b, int *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx64 func_020201b8(fx64 numerator, fx64 denominator);

fx32 func_02036304(VecFx32 *point, Segment *seg, fx64 *outDist)
{
    VecFx32 diff;
    VecFx32 scaledDir;
    fx64 dot64;
    fx64 t;

    func_01ffa724(seg->scale, (int *)&seg->dir, (int *)&scaledDir);
    VEC_Subtract((int *)point, (int *)seg, (int *)&diff);

    dot64 = (fx64)VEC_DotProduct(&diff, &scaledDir) << 20;

    if (dot64 <= 0) {
        t = 0;
    } else if (dot64 >= (((fx64)seg->scale * seg->scale) << 8)) {
        t = (fx64)1 << 32;
        VEC_Subtract((int *)&diff, (int *)&scaledDir, (int *)&diff);
    } else {
        VecFx32 delta;

        t = func_020201b8(dot64, ((((fx64)seg->scale * seg->scale) << 8) >> 20)) << 12;
        delta.x = (fx32)(((t * scaledDir.x) + 0x80000000LL) >> 32);
        delta.y = (fx32)(((t * scaledDir.y) + 0x80000000LL) >> 32);
        delta.z = (fx32)(((t * scaledDir.z) + 0x80000000LL) >> 32);
        VEC_Subtract((int *)&diff, (int *)&delta, (int *)&diff);
    }

    if (outDist) {
        *outDist = ((t * seg->scale) + 0x80000000LL) >> 12;
    }

    return (fx32)(((fx64)diff.x * diff.x + (fx64)diff.y * diff.y + (fx64)diff.z * diff.z + 0x800) >> 12);
}
