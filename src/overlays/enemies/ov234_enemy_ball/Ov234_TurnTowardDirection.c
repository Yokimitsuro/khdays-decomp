/* Turns the enemy towards its target direction at a limited rate (or snaps), updates its rotation
 * and moves its node along the new facing. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

struct Ov234VecBlock {
    VecFx32 vector;
    int unused;
};

static inline void Ov234Vec3_Set(VecFx32 *vec, int x, int y, int z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline int Ov234FxMul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

struct Ov234ObjectFlags {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char rest : 6;
};

struct Ov234Object {
    char pad000[0x2c];
    int frameDelta2c;
    char pad030[0x70];
    VecFx32 anchorA0;
    char pad0ac[0x44];
    VecFx32 movementF0;
    char pad0fc[0x18];
    VecFx32 vector114;
    char pad120[0x5a];
    struct Ov234ObjectFlags flags17a;
    char pad17b[0x23d];
    int value3b8;
};

struct Ov234State {
    struct Ov234Object *object00;
    int field04;
    int node08;
    int field0c;
    VecFx32 direction10;
    VecFx32 effectPosition1c;
    char pad28[0x0c];
    int angle34;
    int targetAngle38;
    int computedAngle3c;
    int field40;
    int effectTimer44;
    int countdown48;
    char pad4c[0x08];
    int lowerLimit54;
    int verticalStep58;
    int verticalScale5c;
    int field60;
    int preserveDirection64;
    int snapAngle68;
    int reactionLatched6c;
};

struct Ov234Node {
    struct Ov234Object *object;
    struct Ov234State *state;
};

extern const VecFx32 data_02042264;
extern const VecFx32 data_02041dc8;
extern const short data_0203d210[];

extern void Srt_SetRotationQuat(VecFx32 *, VecFx32 *);
extern int VEC_DotProduct(VecFx32 *, VecFx32 *);
extern void ScaleVec3Fx12(int, VecFx32 *, VecFx32 *);
extern void VEC_Subtract(VecFx32 *, VecFx32 *,
                         VecFx32 *);
extern int VEC_Normalize(VecFx32 *, VecFx32 *);
extern fx16 FX_Atan2(int, int);
extern void Ov107_BuildAndSendUpdate(struct Ov234Object *, int, int, int);

void Ov234_TurnTowardDirection(struct Ov234Node *node)
{
    struct Ov234State *state = node->state;
    struct Ov234VecBlock rotated;
    VecFx32 objectVector;
    VecFx32 facing;
    VecFx32 projected;
    VecFx32 oldDirection;
    VecFx32 newDirection;
    int turnStep;
    int angleIndex;

    turnStep = node->object->frameDelta2c * 90 / 10;
    if (state->snapAngle68 != 0) {
        state->angle34 = state->targetAngle38;
    } else {
        state->angle34 = Angle_TurnToward(
            state->angle34, state->targetAngle38,
            turnStep, 0);
    }

    QuatFromAxisAngle(&rotated.vector, &data_02042264, state->angle34);
    Srt_SetRotationQuat(&state->object00->anchorA0, &rotated.vector);

    if (state->object00->flags17a.bit1 == 0) {
        state->reactionLatched6c = 0;
    }

    if (state->object00->flags17a.bit1 != 0 &&
        state->object00->flags17a.bit0 == 0 &&
        state->reactionLatched6c == 0) {
        objectVector = state->object00->vector114;
        angleIndex =
            ((int)(unsigned short)((unsigned int)(
                ((long long)state->angle34 * 0x28be60db9391LL +
                 0x80000000000LL) >> 32) >> 12) >> 4);
        Ov234Vec3_Set(&facing,
                      -data_0203d210[angleIndex * 2],
                      0,
                      -data_0203d210[angleIndex * 2 + 1]);
        ScaleVec3Fx12(VEC_DotProduct(&facing, &objectVector) << 1,
                      &objectVector, &projected);
        VEC_Subtract(&projected, &facing, &projected);
        VEC_Normalize(&projected, &projected);
        state->computedAngle3c = FX_Atan2(projected.x, projected.z);

        oldDirection = state->direction10;
        ScaleVec3Fx12(VEC_Normalize(&state->direction10,
                                    &state->direction10),
                      &projected, &newDirection);
        state->direction10.x = newDirection.x;
        state->direction10.y = oldDirection.y;
        state->direction10.z = newDirection.z;
        state->angle34 = state->targetAngle38 =
            FX_Atan2(state->direction10.x, state->direction10.z);
        Ov107_BuildAndSendUpdate(state->object00, 0x178, 4, state->node08);
        state->reactionLatched6c = 1;
    }

    state->object00->movementF0 = state->direction10;

    if (state->object00->flags17a.bit0 != 0) {
        if (state->preserveDirection64 == 0) {
            state->direction10 = data_02041dc8;
        }
    }

    state->direction10.x = Ov234FxMul(state->direction10.x, 0xd00);
    state->direction10.z = Ov234FxMul(state->direction10.z, 0xd00);

    if (*(int *)((char *)state->node08 + 4) > 0x19000) {
        state->direction10.z = Ov234FxMul(state->direction10.z, 0xc00);
    }

    if (state->direction10.y > 0x100) {
        state->direction10.y =
            Ov234FxMul(state->direction10.y, state->verticalScale5c);
    } else if (state->direction10.y > state->lowerLimit54) {
        state->direction10.y += state->verticalStep58;
    }

    state->effectTimer44 += node->object->frameDelta2c;
    if (state->effectTimer44 > 0x77880) {
        Ov107_MoveNodeAndRelayout((Actor *)state->object00, &state->effectPosition1c);
        state->effectTimer44 = 0;
    }

    if (state->countdown48 > 0) {
        state->countdown48 -= node->object->frameDelta2c;
    } else {
        state->countdown48 = 0;
    }

    if (state->object00->value3b8 < 0x1e) {
        state->lowerLimit54 = -0x280;
        state->verticalStep58 = -0x38;
        state->verticalScale5c = 0xe00;
        state->field60 = 0x400;
        return;
    }
    if (state->object00->value3b8 < 0x32) {
        state->lowerLimit54 = -0x2c0;
        state->verticalStep58 = -0x3c;
        state->verticalScale5c = 0xdc0;
        state->field60 = 0x480;
        return;
    }
    if (state->object00->value3b8 < 0x64) {
        state->lowerLimit54 = -0x300;
        state->verticalStep58 = -0x40;
        state->verticalScale5c = 0xd90;
        state->field60 = 0x500;
        return;
    }
    if (state->object00->value3b8 < 0x96) {
        state->lowerLimit54 = -0x340;
        state->verticalStep58 = -0x44;
        state->verticalScale5c = 0xd60;
        state->field60 = 0x600;
        return;
    }
    state->lowerLimit54 = -0x380;
    state->verticalStep58 = -0x48;
    state->verticalScale5c = 0xd30;
    state->field60 = 0x700;
}
