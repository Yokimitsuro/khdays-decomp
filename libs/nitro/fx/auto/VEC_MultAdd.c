typedef struct { int x, y, z; } VecFx32;

void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst) {
    dst->x = add->x + (int)(((long long)scale * v->x) >> 12);
    dst->y = add->y + (int)(((long long)scale * v->y) >> 12);
    dst->z = add->z + (int)(((long long)scale * v->z) >> 12);
}
