/* Special attack finishing step: turns the actor towards its target, emits the timeline effects and
 * ends the attack when its slot is ready. */

#pragma opt_propagation off
#pragma opt_common_subs off

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

struct Ov044UpdateVectors {
    VecFx32 horizontal;
    VecFx32 movement;
    VecFx32 direction;
};

struct TimelineActorNode {
    u32 flags00;
    u16 flags04;
    char pad006[0x7a];
    u16 angle80;
};

struct TimelineActor;
typedef int (*TimelineActorModeCallback)(struct TimelineActor *actor, int mode);
typedef int (*TimelineActorTickCallback)(struct TimelineActor *actor);

struct TimelineActorBits694 {
    u8 bit0 : 1;
    u8 callbackActive : 1;
};

struct TimelineActor {
    u64 flags000;
    char pad008[0x10];
    u16 flags18;
    char pad01a[6];
    struct TimelineActorNode *node20;
    u32 flags24;
    char pad028[0x30];
    int verticalDelta58;
    char pad05c[0x408];
    u64 flags464;
    u64 flags46c;
    char pad474[0x18];
    VecFx32 anchor48c;
    VecFx32 accumulated498;
    char pad4a4[0x1c0];
    TimelineActorModeCallback callback664;
    TimelineActorTickCallback callback668;
    char pad66c[0x28];
    struct TimelineActorBits694 bits694;
    char pad695[3];
    VecFx32 accumulated698;
    char pad6a4[0x10c];
    int timeline7b0;
    char pad7b4[0x1b44];
    u8 effectContext22f8[1];
};

struct TimelineActorOwner {
    char pad000[8];
    int latched08;
    char pad00c[0xda8];
    struct TimelineActor *actorDb4;
};

extern int Ov022_ValidateTargetRef(struct TimelineActor *actor);
extern VecFx32 *func_ov022_020ad0c0(struct TimelineActor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b,
                         VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int FX_Atan2Idx(int y, int x);
extern void Ov022_StepAnchorDelta(struct TimelineActor *actor, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b,
                    VecFx32 *out);
extern void Ov099_EmitTimelineEffect(struct TimelineActorOwner *self);
extern int Ov022_IsSlotReady(void *context);
extern int Ov022_IsState9Or6WithFlag200(void *context);
extern void func_ov022_020acf14(struct TimelineActor *actor, int mode);
extern void *Ov022_ActorSetState(struct TimelineActor *actor, int mode);

void *Ov099_UpdateController(struct TimelineActorOwner *self)
{
    void *result = 0;
    struct TimelineActor *actor = self->actorDb4;
    register int angle = -1;
    int finishAllowed = 0;
    int zero;
    struct Ov044UpdateVectors vectors;

    if (Session_GetLocalPlayerIndex() == 0) {
        actor->flags464 |= 0x10000ULL;
    }
    if (Session_GetLocalPlayerIndex() == 0) {
        actor->flags46c |= 0x10000ULL;
    }

    if (Ov022_ValidateTargetRef(actor) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(actor), &actor->anchor48c,
                     &vectors.direction);
        if (VEC_Mag(&vectors.direction) != 0) {
            VEC_Normalize(&vectors.direction, &vectors.direction);
        }
        angle = (u16)FX_Atan2Idx(-vectors.direction.x, -vectors.direction.z);
    }

    if (actor->timeline7b0 % 0x6000 == 0 && angle != -1) {
        struct TimelineActorNode *node = actor->node20;
        if ((node->flags00 & 0x20) == 0) {
            node->angle80 = (u16)(angle + 0x8000);
            node->flags04 |= 0x20;
        }
    }

    if (Session_GetLocalPlayerIndex() == 0) {
        actor->flags464 |= 8ULL << 32;
    }

    Ov022_StepAnchorDelta(actor, &vectors.movement);
    if (vectors.movement.y != 0) {
        actor->verticalDelta58 = vectors.movement.y;
    } else if ((actor->flags24 & 4) == 0 &&
               (Ov022_ValidateTargetRef(actor) != 0 ||
                (actor->flags000 & (0x10ULL << 32)) != 0)) {
        actor->verticalDelta58 = 0;
    }

    vectors.horizontal = vectors.movement;
    vectors.horizontal.y = 0;
    VEC_Add(&actor->accumulated498, &vectors.horizontal,
            &actor->accumulated498);

    if ((actor->flags18 & 1) != 0) {
        self->latched08 = 1;
    }

    actor->bits694.callbackActive = actor->callback668(actor);
    Ov099_EmitTimelineEffect(self);

    if (self->latched08 != 0 && actor->timeline7b0 >= 0x39000) {
        int canDispatch = 1;
        if (Ov022_IsSlotReady(actor->effectContext22f8) != 0) {
            canDispatch = 0;
        }
        int effectActive = Ov022_IsState9Or6WithFlag200(actor->effectContext22f8);

        if (effectActive == 0) {
            canDispatch = 0;
            finishAllowed = 1;
        }
        if (Ov022_ValidateTargetRef(actor) == 0 &&
            (actor->flags24 & 4) == 0 &&
            (actor->flags000 & (0x10ULL << 32)) == 0) {
            canDispatch = 0;
            finishAllowed = 1;
        }
        if (canDispatch != 0) {
            func_ov022_020acf14(actor, 0);
        } else {
            actor->bits694.callbackActive = 1;
        }
    }

    if (actor->timeline7b0 == 0x12000 &&
        (actor->flags000 & (0x10ULL << 32)) == 0 &&
        Ov022_ValidateTargetRef(actor) == 0 &&
        (actor->flags24 & 4) == 0) {
        self->latched08 = 0;
    }

    switch (actor->timeline7b0) {
    case 0x9000:
    case 0x12000:
    case 0x18000:
    case 0x21000:
    case 0x2d000:
    case 0x39000:
        if (self->latched08 == 0) {
            finishAllowed = 1;
            actor->bits694.callbackActive = 1;
        }
        self->latched08 = 0;
        break;
    }

    if (actor->bits694.callbackActive) {
        struct TimelineActorNode *node;

        actor->flags000 |= 0x20000ULL << 32;
        node = actor->node20;
        if ((node->flags00 & 0x20) == 0) {
            SceneNode_Enable(&node->flags04);
        }
        if (Session_GetLocalPlayerIndex() == 0) {
            actor->flags464 |= 2ULL;
        }
    }

    if ((actor->flags464 & 2ULL) != 0) {
        if (actor->timeline7b0 < 0x39000 ||
            Ov022_IsState9Or6WithFlag200(actor->effectContext22f8) == 0 ||
            finishAllowed != 0) {
            zero = 0;
            actor->accumulated698.x = actor->accumulated698.y =
                actor->accumulated698.z = actor->accumulated498.x =
                actor->accumulated498.y = actor->accumulated498.z = zero;
            actor->flags000 |= 4ULL;
            if ((actor->flags24 & 4) != 0) {
                result = Ov022_ActorSetState(actor, zero);
                actor->callback664(actor, 0);
            } else {
                result = Ov022_ActorSetState(actor, 2);
            }
        } else {
            if (Session_GetLocalPlayerIndex() == 0) {
                actor->flags464 |= 0x80000000ULL;
            }
            result = Ov022_ActorSetState(actor, 0x23);
        }
    }

    if (result != 0) {
        actor->flags46c &= ~0x10000ULL;
    }
    return result;
}
