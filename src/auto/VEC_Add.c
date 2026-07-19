typedef struct { int x, y, z; } VecFx32;

void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst) {
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
    dst->z = a->z + b->z;
}
