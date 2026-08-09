typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b)
{
    long long sum = (long long)a->x * b->x
                  + (long long)a->y * b->y
                  + (long long)a->z * b->z;

    return (fx32)((sum + 0x800) >> 12);
}
