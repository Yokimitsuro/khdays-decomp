/* Pushes a point out of the collision world (x3 with ov272/ov279): a sphere of the given radius
 * at the point is tested against the world's (+0x7c) collision; every contact weighs by the
 * radius less its distance, the unit directions away from the contacts scaled by those weights
 * are summed by their share of the total (64-bit ratios) and the point is moved by that sum. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { VecFx32 pos; int nRadius; } Sphere;

extern int func_ov107_020ca414(void *collision, Sphere *sphere, VecFx32 *list, VecFx32 *direction);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *out);
extern void func_01ffa724(int factor, const VecFx32 *source, VecFx32 *destination);
extern long long func_01ff8a14(int numerator, int denominator);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline int scale_by_ratio(long long ratio, int value)
{
    return (int)(((ratio * (long long)value) + 0x80000000LL) >> 32);
}

static inline void ScaleRatioVector(long long ratio, const VecFx32 *source, VecFx32 *destination)
{
    destination->x = scale_by_ratio(ratio, source->x);
    destination->y = scale_by_ratio(ratio, source->y);
    destination->z = scale_by_ratio(ratio, source->z);
}

static inline void VEC_Set(VecFx32 *vec, int x, int y, int z)
{
    int *components = (int *)vec;
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

void func_ov119_020ccc48(char *owner, VecFx32 *point, int unused, int radius)
{
    Sphere sphere;
    VecFx32 direction;
    VecFx32 list[4];
    VecFx32 sum;
    VecFx32 normalized[4];
    int distance[4];
    long long ratio[4];
    VecFx32 difference;
    VecFx32 weighted;
    int count;
    int total;
    int i;
    int value;

    VEC_Set(&direction, 0, 0, 0);
    sphere.pos = *point;
    sphere.nRadius = radius;
    count = func_ov107_020ca414(*(void **)(owner + 0x7c), &sphere, list, &direction);
    if (count <= 0) {
        return;
    }
    total = 0;
    VEC_Set(&sum, 0, 0, 0);
    for (i = 0; i < count; i++) {
        VEC_Subtract(&sphere.pos, &list[i], &difference);
        value = func_01ff8d18(&difference, &normalized[i]);
        distance[i] = sphere.nRadius - value;
        func_01ffa724(distance[i], &normalized[i], &normalized[i]);
        total += distance[i];
    }
    for (i = 0; i < count; i++) {
        ratio[i] = func_01ff8a14(distance[i], total);
    }
    for (i = 0; i < count; i++) {
        ScaleRatioVector(ratio[i], &normalized[i], &weighted);
        VEC_Add(&sum, &weighted, &sum);
    }
    VEC_Add(point, &sum, point);
}
