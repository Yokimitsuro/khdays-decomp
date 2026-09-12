typedef struct Quat_0202ef54 {
    int w;
    int x;
    int y;
    int z;
} Quat_0202ef54;

static inline int FX32_CAST_0202ef54(long long result)
{
    return (int)result;
}

static inline int FX_MulInline_0202ef54(int v1, int v2)
{
    return FX32_CAST_0202ef54(((long long)v1 * v2 + 0x800LL) >> 12);
}

/* Hamilton product of two fixed-point quaternions: *out = (*a) * (*b).
 * Callers pass the same pointer for out and a (in-place concat), so the
 * four components are built up in locals before being written to *out. */
void func_0202ef54(Quat_0202ef54 *out, const Quat_0202ef54 *a, const Quat_0202ef54 *b)
{
    Quat_0202ef54 result;

    result.w = FX_MulInline_0202ef54(a->w, b->w) - FX_MulInline_0202ef54(a->x, b->x)
        - FX_MulInline_0202ef54(a->y, b->y) - FX_MulInline_0202ef54(a->z, b->z);
    result.x = FX_MulInline_0202ef54(a->y, b->z)
        + (FX_MulInline_0202ef54(a->w, b->x) + FX_MulInline_0202ef54(a->x, b->w))
        - FX_MulInline_0202ef54(a->z, b->y);
    result.y = FX_MulInline_0202ef54(a->z, b->x)
        + (FX_MulInline_0202ef54(a->w, b->y) + FX_MulInline_0202ef54(a->y, b->w))
        - FX_MulInline_0202ef54(a->x, b->z);
    result.z = FX_MulInline_0202ef54(a->x, b->y)
        + (FX_MulInline_0202ef54(a->w, b->z) + FX_MulInline_0202ef54(a->z, b->w))
        - FX_MulInline_0202ef54(a->y, b->x);

    *out = result;
}
