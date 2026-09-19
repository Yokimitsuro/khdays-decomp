/* Draw handler of the ov274 enemy: unhooks the +0x3b4 clip and, in owner mode 1 without bit 2
 * of the +0x60 flags, pushes the actor away from the entities inside a 0x2b80 sphere around
 * the +0x3dc bone's +0x14 point lifted 0x1d00: each hit weighs by the sphere radius less its
 * distance, the unit directions scaled by those weights are summed by their share of the total
 * (64-bit ratios), and the +0xa0 pose is placed at the +0xb0 point plus that sum (c4ecc
 * afterwards). The base draw handler always runs. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { VecFx32 pos; int nRadius; } Sphere;

extern void func_ov107_020c9ec8(int clip);
extern int func_ov107_020ca414(void *collision, Sphere *sphere, VecFx32 *list, VecFx32 *direction);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *out);
extern void func_01ffa724(int factor, const VecFx32 *source, VecFx32 *destination);
extern long long func_01ff8a14(int numerator, int denominator);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0203ca30(void *transform, const VecFx32 *v);
extern void func_ov107_020c4ecc(int self);
extern void func_ov107_020c6980(int self, int slot);

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

void func_ov275_020d1ef8(int self, int slot)
{
    VecFx32 list[4];
    VecFx32 direction;
    Sphere sphere;
    VecFx32 sum;
    VecFx32 normalized[4];
    VecFx32 out;
    int distance[4];
    long long ratio[4];
    VecFx32 difference;
    VecFx32 weighted;
    int count;
    int i;
    int total;
    int value;
    struct { char pad[0x7c]; void *collision; } *collisionOwner;

    func_ov107_020c9ec8(*(int *)(self + 0x3b4));
    if (*(int *)(self + 0x50) == 1 && ((unsigned int)(*(unsigned short *)(self + 0x60) << 24) >> 24 & 4) == 0) {
        VEC_Set(&direction, 0, 0, 0);
        collisionOwner = *(void **)(self + 4);
        sphere.pos = *(VecFx32 *)(*(int *)(self + 0x3dc) + 0x14);
        sphere.nRadius = 0x2b80;
        sphere.pos.y += 0x1d00;
        count = func_ov107_020ca414(collisionOwner->collision, &sphere, list, &direction);
        if (count > 0) {
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
            VEC_Add((VecFx32 *)(self + 0xb0), &sum, &out);
            func_0203ca30((void *)(self + 0xa0), &out);
            func_ov107_020c4ecc(self);
        }
    }
    func_ov107_020c6980(self, slot);
}
