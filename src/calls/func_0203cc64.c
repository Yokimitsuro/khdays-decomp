typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_0202f384(VecFx32 *in_vec, void *unused, VecFx32 *out_vec);

typedef struct {
    char pad_00[0x10];
    VecFx32 offset;     /* 0x10 */
    int scale_x;        /* 0x1c */
    int scale_y;        /* 0x20 */
    int scale_z;        /* 0x24 */
    unsigned char flags : 1; /* 0x28 bit 0 */
} Obj;

void func_0203cc64(VecFx32 *out, Obj *obj, VecFx32 *in)
{
    VecFx32 tmp;
    int sx, sy, sz;

    if (obj->flags) {
        *out = *in;
        return;
    }

    sz = (int)(((long long)obj->scale_z * in->z + 0x800) >> 12);
    sy = (int)(((long long)obj->scale_y * in->y + 0x800) >> 12);
    sx = (int)(((long long)obj->scale_x * in->x + 0x800) >> 12);

    tmp.x = sx;
    tmp.y = sy;
    tmp.z = sz;

    func_0202f384(&tmp, obj, &tmp);
    VEC_Add(&tmp, &obj->offset, &tmp);

    *out = tmp;
}
