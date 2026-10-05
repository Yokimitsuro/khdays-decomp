/* Computes the character's aim: faces the locked target (turning the display node once) and derives
 * the movement direction from the input and the anchor. */

#pragma opt_propagation off
#pragma opt_common_subs off

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

struct Ov044TickVectors {
    VecFx32 horizontal;
    VecFx32 direction;
    VecFx32 movement;
};

struct Ov044Node {
    u32 flags00;
    u16 flags04;
    char pad006[0x7a];
    u16 angle80;
};

struct Ov044Actor;
typedef int (*Ov044ActorCallback)(struct Ov044Actor *actor, int mode);
typedef int (*Ov044ActorUpdateCallback)(struct Ov044Actor *actor);

struct Ov044ActorBits694 {
    u8 bit0 : 1;
    u8 callbackActive : 1;
};

struct Ov044ActorFlags000Bits {
    u32 low16 : 16;
    int flag10000 : 1;
};

struct Ov044Actor {
    u64 flags000;
    char pad008[0x18];
    struct Ov044Node *node20;
    u32 flags24;
    char pad028[0x30];
    int verticalDelta58;
    char pad05c[0x408];
    u64 flags464;
    u64 flags46c;
    char pad474[6];
    u8 action47a;
    u8 action47b;
    char pad47c[0x10];
    VecFx32 anchor48c;
    VecFx32 accumulated498;
    char pad4a4[0x28];
    int timer4cc;
    char pad4d0[0x194];
    Ov044ActorCallback callback664;
    Ov044ActorUpdateCallback callback668;
    char pad66c[0x28];
    struct Ov044ActorBits694 bits694;
    char pad695[3];
    VecFx32 accumulated698;
    char pad6a4[0x10c];
    int timeline7b0;
};

struct Ov044Controller4908 {
    char pad000[4];
    int latched04;
    char pad008[0xdac];
    struct Ov044Actor *actorDb4;
};

extern int Ov022_ValidateTargetRef(struct Ov044Actor *actor);
extern VecFx32 *func_ov022_020ad0c0(struct Ov044Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b,
                         VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int FX_Atan2Idx(int y, int x);
extern void Ov022_StepAnchorDelta(struct Ov044Actor *actor, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b,
                    VecFx32 *out);
extern void Ov030_EmitTimelineEffect(struct Ov044Controller4908 *self);
extern void *Ov022_ActorSetState(struct Ov044Actor *actor, int mode);

void *Ov030_ComputeAimAngle(struct Ov044Controller4908 *self)
{
    void *result = 0;
    struct Ov044Actor *actor = self->actorDb4;

    if (Session_GetLocalPlayerIndex() == 0) {
        actor->flags464 |= 0x10000ULL;
    }
    actor->flags46c |= 0x10000ULL;

    register int gateTimeline = actor->timeline7b0;
    if (gateTimeline >= 0x4b000) {
        if (self->latched04 == 0) {
            register u32 initialFlags = (u32)actor->flags000;
            register u32 initialMask = 0x10000;
            if ((initialFlags & initialMask) == 0) {
                actor->action47a = 3;
                actor->action47b = 1;
                self->latched04 = 1;
            }
        }
    }
    struct Ov044TickVectors vectors;

    if (actor->timeline7b0 == 0x3f000 &&
        Ov022_ValidateTargetRef(actor) != 0) {
        struct Ov044Node *node;
        u16 angle;

        VEC_Subtract(func_ov022_020ad0c0(actor), &actor->anchor48c,
                     &vectors.direction);
        if (VEC_Mag(&vectors.direction) != 0) {
            VEC_Normalize(&vectors.direction, &vectors.direction);
        }
        angle = (u16)FX_Atan2Idx(-vectors.direction.x, -vectors.direction.z);
        node = actor->node20;
        if ((node->flags00 & 0x20) == 0) {
            node->angle80 = angle + 0x8000;
            node->flags04 |= 0x20;
        }
    }

    if (Session_GetLocalPlayerIndex() == 0) {
        actor->flags464 |= 8ULL << 32;
    }

    Ov022_StepAnchorDelta(actor, &vectors.movement);
    if (vectors.movement.y != 0) {
        actor->verticalDelta58 = vectors.movement.y;
    } else if ((actor->flags24 & 4) == 0) {
        actor->flags000 |= 0x4000ULL << 32;
        actor->verticalDelta58 = 0;
    }

    vectors.horizontal = vectors.movement;
    vectors.horizontal.y = 0;
    VEC_Add(&actor->accumulated498, &vectors.horizontal,
            &actor->accumulated498);
    Ov030_EmitTimelineEffect(self);

    actor->bits694.callbackActive = actor->callback668(actor);
    if (actor->bits694.callbackActive) {
        struct Ov044Node *node;

        actor->flags000 |= 0x20000ULL << 32;
        node = actor->node20;
        if ((node->flags00 & 0x20) == 0) {
            SceneNode_Enable(&node->flags04);
        }
        if (Session_GetLocalPlayerIndex() == 0) {
            actor->flags464 |= 2ULL;
        }
    }

    if ((actor->flags464 & 2ULL) != 0 && actor->timer4cc >= 0x1e000) {
        actor->accumulated498.z = 0;
        actor->accumulated498.y = 0;
        actor->accumulated498.x = 0;
        actor->accumulated698.z = 0;
        actor->accumulated698.y = 0;
        actor->accumulated698.x = 0;
        actor->flags000 |= 4ULL;
        if ((actor->flags24 & 4) != 0) {
            result = Ov022_ActorSetState(actor, 0);
            actor->callback664(actor, 0);
        } else {
            actor->accumulated698.x = actor->accumulated698.y =
                actor->accumulated698.z = 0;
            result = Ov022_ActorSetState(actor, 2);
        }
    }

    return result;
}
