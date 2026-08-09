typedef int fx32;
typedef long long s64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out)
{
    fx32 x;
    fx32 y;
    fx32 z;

    x = (fx32)(((s64)a->y * b->z - (s64)a->z * b->y + 0x800) >> 12);
    y = (fx32)(((s64)a->z * b->x - (s64)a->x * b->z + 0x800) >> 12);
    z = (fx32)(((s64)a->x * b->y - (s64)a->y * b->x + 0x800) >> 12);
    out->x = x;
    out->y = y;
    out->z = z;
}
