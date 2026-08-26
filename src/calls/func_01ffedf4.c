typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

typedef struct CollCastParams {
    VecFx32 *origin;
    VecFx32 *direction;
    s32 radius;
    u16 directionIsUnit;
    u16 flags;
    void *exclude;
} CollCastParams;

typedef struct CollCastState {
    u32 mode00;
    u8 pad04[0x1c - 0x04];
    VecFx32 direction1c;
    VecFx32 origin28;
    u8 pad34[0x70 - 0x34];
    s32 unknown70;
    s32 radius74;
    s32 nearestHit78;
    u8 pad7c[0x10];
} CollCastState;

typedef struct CollisionHitRecord {
    void *model;
    void *face;
    void *object;
    s32 distance;
} CollisionHitRecord;

extern CollisionHitRecord data_027e0764;

void func_01ffedf4(CollCastState *state, CollCastParams *params)
{
    state->mode00 = params->directionIsUnit;
    state->origin28 = *params->origin;
    state->direction1c = *params->direction;
    state->nearestHit78 = 0x7fffffff;
    state->unknown70 = 0;
    data_027e0764.face = 0;
    data_027e0764.object = 0;
    data_027e0764.distance = 0x7fffffff;
}
