typedef struct { int x; int y; int z; } Vec3;

void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *out)
{
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}
