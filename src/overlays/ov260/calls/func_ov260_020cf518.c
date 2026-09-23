/* Settle tick of the ov260 actor after a landing: after 0x400 of the +0x70 timer its +0x14 point is
 * pushed out of the scene geometry inside a sphere of its +0x80 radius (each contact weighs by the
 * radius less its distance, the unit directions scaled by those weights are summed by their share
 * of the total, 64-bit ratios), then dropped onto the floor below it (probe of twice the radius from
 * one radius above, reflected by the floor plane). The actor is placed there (020c5c54), knocked back
 * one radius above it (mode 3), effect 0xc starts there, bits 1 and 7 of the +0x60 high byte drop and
 * the node moves on to the armed +0xc entry, if any. */
typedef unsigned short u16;
typedef struct { int x, y, z; } VecFx32;
typedef struct { VecFx32 pos; int nRadius; } Sphere;

extern int func_ov107_020ca414(void *collision, Sphere *sphere, VecFx32 *list, VecFx32 *direction);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *out);
extern void func_01ffa724(int factor, const VecFx32 *source, VecFx32 *destination);
extern long long func_01ff8a14(int numerator, int denominator);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void *func_01fff888(void *collision, VecFx32 *origin, VecFx32 *direction);
extern void func_01ffd144(int plane, VecFx32 *in, VecFx32 *out);
extern void func_ov107_020c5c54(int actor, VecFx32 *at);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);

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

void func_ov260_020cf518(int *node)
{
    int *state = (int *)node[1];
    VecFx32 at;
    Sphere sphere;
    VecFx32 list[4];
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
    int scene;
    void *hit;

    state[0x1c] += *(int *)(node[0] + 0x2c);
    if (state[0x1c] < 0x400) {
        return;
    }
    scene = *(int *)(*state + 4);
    VEC_Set(&direction, 0, 0, 0);
    sphere.pos = *(VecFx32 *)(state + 5);
    sphere.nRadius = *(int *)(*state + 0x80);
    count = func_ov107_020ca414(*(void **)(scene + 0x7c), &sphere, list, &direction);
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
        VEC_Add((VecFx32 *)(state + 5), &sum, (VecFx32 *)(state + 5));
    }
    sphere.pos = *(VecFx32 *)(state + 5);
    direction.x = 0;
    sphere.pos.y += sphere.nRadius;
    direction.y = -sphere.nRadius * 2;
    direction.z = 0;
    hit = func_01fff888(*(void **)(scene + 0x7c), &sphere.pos, &direction);
    if (hit != 0) {
        func_01ffd144(*(int *)((char *)hit + 0xc), &direction, &direction);
        VEC_Add(&sphere.pos, &direction, (VecFx32 *)(state + 5));
    }
    func_ov107_020c5c54(*state, (VecFx32 *)(state + 5));
    at = *(VecFx32 *)(state + 5);
    at.y += *(int *)(*state + 0x80);
    func_ov107_020c0b90(*state, 3, at, 0);
    func_ov260_020cd148(*state, 0xc, (int)&at);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
    }
    if (state[3] == 0) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)state[3]);
}
