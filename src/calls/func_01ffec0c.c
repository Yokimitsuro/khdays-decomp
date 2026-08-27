typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct VecFx32 { s32 x; s32 y; s32 z; } VecFx32;

typedef struct CollCastParams {
    VecFx32 *origin00;
    VecFx32 *direction04;
    s32 radius08;
    u16 directionIsUnit0c;
    u16 flags0e;
    void *extra10;
} CollCastParams;

typedef struct CollCastState {
    u32 mode00;
    void *modelDataA04;
    void *modelDataB08;
    u8 pad0c[0x1c - 0x0c];
    VecFx32 direction1c;
    VecFx32 origin28;
    u8 pad34[0x44 - 0x34];
    VecFx32 unitDirection44;
    s32 directionLength50;
    u8 pad54[0x70 - 0x54];
    s32 unknown70;
    s32 radius74;
    s32 nearestHit78;
    u8 pad7c[8];
    void *extra84;
    u16 flags88;
} CollCastState;

typedef struct CollisionHitRecord {
    void *model00;
    void *face04;
    u32 unknown08;
    s32 distance0c;
} CollisionHitRecord;

extern s32 func_01ff8d18(VecFx32 *input, VecFx32 *output);
extern CollisionHitRecord data_027e0764;

void func_01ffec0c(CollCastState *state, CollCastParams *params)
{
    VecFx32 *direction;

    state->mode00 = params->directionIsUnit0c;
    state->origin28 = *params->origin00;
    state->nearestHit78 = 0x50000000;
    state->extra84 = params->extra10;
    state->flags88 = params->flags0e;
    state->unknown70 = 0;

    direction = params->direction04;
    if ((direction->x | direction->z) != 0) {
        state->direction1c = *direction;
        if (params->directionIsUnit0c == 0) {
            state->directionLength50 = func_01ff8d18(params->direction04, &state->unitDirection44);
        }
    } else {
        s32 y = direction->y;

        state->direction1c.z = 0;
        state->direction1c.x = 0;
        state->direction1c.y = y;
        if (params->directionIsUnit0c == 0) {
            state->unitDirection44.z = 0;
            state->unitDirection44.x = 0;
            state->unitDirection44.y = 0x1000;
            state->directionLength50 = y;
            if (y < 0) {
                state->unitDirection44.y *= -1;
                state->directionLength50 *= -1;
            }
        }
    }

    data_027e0764.face04 = 0;
    data_027e0764.unknown08 = 0;
    data_027e0764.distance0c = 0x7fffffff;
}
