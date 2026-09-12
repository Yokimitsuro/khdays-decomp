/* Ov022_StepReactionCues -- play the voice cues of the current hit reaction.
 *
 * The reaction's slot resources are released first. Nothing plays for a dead
 * actor, without a reaction, for a remote player without a target, or while
 * the animation request is busy. Reactions 0x17..0x19 need flag-2 bit 12 and
 * 0x1a flag-2 bit 13, else the cue set is dropped.
 *
 * With flag-2 bit 37 every entry whose frame has passed is marked done with
 * its voice dropped. Then every entry whose frame has come: one already done
 * follows its live voice to the actor's aim (or forgets a dead one) when the
 * cue names the actor's own voice; one not yet done picks a cue (its first,
 * or a random one) whose voice id, unless it is one of the actor's own ids or
 * 0, 2, 15, is replaced by the actor's handler id, and plays it.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022VoiceCue */
struct VoiceCue {
    u16 nVoice;                  /* 0x00 */
    u16 nArg;                    /* 0x02 */
};

/* Ov022CueEntry */
struct CueEntry {
    int nFrame;                  /* 0x00 */
    union {
        u8 nFlags;               /* 0x04 */
        struct {
            u8 nBit0 : 1;
            u8 bDone : 1;        /* bit 1 */
            u8 nRest : 6;
        } bits;
    } f;
    u8 nMode;                    /* 0x05 0: first cue, 1: random cue */
    u8 nCount;                   /* 0x06 */
    u8 pad07;
    int hVoice;                  /* 0x08 */
    struct VoiceCue *apCues[1];  /* 0x0c */
};

/* Ov022CueTable */
struct CueTable {
    u8 pad00;
    u8 nCount;                   /* 0x01 */
    u8 pad02[2];
    struct CueEntry **apEntries; /* 0x04 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x12];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0x450];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x70];
    int nReplayIndex;            /* 0x0508 */
    u8 pad050c[0x1b0];
    int nHitReaction;            /* 0x06bc */
    struct CueTable *apCueTables[54];     /* 0x06c0 by reaction */
    struct CueEntry *pCueEntries;         /* 0x0798 */
    void *pCueVoices;                     /* 0x079c */
    int nCueEntryCount;                   /* 0x07a0 */
    short nVoiceId;              /* 0x07a4 */
    short nHandlerId;            /* 0x07a6 */
    short nKindId;               /* 0x07a8 */
    short nVoiceArg;             /* 0x07aa */
    u8 pad07ac[4];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x5dc];
    u8 animReq[0x10];            /* 0x0d90 */
};

#define FLAG2_BIT12 (1ULL << 12)
#define FLAG2_BIT13 (1ULL << 13)
#define FLAG2_BIT37 (1ULL << 37)
#define CUE_DONE 0x2
#define CUE_MODE_FIRST 0
#define CUE_MODE_RANDOM 1
#define VOICE_NONE 0
#define VOICE_SKIP_2 2
#define VOICE_SKIP_15 0xf

extern void func_ov022_020a46f8(struct Actor *pActor, int nReaction);   /* Ov022_ReleaseNodeSlotResources */
extern int func_02030788(void);
extern int func_ov022_020b1b88(u8 *pAnimReq);
extern int func_02033ea0(int hVoice);
extern void func_02033e00(int hVoice, VecFx32 *pPos);
extern int func_02023e80(int nRange);                                   /* Rand16NextScaled */
extern int func_ov022_020a4490(struct Actor *pActor, int nVoice, int nArg);   /* Ov022_PlayEntityVoice */

void func_ov022_020a4238(struct Actor *pActor)
{
    struct CueTable *pTable;
    int nEntry;
    struct CueEntry *pEntry;
    struct VoiceCue *pCue;
    int nVoice;
    struct CueEntry *pDone;

    func_ov022_020a46f8(pActor, pActor->nHitReaction);
    if (pActor->nHp == 0) {
        return;
    }
    if (pActor->nHitReaction < 0) {
        return;
    }
    if (func_02030788() != 0 && pActor->nReplayIndex < 0) {
        return;
    }
    if (func_ov022_020b1b88(pActor->animReq) == 0) {
        return;
    }
    pTable = pActor->apCueTables[pActor->nHitReaction];
    switch (pActor->nHitReaction) {
    case 0x17:
    case 0x18:
    case 0x19:
        if ((pActor->nFlags2 & FLAG2_BIT12) == 0) {
            pTable = 0;
        }
        break;
    case 0x1a:
        if ((pActor->nFlags2 & FLAG2_BIT13) == 0) {
            pTable = 0;
        }
        break;
    }
    if (pTable == 0) {
        return;
    }
    if ((pActor->nFlags2 & FLAG2_BIT37) != 0) {
        for (nEntry = 0; nEntry < pTable->nCount; nEntry++) {
            pDone = pTable->apEntries[nEntry];
            if (pDone->nFrame < pActor->nAnimFrame) {
                pDone->f.nFlags |= CUE_DONE;
                pDone->hVoice = 0;
            }
        }
    }
    for (nEntry = 0; nEntry < pTable->nCount; nEntry++) {
        pEntry = pTable->apEntries[nEntry];
        pCue = 0;
        if (pEntry->nFrame <= pActor->nAnimFrame) {
            if (pEntry->f.bits.bDone) {
                if (pEntry->hVoice != 0 && pEntry->apCues[0]->nVoice == pActor->nVoiceId) {
                    if (func_02033ea0(pEntry->hVoice)) {
                        func_02033e00(pEntry->hVoice, &pActor->vecAim);
                    } else {
                        pEntry->hVoice = 0;
                    }
                }
            } else {
                switch (pEntry->nMode) {
                case CUE_MODE_FIRST:
                    pCue = pEntry->apCues[0];
                    break;
                case CUE_MODE_RANDOM:
                    pCue = pEntry->apCues[func_02023e80(pEntry->nCount)];
                    break;
                }
                if (pCue != 0) {
                    nVoice = pCue->nVoice;
                    if (nVoice != VOICE_NONE && nVoice != VOICE_SKIP_2 && nVoice != VOICE_SKIP_15
                        && nVoice != pActor->nVoiceId && nVoice != pActor->nKindId
                        && nVoice != pActor->nVoiceArg) {
                        nVoice = pActor->nHandlerId;
                    }
                    if (nVoice >= 0) {
                        pEntry->hVoice = func_ov022_020a4490(pActor, nVoice, pCue->nArg);
                        pEntry->f.nFlags |= CUE_DONE;
                    }
                }
            }
        }
    }
}
