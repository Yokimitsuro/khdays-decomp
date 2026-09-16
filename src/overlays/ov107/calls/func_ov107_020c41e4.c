typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed long long s64;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct NodeTransform {
    int field_00[4];
    VecFx32 translation;
    int field_1c;
    int field_20;
    int field_24;
    u8 flags;
    u8 pad029[3];
} NodeTransform;

typedef struct Owner {
    u8 pad000[0x7c];
    void *field_7c;
} Owner;

typedef struct CallbackOwner {
    u8 pad000[4];
    NodeTransform transform;
} CallbackOwner;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    u16 field_00;
    u8 pad002[2];
    Owner *field_04;
    u8 pad008[0x48];
    int field_50;
    u8 pad054[0xc];
    u16 flags60;
    u8 pad062[0x12];
    VecFx32 field_74;
    int field_80;
    u8 pad084[0x18];
    CallbackOwner *field_9c;
    NodeTransform field_a0;
    u8 pad_cc[0x48];
    VecFx32 field_114;
    int field_120;
    VecFx32 field_124;
    int field_130;
    int field_134;
    int field_138;
    int field_13c;
    void *field_140;
    u8 pad144[0x36];
    u8 field_17a;
    u8 field_17b;
    u8 field_17c;
};

typedef struct Sphere {
    VecFx32 center;
    int radius;
} Sphere;

typedef struct CollisionHit {
    void *field_00;
    void *field_04;
    void *field_08;
    int field_0c;
} CollisionHit;

typedef struct CollisionInfo {
    u8 pad00[0x14];
    s16 field_14;
    s16 field_16;
    s16 field_18;
    u8 pad1a[8];
    u16 field_22;
    u8 pad24[0x60];
    u16 field_84;
} CollisionInfo;

extern int func_ov107_020ca414(void *obj, Sphere *sphere,
                               VecFx32 *outList, VecFx32 *outDirection);
extern int func_ov107_020ca860(void *obj, Sphere *sphere,
                               VecFx32 *outList, VecFx32 *outDirection);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffa724(int factor, const VecFx32 *source, VecFx32 *destination);
extern long long func_01ff8a14(int numerator, int denominator);
extern void func_0203ca30(NodeTransform *dst, VecFx32 *src);
extern void func_ov107_020c4ecc(struct AiState *node);
extern CollisionHit *func_01fff920(void *obj, VecFx32 *origin, VecFx32 *direction);
extern void func_0203c7ac(void *obj, unsigned int tick);
extern const VecFx32 data_02042264;

static inline int scale_by_ratio(long long ratio, int value)
{
    return (int)(((ratio * (long long)value) + 0x80000000LL) >> 32);
}

static inline void ScaleRatioVector(long long ratio, const VecFx32 *source,
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

#pragma push
#pragma opt_lifetimes off
void func_ov107_020c41e4(struct AiState *self, unsigned int tick)
{
    VecFx32 position;
    VecFx32 rayDirection;
    VecFx32 difference;
    VecFx32 list[4];
    VecFx32 direction;
    VecFx32 sumA;
    VecFx32 normalizedA[4];
    int distanceA[4];
    long long ratioA[4];
    VecFx32 weightedA;
    VecFx32 normalizedB[4];
    int distanceB[4];
    long long ratioB[4];
    VecFx32 sumB;
    VecFx32 weightedB;
    int countA;
    int countB;
    int negativeScale;
    int update;
    int radiusA;
    int radiusB;
    int total;
    Owner *collisionOwner;
    int dot;
    int cooldown;
    CollisionHit *hit;
    Owner *queryOwner;
    int value;

    collisionOwner = self->field_04;
    if (self->field_50 == 1) {
        self->field_17c &= ~1;
    }
    if (self->field_50 == 1 &&
        ((unsigned int)(self->flags60 << 24) >> 24 & 1) != 0 &&
        collisionOwner->field_7c != 0 &&
        (self->field_00 & 0x80) == 0) {
        VEC_Set(&direction, 0, 0, 0);
        VEC_Set(&sumA, 0, 0, 0);
        cooldown = self->field_17b;
        update = 0;
        queryOwner = self->field_04;
        if (cooldown != 0) {
            self->field_17b = (u8)(cooldown - 1);
        }

        if (((unsigned int)(self->flags60 << 24) >> 24 & 4) == 0) {
            countA = func_ov107_020ca414(queryOwner->field_7c,
                                          (Sphere *)&self->field_74,
                                          list, &direction);
            if (countA > 0) {
                radiusA = self->field_80;
                total = 0;
                {
                    int i;
                for (i = 0; i < countA; i++) {
                    VEC_Subtract(&self->field_74, &list[i], &difference);
                    value = func_01ff8d18(&difference, &normalizedA[i]);
                    distanceA[i] = radiusA - value;
                    func_01ffa724(distanceA[i], &normalizedA[i], &normalizedA[i]);
                    total += distanceA[i];
                }
                }
                {
                    int i;
                for (i = 0; i < countA; i++) {
                    ratioA[i] = func_01ff8a14(distanceA[i], total);
                }
                }
                {
                    const VecFx32 *normal;
                    int weightIndex = 0;
                    if (countA > 0) {
                        normal = normalizedA;
                        do {
                            ScaleRatioVector(ratioA[weightIndex], normal, &weightedA);
                            VEC_Add(&sumA, &weightedA, &sumA);
                            normal++;
                            weightIndex++;
                        } while (weightIndex < countA);
                    }
                }
                func_01ff8d18(&sumA, &self->field_114);
                self->field_120 = VEC_Mag(&self->field_74) - radiusA;
                update = 1;
                if (self->field_17b == 0) {
                    self->field_17a |= 4;
                    self->field_17b = 4;
                }
            }
        }

        if ((self->field_00 & 0x100) == 0) {
            countB = func_ov107_020ca860(queryOwner->field_7c,
                                          (Sphere *)&self->field_74,
                                          list, &direction);
            if (countB > 0) {
                VEC_Set(&sumB, 0, 0, 0);
                radiusB = self->field_80;
                negativeScale = -0x1000;
                total = 0;
                {
                    int i;
                for (i = 0; i < countB; i++) {
                    VEC_Subtract(&self->field_74, &list[i], &difference);
                    if (VEC_DotProduct(&difference, &direction) < 0) {
                        func_01ffa724(negativeScale, &difference, &difference);
                        value = func_01ff8d18(&difference, &normalizedB[i]);
                        distanceB[i] = radiusB + value;
                    } else {
                        value = func_01ff8d18(&difference, &normalizedB[i]);
                        distanceB[i] = radiusB - value;
                    }
                    value = distanceB[i];
                    func_01ffa724(value, &normalizedB[i], &normalizedB[i]);
                    total += value;
                }
                }
                {
                    int i;
                for (i = 0; i < countB; i++) {
                    ratioB[i] = func_01ff8a14(distanceB[i], total);
                }
                }
                {
                    const VecFx32 *normal;
                    int weightIndex = 0;
                    if (countB > 0) {
                        normal = normalizedB;
                        do {
                            ScaleRatioVector(ratioB[weightIndex], normal, &weightedB);
                            VEC_Add(&sumB, &weightedB, &sumB);
                            normal++;
                            weightIndex++;
                        } while (weightIndex < countB);
                    }
                }
                func_01ff8d18(&sumB, &direction);
                dot = VEC_DotProduct(&direction, &data_02042264);
                if (dot >= -0x200 && dot <= 0x200) {
                    self->field_17a |= 4;
                    func_01ff8d18(&direction, &self->field_114);
                    self->field_120 = VEC_Mag(&self->field_74) - radiusB;
                }
                if (dot > 0) {
                    self->field_17c = (u8)((self->field_17c & ~1) | 1);
                    self->field_124.x = direction.x;
                    self->field_124.y = direction.y;
                    self->field_124.z = direction.z;
                    self->field_140 = 0;
                }
                if (update != 0) {
                    func_01ffa724(0x800, &sumB, &sumB);
                }
                VEC_Add(&sumA, &sumB, &sumA);
                update = 1;
            }
        }

        if (update != 0) {
            VEC_Add(&self->field_a0.translation, &sumA, &position);
            func_0203ca30(&self->field_a0, &position);
            func_ov107_020c4ecc(self);
        }
    }

    position = self->field_74;
    rayDirection.x = 0;
    rayDirection.y = -0x32000;
    rayDirection.z = 0;
    hit = func_01fff920(collisionOwner->field_7c, &position, &rayDirection);
    if (hit != 0 &&
        (hit->field_08 == 0 ||
         (hit->field_08 != 0 &&
          (((CollisionInfo *)hit->field_08)->field_22 & 0xff) == 0))) {
        int groundDistance = (int)(((s64)hit->field_0c * rayDirection.y) >> 27);
        if (groundDistance < 0) {
            groundDistance = -groundDistance;
        }
        self->field_13c = groundDistance;
        self->field_140 = hit->field_04;
        self->field_124.x = ((CollisionInfo *)self->field_140)->field_14;
        self->field_124.y = ((CollisionInfo *)self->field_140)->field_16;
        self->field_124.z = ((CollisionInfo *)self->field_140)->field_18;
        if (self->field_9c != 0) {
            *(u16 *)((u8 *)self->field_9c + 0x70) =
                ((CollisionInfo *)self->field_140)->field_84;
        }
        if (((u32)(self->flags60 << 24) >> 24 & 8) == 0 &&
            self->field_13c < self->field_80) {
            rayDirection.y = self->field_80 - self->field_13c;
            VEC_Add(&self->field_a0.translation, &rayDirection, &position);
            func_0203ca30(&self->field_a0, &position);
            func_ov107_020c4ecc(self);
        }
    } else {
        self->field_124.x = 0;
        self->field_124.y = 0x1000;
        self->field_124.z = 0;
        self->field_13c = 0;
        self->field_140 = 0;
    }

    if (((unsigned int)(self->flags60 << 24) >> 24 & 1) != 0 && self->field_9c != 0) {
        ((CallbackOwner *)self->field_9c)->transform = self->field_a0;
        func_0203c7ac(self->field_9c, tick);
    }
}
#pragma pop
