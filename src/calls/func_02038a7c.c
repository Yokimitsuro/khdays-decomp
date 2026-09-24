/* func_02038a7c -- project a point onto a shape along its dominant axis, MAIN. The offset of `p`
 * from the shape's centre (+0x30) is compared against the normal `n` with fixed-point cross terms
 * to find which pair of axes to work in, and func_02037550 is called with that axis order (0/1/2,
 * 1/2/0 or 2/0/1) together with the point, the normal, the shape, the offset and the two extra
 * arguments. */
typedef int fx32;
typedef long long s64;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct Shape {
    char pad00[0x30];
    VecFx32 centre;                     /* +0x30 */
} Shape;

extern void func_02037550(int ax0, int ax1, int ax2, const VecFx32 *p, const VecFx32 *n, const Shape *shape,
                          VecFx32 *d, int a, int b);

#define FX64_MUL(a, b) ((fx32)(((a) * (b) + 0x800) >> 12))

void func_02038a7c(const VecFx32 *p, const VecFx32 *n, const Shape *shape, int a, int b)
{
    VecFx32 d;

    d.x = p->x - shape->centre.x;
    d.y = p->y - shape->centre.y;
    d.z = p->z - shape->centre.z;
    if (FX64_MUL((s64)n->y, (s64)d.x) >= FX64_MUL((s64)n->x, (s64)d.y)) {
        if (FX64_MUL((s64)n->z, (s64)d.x) >= FX64_MUL((s64)n->x, (s64)d.z)) {
            func_02037550(0, 1, 2, p, n, shape, &d, a, b);
        } else {
            func_02037550(2, 0, 1, p, n, shape, &d, a, b);
        }
    } else {
        if (FX64_MUL((s64)n->z, (s64)d.y) >= FX64_MUL((s64)n->y, (s64)d.z)) {
            func_02037550(1, 2, 0, p, n, shape, &d, a, b);
        } else {
            func_02037550(2, 0, 1, p, n, shape, &d, a, b);
        }
    }
}
