typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
};

struct Vec4 {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
};

struct Sphere {
    struct Vec3 center;
    s32 radius;
};

struct Component388 {
    char pad00[8];
    s32 flags08;
};

struct Transform {
    struct Vec3 position;
    char pad0c[0x70];
    void *field7c;
};

struct Actor {
    void *node00;
    struct Transform *transform04;
    char pad08[0x58];
    u16 flags60;
    char pad62[0x3e];
    char fieldA0[0x84];
    struct Vec3 direction124;
    char pad130[0x4a];
    u8 flags17a;
    char pad17b[0x20d];
    struct Component388 *component388;
};

struct Inner {
    struct Actor *actor00;
    struct Vec3 *target04;
};

struct Task {
    char pad00[4];
    struct Inner *inner04;
    char pad08[0x18];
    s8 index20;
};

struct HitInfo {
    char pad00[0x14];
    s16 x14;
    s16 y16;
    s16 z18;
};

struct HitState {
    char pad00[0x22];
    u16 flags22;
};

struct Hit {
    char pad00[4];
    struct HitInfo *info04;
    struct HitState *state08;
    void *field0c;
};

extern struct Vec4 data_02042264;

extern struct Hit *func_01fff8b8(void *a, struct Vec3 *b, struct Vec3 *c, int d);
extern void func_01ffd144(void *a, struct Vec3 *b, struct Vec3 *c);
extern void func_01ff8d18(struct Vec3 *dst, struct Vec3 *src);
extern int func_ov107_020c5c54(void *node, struct Vec3 *pos);
extern int func_0202ed60(struct Vec4 *out, struct Vec4 *m, struct Vec3 *v);
extern int func_0203c9d0(void *dst, struct Vec4 *src);
extern void func_0203c634(struct Task *obj, int idx, void *value);
extern int func_ov107_020ca414(void *a, struct Sphere *b, struct Vec3 *outList, struct Vec3 *outDir);
extern void VEC_Subtract(struct Vec3 *a, struct Vec3 *b, struct Vec3 *out);
extern int VEC_Mag(struct Vec3 *v);

struct StackLocals {
    struct Vec3 diff;
    struct Vec3 candidates[4];
    struct Sphere sphere;
    struct Vec4 matrix;
    struct Vec3 direction;
    struct Vec3 result;
    struct Vec3 offset;
};

static inline s32 mul_round(s32 a, s32 b)
{
    return (s32)(((s64)a * b + 0x800) >> 12);
}

void func_ov294_020d2008(struct Task *arg0)
{
    struct StackLocals s;
    struct Inner *inner;
    struct Component388 *component;
    struct Hit *hit;
    struct Transform *transform;
    int i;
    int count;
    int nearest;
    int distance;
    int scale;
    u16 flags;

    inner = arg0->inner04;
    component = inner->actor00->component388;
    transform = inner->actor00->transform04;

    {
        s32 old = component->flags08;
        u32 low = (u32)(old << 24) >> 24;

        low |= 1;
        old &= ~0xff;
        low &= 0xff;

        component->flags08 = old | low;
    }

    s.offset.x = 0;
    s.offset.y = 0x1200;
    s.offset.z = 0;

    hit = func_01fff8b8(transform->field7c, inner->target04, &s.offset, 0);

    if (hit != 0 &&
        (hit->state08 == 0 ||
         (hit->state08 != 0 && !(hit->state08->flags22 & 0xff)))) {
        func_01ffd144(hit->field0c, &s.offset, &s.offset);

        s.direction.x = hit->info04->x14;
        s.direction.y = hit->info04->y16;
        s.direction.z = hit->info04->z18;

        func_01ff8d18(&s.direction, &s.direction);

        s.result.x = inner->target04->x + s.offset.x + mul_round(s.direction.x, 0x1200);
        s.result.y = inner->target04->y + s.offset.y + mul_round(s.direction.y, 0x1200);
        s.result.z = inner->target04->z + s.offset.z + mul_round(s.direction.z, 0x1200);

        func_ov107_020c5c54(inner->actor00, &s.result);
        func_0202ed60(&s.matrix, &data_02042264, &s.direction);
        func_0203c9d0(&inner->actor00->fieldA0, &s.matrix);

        flags = inner->actor00->flags60;
        inner->actor00->flags60 = (u16)((flags & ~0xff00) |
            (((((u32)(flags << 16) >> 24) | 0x40) << 24) >> 16));

        flags = inner->actor00->flags60;
        inner->actor00->flags60 = (u16)((flags & ~0xff00) |
            (((u32)(u16)(((u32)(flags << 16) >> 24) & ~0x1e)) << 24) >> 16);

        func_0203c634(arg0, arg0->index20, 0);
        return;
    }

    s.sphere.center = *inner->target04;
    s.sphere.radius = 0x1200;

    count = func_ov107_020ca414(transform->field7c, &s.sphere, s.candidates, &s.direction);

    if (count > 0) {
        nearest = 0x7fffffff;

        for (i = 0; i < count; i++) {
            VEC_Subtract(&s.sphere.center, &s.candidates[i], &s.diff);

            distance = VEC_Mag(&s.diff);

            if (distance < nearest) {
                nearest = distance;

                func_01ff8d18(&s.diff, &s.direction);
            }
        }

        scale = 0x1200 - nearest;

        s.result.x = inner->target04->x + mul_round(s.direction.x, scale);
        s.result.y = inner->target04->y + mul_round(s.direction.y, scale);
        s.result.z = inner->target04->z + mul_round(s.direction.z, scale);

        func_ov107_020c5c54(inner->actor00, &s.result);
        func_0202ed60(&s.matrix, &data_02042264, &s.direction);
        func_0203c9d0(&inner->actor00->fieldA0, &s.matrix);

        flags = inner->actor00->flags60;
        inner->actor00->flags60 = (u16)((flags & ~0xff00) |
            (((((u32)(flags << 16) >> 24) | 0x40) << 24) >> 16));

        flags = inner->actor00->flags60;
        inner->actor00->flags60 = (u16)((flags & ~0xff00) |
            (((u32)(u16)(((u32)(flags << 16) >> 24) & ~0x1e)) << 24) >> 16);

        func_0203c634(arg0, arg0->index20, 0);
        return;
    }

    if (((u32)(inner->actor00->flags17a << 31) >> 31) != 0) {
        func_0202ed60(&s.matrix, &data_02042264, &inner->actor00->direction124);
        func_0203c9d0(&inner->actor00->fieldA0, &s.matrix);

        flags = inner->actor00->flags60;
        inner->actor00->flags60 = (u16)((flags & ~0xff00) |
            (((((u32)(flags << 16) >> 24) | 0x40) << 24) >> 16));

        func_0203c634(arg0, arg0->index20, 0);
        return;
    }

    flags = inner->actor00->flags60;
    inner->actor00->flags60 = (u16)((flags & ~0xff00) |
        (((u32)(u16)(((u32)(flags << 16) >> 24) & ~0x48)) << 24) >> 16);
}
