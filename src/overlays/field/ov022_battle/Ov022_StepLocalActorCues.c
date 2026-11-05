/* Ov022_StepLocalActorCues -- per-frame cues of the local player's actor.
 *
 * Only an actor whose draw is suppressed does any of this. When it is the
 * local player's: with hit reaction 0x2e and a kind id, a still-free spawn
 * handle and flag bit 48 set, it spawns its kind at its aim point (flag 1 on
 * the spawn unless the actor's own bit 16 is set) and keeps the handle;
 * otherwise a live handle gets the aim written through, and a dead one is
 * dropped. Then each of seven high flag bits plays its voice cue, and the
 * shared cue step runs.
 *
 * The bit-16 test ANDs the 32-bit flag word with a 64-bit constant and
 * truncates: that is what puts the mask in a register (mov r1, #0x10000) and
 * the constant's zero half into the spawn-flag register, as the ROM has it.
 */

/* Ov022Actor */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Actor {
    u32 nFlags;                      /* 0x0000 */
    u8 pad0004[4];
    u8 nOwner;                       /* 0x0008 */
    u8 pad0009[0x45b];
    u64 nFlags2;                     /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;           /* 0x048c */
    u8 pad0498[0x1fc];
    u8 bSuppressDraw : 1;            /* 0x0694 bit 0 */
    u8 nRest694 : 7;
    u8 pad0695[0x27];
    int nHitReaction;                /* 0x06bc */
    u8 pad06c0[0xe8];
    short nKindId;                   /* 0x07a8 */
    u8 pad07aa[2];
    int hSpawn;                      /* 0x07ac */
};

#define REACTION_SPAWN 0x2e
#define FLAG_BIT16 (1ULL << 16)     /* a 64-bit flag constant tested on the low word */
#define BIT48 (1ULL << 48)
#define BIT45 (1ULL << 45)
#define BIT44 (1ULL << 44)
#define BIT54 (1ULL << 54)
#define BIT56 (1ULL << 56)
#define BIT60 (1ULL << 60)
#define BIT57 (1ULL << 57)
#define BIT58 (1ULL << 58)

extern int Session_GetLocalPlayerIndex(void);
extern int Slot_Spawn(int nKindId, int nCue, VecFx32 *pPos, unsigned int nFlags);
extern int SoundSeqHandle_IsActive(int hSpawn);
extern void Handle_WritePayloadIfLive(int hSpawn, VecFx32 *pPos);
extern void Ov022_PlayEntityVoice(struct Actor *pActor, int nSeqArc, int nSeq);
extern void Ov022_StepReactionCues(struct Actor *pActor);

void Ov022_StepLocalActorCues(struct Actor *pActor)
{
    u16 nSpawnFlags;

    if (pActor->bSuppressDraw == 0) {
        return;
    }
    if (pActor->nOwner == Session_GetLocalPlayerIndex()) {
        if (pActor->nHitReaction == REACTION_SPAWN) {
            if (pActor->nKindId >= 0 && pActor->hSpawn == 0
                && (pActor->nFlags2 & BIT48) != 0) {
                nSpawnFlags = 0;
                if ((u32)(pActor->nFlags & FLAG_BIT16) == 0) {
                    nSpawnFlags |= 1;
                }
                pActor->hSpawn = Slot_Spawn(pActor->nKindId, 0, &pActor->vecAim, nSpawnFlags);
            }
        } else if (pActor->hSpawn != 0) {
            if (SoundSeqHandle_IsActive(pActor->hSpawn) != 0) {
                Handle_WritePayloadIfLive(pActor->hSpawn, &pActor->vecAim);
            } else {
                pActor->hSpawn = 0;
            }
        }
    }
    if ((pActor->nFlags2 & BIT45) != 0) {
        Ov022_PlayEntityVoice(pActor, 0, 0x40);
    }
    if ((pActor->nFlags2 & BIT44) != 0) {
        Ov022_PlayEntityVoice(pActor, 0, 0x3f);
    }
    if ((pActor->nFlags2 & BIT54) != 0) {
        Ov022_PlayEntityVoice(pActor, 0, 0x46);
    }
    if ((pActor->nFlags2 & BIT56) != 0) {
        Ov022_PlayEntityVoice(pActor, 0, 0x44);
    }
    if ((pActor->nFlags2 & BIT60) != 0) {
        Ov022_PlayEntityVoice(pActor, 0, 0x60);
    }
    if ((pActor->nFlags2 & BIT57) != 0) {
        Ov022_PlayEntityVoice(pActor, 0, 0x57);
    }
    if ((pActor->nFlags2 & BIT58) != 0) {
        Ov022_PlayEntityVoice(pActor, 0, 0x5f);
    }
    Ov022_StepReactionCues(pActor);
}
