typedef signed int s32;
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
    u8 pad00[0x74];
    s32 radius74;
    s32 nearestHit78;
    u8 pad7c[0x10];
} CollCastState;

typedef struct CollisionWorld {
    void *unknown00;
    void **modelList;
} CollisionWorld;

typedef struct CollisionHitRecord {
    void *model;
    void *face;
    s32 unknown08;
    s32 distance;
} CollisionHitRecord;

extern void func_01ffef34(CollCastState *state, CollCastParams *params);
extern int func_01ffefb4(CollCastState *state, void *modelList);
extern CollisionHitRecord data_027e0764;

CollisionHitRecord *func_01fff83c(CollisionWorld *world, CollCastParams *params)
{
    CollCastState state;

    func_01ffef34(&state, params);
    if (func_01ffefb4(&state, *world->modelList) != 0) {
        data_027e0764.distance = state.nearestHit78;
        return &data_027e0764;
    }
    return 0;
}
