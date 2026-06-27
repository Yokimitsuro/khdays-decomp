typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

void func_01ffd0e8(fx32 s, const VecFx32 *a, const VecFx32 *b, VecFx32 *c)
{
    c->x = b->x + (fx32)(((fx64)s * a->x) >> 27);
    c->y = b->y + (fx32)(((fx64)s * a->y) >> 27);
    c->z = b->z + (fx32)(((fx64)s * a->z) >> 27);
}
