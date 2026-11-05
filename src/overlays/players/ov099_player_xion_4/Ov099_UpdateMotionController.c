/* Per-frame update of a player motion controller: follows the ground rumble in the special state,
 * spawns the emitters at the right moment, updates its path motion and animation, and its
 * sub-objects. */

#include "nitro/types.h"
#include "game/engine.h"

struct TimelineActor {
    char pad000[8];
    u8 owner08;
    char pad009[0x17];
    void *node20;
    char pad024[0x440];
    u64 flags464;
    u64 flags46c;
    char pad474[0x248];
    int state6bc;
    char pad6c0[0xea];
    s16 cue7aa;
    char pad7ac[4];
    int timeline7b0;
};

struct TimelineMotionState {
    char bytes[0x170];
};

struct TimelineActorOwner {
    char pad000[0x0c];
    int pending0c;
    char pad010[4];
    int animState14;
    char animation18[0xe0];
    char animationTablef8[0x138];
    int playerHandle230;
    struct TimelineMotionState motions234[8];
    struct TimelineActor *actorDb4;
};

extern int func_ov022_02083f0c(void);
extern void Ov002_StoreVAndToggleBit25(int handle, int a, int b);
extern int Ov022_FollowGroundRumble(struct TimelineActor *actor);
extern void Ov022_PlayEntityVoice(struct TimelineActor *actor, int nSeqArc, int nSeq);
extern void Ov099_SpawnEmitters(struct TimelineActorOwner *self);
extern int Ov099_ov030_UpdatePathMotionState(struct TimelineActorOwner *self,
                               struct TimelineMotionState *motion, int delta);
extern int Ov022_IsState9Or6WithFlag200(void *buildBlock);
extern void BindAnimTrack(void *animation, int track, void *table, int mode);
extern void Anim_SetFrameWrapped(void *animation, int track, int frame);
extern unsigned short Sequence_UpdateTracks(void *animation, int delta);
extern void Ov099_UpdateNodeActiveByMode(struct TimelineActorOwner *self, int delta);
extern void Ov099_updateSubObjects(struct TimelineActorOwner *self);

void Ov099_UpdateMotionController(struct TimelineActorOwner *self, int delta)
{
    struct TimelineActor *actor = self->actorDb4;
    int active = 0;
    int i;
    struct TimelineMotionState *motion;

    if (actor->state6bc != 0x2f) {
        if (self->playerHandle230 == 1) {
            Ov002_StoreVAndToggleBit25(func_ov022_02083f0c(), 0, 0);
            self->playerHandle230 = 0;
        }
    } else if (actor->owner08 == Session_GetLocalPlayerIndex()) {
        self->playerHandle230 = Ov022_FollowGroundRumble(actor);
    }

    switch (self->pending0c) {
    case 1:
        break;
    default:
        goto afterSpawn;
    }
    if (actor->state6bc != 0x30) {
        goto afterSpawn;
    }
    if (actor->timeline7b0 < 0x39000) {
        goto afterSpawn;
    }
    Ov022_PlayEntityVoice(actor, actor->cue7aa, 0);
    Ov099_SpawnEmitters(self);
    self->pending0c = 0;
afterSpawn:

    motion = self->motions234;
    i = 0;
    do {
        if (Ov099_ov030_UpdatePathMotionState(self, motion, delta) != 0) {
            active = 1;
        }
        i++;
        motion++;
    } while (i < 8);

    if ((u32)(actor->state6bc - 0x2f) <= 1) {
        active = 1;
    }

    if (active != 0) {
        if (Session_GetLocalPlayerIndex() == 0) {
            actor->flags464 |= 0x10000;
        }
        if (Session_GetLocalPlayerIndex() == 0) {
            actor->flags46c |= 0x10000;
        }
    }

    if (self->pending0c != 0) {
        if (Ov022_IsState9Or6WithFlag200((char *)actor + 0x22f8) == 0 &&
            active == 0) {
            self->pending0c = 0;
        }
    }

    if (self->animState14 == 1) {
        goto updateAnimation;
    }
    if (self->animState14 != 2) {
        goto afterAnimation;
    }
    if (actor->timeline7b0 < 0x4b000) {
        goto afterAnimation;
    }
    BindAnimTrack(self->animation18, 0, self->animationTablef8, 0);
    BindAnimTrack(self->animation18, 2, self->animationTablef8, 0);
    Anim_SetFrameWrapped(self->animation18, 0, 0);
    Anim_SetFrameWrapped(self->animation18, 2, 0);
    self->animState14 = 1;
    goto afterAnimation;

updateAnimation:
    if (Sequence_UpdateTracks(self->animation18, delta) != 0) {
        self->animState14 = 0;
    }
afterAnimation:

    Ov099_UpdateNodeActiveByMode(self, delta);
    Ov099_updateSubObjects(self);
}
