typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct SphereFx32 {
    VecFx32 center;
    int radius;
} SphereFx32;

typedef struct CollisionHit {
    void *model;
    void *face;
    int unknown08;
    int distance;
} CollisionHit;

typedef struct Ov172CarryScene {
    unsigned char pad00[0x7c];
    void *pCollisionContext;
} Ov172CarryScene;

extern int func_ov107_020ca414(void *collision, SphereFx32 *sphere,
                               VecFx32 *contacts, VecFx32 *direction);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b,
                         VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern void func_01ffa724(int factor, const VecFx32 *source,
                          VecFx32 *destination);
extern long long func_01ff8a14(int numerator, int denominator);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern CollisionHit *func_01fff888(void *collision, VecFx32 *origin,
                                   VecFx32 *direction, void *filter);
extern void func_01ffd144(int factor, int *source, int *destination);

static inline int scale_by_ratio(long long ratio, int value)
{
    return (int)(((ratio * (long long)value) + 0x80000000LL) >> 32);
}

static inline void ScaleRatioVector(long long ratio,
                                    const VecFx32 *source,
                                    VecFx32 *destination)
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

void func_ov172_020d200c(Ov172CarryScene *pScene, VecFx32 *pPosition,
                         SphereFx32 *pBounds)
{
    SphereFx32 sphere;
    VecFx32 contacts[4];
    VecFx32 direction;
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
    CollisionHit *hit;

    VEC_Set(&direction, 0, 0, 0);
    sphere.center = *pPosition;
    sphere.radius = pBounds->radius;
    count = func_ov107_020ca414(pScene->pCollisionContext, &sphere,
                                 contacts, &direction);
    if (count > 0) {
        total = 0;
        VEC_Set(&sum, 0, 0, 0);
        for (i = 0; i < count; i++) {
            VEC_Subtract(&sphere.center, &contacts[i], &difference);
            value = func_01ff8d18(&difference, &normalized[i]);
            distance[i] = sphere.radius - value;
            func_01ffa724(distance[i], &normalized[i], &normalized[i]);
            total += distance[i];
        }
        for (i = 0; i < count; i++) {
            ratio[i] = func_01ff8a14(distance[i], total);
        }
        {
            const VecFx32 *normal;
            int weightIndex = 0;

            if (count > 0) {
                normal = normalized;
                do {
                    ScaleRatioVector(ratio[weightIndex], normal, &weighted);
                    VEC_Add(&sum, &weighted, &sum);
                    normal++;
                    weightIndex++;
                } while (weightIndex < count);
            }
        }
        VEC_Add(pPosition, &sum, pPosition);
    }

    sphere.center = *pPosition;
    sphere.center.y += sphere.radius;
    direction.y = -sphere.radius * 2;
    direction.x = 0;
    direction.z = 0;
    hit = func_01fff888(pScene->pCollisionContext, &sphere.center,
                        &direction, 0);
    if (hit == 0) {
        return;
    }
    func_01ffd144(hit->distance, &direction.x, &direction.x);
    VEC_Add(&sphere.center, &direction, pPosition);
}

