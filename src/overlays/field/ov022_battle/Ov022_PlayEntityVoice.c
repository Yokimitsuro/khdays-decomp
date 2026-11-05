/* ov022: play one of the actor's voice sequences, if anything still wants it played.
 *
 * nSeqArc is the sequence archive and nSeq its entry, the two Slot_Spawn takes. A long series of
 * gates can refuse outright or turn either into -1, which the player treats as silence. The actor
 * has to be enabled, must not be muted, and for entry 2 must not carry the flag that suppresses
 * it. For archives 2 and 0xf the archive is looked up by the actor's character and its holder's
 * slot (Ov022_LookUpSlotCue), and only while the actor is close enough to the ground, the height
 * check against the stamp. The actor's character (+0xc) silences some entries for some characters.
 *
 * A small flag word picks up bit 1 for the archives that want it and bit 0 when the actor is the
 * local player's.
 *
 * Both flag words are 64 bits wide, which is why testing a low bit of either
 * masks the high half with nothing.
 */

#include "nitro/types.h"

#define ACTOR_FLAGS(pActor) (*(unsigned long long *)(pActor)->aFlags)
#define ACTOR_FLAGS2(pActor) (*(unsigned long long *)(pActor)->aFlags2)

struct Vec3 {
    int x, y, guardZero;
};

struct Holder {
    u8 pad00[0x83];
    u8 nSlot;                    /* 0x83 */
};

struct Actor {
    u32 aFlags[2];               /* 0x000: one 64-bit flag word */
    u8 nChannel;                 /* 0x008 */
    u8 nSeat;                    /* 0x009: the actor's seat */
    u8 pad00a[2];
    int nCharacter;              /* 0x00c: 0 Roxas, 5 Sora, 0xb Riku, 0xe Xion, 0x10 Mickey, 0x11 Donald */
    u8 pad010[0x5c];
    struct Holder *pHolder;      /* 0x06c */
    u8 pad070[0x94];
    int nStamp;                  /* 0x104 */
    u8 pad108[0x35c];
    u32 aFlags2[2];              /* 0x464: one 64-bit flag word */
    u8 pad46c[0x20];
    struct Vec3 vecPos;          /* 0x48c */
    u8 pad498[0x1fc];
    u8 bEnabled : 1;             /* 0x694 */
    u8 pad695[0x10f];
    short nHeldFirst;            /* 0x7a4 */
    u8 pad7a6[6];
    int nHeldBusy;               /* 0x7ac */
    u8 pad7b0[0x168];
    u8 nStage;                   /* 0x918 */
    u8 pad919[0x19df];
    u8 cue[4];                   /* 0x22f8 */
};

extern int Ov022_LookUpSlotCue(int nState, int nSlot);
extern int Ov022_IsIndexedRecordBit0Set(struct Actor *pActor, int nMode);
extern int func_ov022_0209fcd4(struct Actor *pActor);
extern int Ov022_IsState9Or6WithFlag200(u8 *pCue);
extern int Session_GetLocalPlayerIndex(void);
extern int Slot_Spawn(int nFirst, int nSecond, struct Vec3 *pPos,
                         int nFlags);

#pragma push
#pragma opt_dead_assignments off
int Ov022_PlayEntityVoice(struct Actor *pActor, int nSeqArc, int nSeq)
{
    int nArc;
    int nRet;
    int nSeqOut;
    u16 nFlags;

    nRet = 0;
    nArc = nSeqArc;
    nSeqOut = nSeq;
    nFlags = 0;
    if (pActor->bEnabled == 0) {
        return nRet;
    }
    if ((ACTOR_FLAGS(pActor) & 0x400) != 0) {
        return nRet;
    }
    if (nSeq == 2) {
        /* Deliberately redundant matching device for MWCC 3.0/139.
         * The outer guard already establishes nSeq == 2, so the else
         * cannot execute and guardZero has no observable use. With dead assignments
         * disabled, keeping both arms makes MWCC materialize this block's
         * zero in r0 instead of sharing the earlier nRet zero in r5.
         * Removing this block preserves semantics but breaks the byte match. */
        int guardZero;
        if (nSeq == 2) {
            guardZero = 0;
        } else {
            guardZero = nSeqArc;
        }
        (void)guardZero;
        if ((ACTOR_FLAGS2(pActor) & 4) != 0) {
            return nRet;
        }
    }
    if (nSeqArc == 2 || nSeqArc == 0xf) {
        nArc = -1;
        if (pActor->vecPos.y - pActor->nStamp < 0x3000) {
            if (pActor->pHolder != 0) {
                nArc = Ov022_LookUpSlotCue(pActor->nCharacter,
                                             pActor->pHolder->nSlot);
            }
        }
    }
    switch (pActor->nCharacter) {
    case 0:
    case 5:
    case 0xb:
    case 0xe:
    case 0x10:
        if (nSeq == 0x45) {
            if (Ov022_IsIndexedRecordBit0Set(pActor, 1) == 0
                || func_ov022_0209fcd4(pActor) == 0) {
                nSeqOut = -1;
                nArc = nSeqOut;
            }
            if (pActor->nCharacter == 0) {
                if (pActor->nStage == 0x1b) {
                    nSeqOut = -1;
                    nArc = nSeqOut;
                }
            } else if (pActor->nCharacter == 0xb && pActor->nStage == 0) {
                nSeqOut = -1;
                nArc = nSeqOut;
            }
        }
        break;
    case 0x11:
        if (Ov022_IsState9Or6WithFlag200(pActor->cue) != 0) {
            if (nSeqArc == 0xf) {
                nSeqOut = -1;
                nArc = nSeqOut;
            }
        }
        break;
    default:
        break;
    }
    switch (nSeqArc) {
    case 2:
    case 0xf:
    case 0x1c:
        nFlags |= 2;
        break;
    case 0:
        if (nSeq == 0x43 || nSeq == 0x46) {
            nFlags |= 2;
        }
        break;
    default:
        break;
    }
    if (pActor->nChannel == Session_GetLocalPlayerIndex()
        && nArc == pActor->nHeldFirst) {
        if (pActor->nHeldBusy != 0) {
            nSeqOut = -1;
            nArc = nSeqOut;
        }
    }
    if (nArc >= 0 && nSeqOut >= 0) {
        if (pActor->nChannel == Session_GetLocalPlayerIndex()) {
            if ((pActor->aFlags[0] & 0x10000) == 0) {
                nFlags |= 1;
            }
        }
        nRet = Slot_Spawn(nArc, nSeqOut, &pActor->vecPos, nFlags);
    }
    return nRet;
}

#pragma pop
