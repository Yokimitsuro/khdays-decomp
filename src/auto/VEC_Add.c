struct Vec3 { int x; int y; int z; };

void VEC_Add(struct Vec3 *a, struct Vec3 *b, struct Vec3 *out)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}
