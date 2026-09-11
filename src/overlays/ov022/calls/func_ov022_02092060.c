/* Ov022_PlaySpawnRecord -- start the effect a spawn record describes and cue
 * its sounds.
 *
 * The record is dispatched on the actor's effect context at its position and
 * angle; a record the context refuses ends here. The slot it got takes the
 * record's value, then the record's kind decides the slot short and the voice
 * cue: kind 0 sends the cue (only its low bit for model 15) and, unless the
 * record is silent, voices 0 or 1 by the cue's low bit; kind 1 sends 0 and
 * voices 2; kind 2 sends 0 and voices 3 unless the cue is 7; kind 5 sends the
 * cue and voices by model (3 for models 2 and 8, 1 for model 18, with a peer
 * hit 0xc5/2 for model 2 on cue 1); kind 8 sends 1. A record flagged for it
 * finally notifies the peer with its hit id and argument.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ControlRecord */
struct ControlRecord {
    struct VecFx32 vecPos;           /* 0x00 */
    short nValue;                    /* 0x0c */
    u16 nAngle;                      /* 0x0e */
    u32 nOwner : 2;                  /* 0x10 bits 0-1: entry index */
    u32 nCue : 3;                    /*      bits 2-4 */
    u32 nKind : 4;                   /*      bits 5-8 */
    u32 bNotify : 1;                 /*      bit 9 */
    u32 bSilent : 1;                 /*      bit 10 */
    u32 nHitId : 12;                 /*      bits 11-22 */
    u32 nHitArg : 8;                 /*      bits 23-30 */
    u32 nTop : 1;                    /*      bit 31 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0xc];
    int nModelId;                    /* 0x000c */
};

#define MODEL_LOW_CUE 0xf
#define MODEL_2 2
#define MODEL_8 8
#define MODEL_18 0x12
#define CUE_NONE 7
#define PEER_HIT_ID 0xc5
#define PEER_HIT_ARG 2

extern int func_ov022_020893f4(int nContext, struct VecFx32 *pAt, int nAngle);
extern void func_ov022_0208956c(int nContext, int nSlot, int nValue);
extern void func_ov022_020894a0(int nContext, int nSlot, int nValue);
extern void func_ov022_020a48c8(struct Actor *pActor, int nIndex,
                                struct VecFx32 *pPos, int nLevel);
extern void func_ov022_020922a4(struct Actor *pActor, struct VecFx32 *pPos,
                                unsigned int nId, unsigned int nArg);

void func_ov022_02092060(struct Actor *pActor, int nContext,
                         struct ControlRecord *pRec)
{
    int nSlot;
    int nCue;

    nSlot = func_ov022_020893f4(nContext, &pRec->vecPos, pRec->nAngle);
    if (nSlot < 0) {
        return;
    }
    func_ov022_0208956c(nContext, nSlot, pRec->nValue);
    switch (pRec->nKind) {
    case 0:
        nCue = pRec->nCue;
        if (pActor->nModelId == MODEL_LOW_CUE) {
            nCue &= 1;
        }
        func_ov022_020894a0(nContext, nSlot, nCue);
        if (!pRec->bSilent) {
            if ((pRec->nCue & 1) == 0) {
                func_ov022_020a48c8(pActor, 0, &pRec->vecPos, pRec->nCue);
            } else {
                func_ov022_020a48c8(pActor, 1, &pRec->vecPos, pRec->nCue);
            }
        }
        break;
    case 1:
        func_ov022_020894a0(nContext, nSlot, 0);
        if (!pRec->bSilent) {
            func_ov022_020a48c8(pActor, 2, &pRec->vecPos, pRec->nCue);
        }
        break;
    case 8:
        func_ov022_020894a0(nContext, nSlot, 1);
        break;
    case 2:
        func_ov022_020894a0(nContext, nSlot, 0);
        if (!pRec->bSilent && pRec->nCue != CUE_NONE) {
            func_ov022_020a48c8(pActor, 3, &pRec->vecPos, pRec->nCue);
        }
        break;
    case 5:
        func_ov022_020894a0(nContext, nSlot, pRec->nCue);
        if (!pRec->bSilent) {
            switch (pActor->nModelId) {
            case MODEL_18:
                func_ov022_020a48c8(pActor, 1, &pRec->vecPos, 0);
                break;
            case MODEL_8:
                func_ov022_020a48c8(pActor, 3, &pRec->vecPos, 0);
                break;
            case MODEL_2:
                func_ov022_020a48c8(pActor, 3, &pRec->vecPos, 0);
                if (pRec->nCue == 1) {
                    func_ov022_020922a4(pActor, &pRec->vecPos, PEER_HIT_ID, PEER_HIT_ARG);
                }
                break;
            }
        }
        break;
    }
    if (pRec->bNotify) {
        func_ov022_020922a4(pActor, &pRec->vecPos, pRec->nHitId, pRec->nHitArg);
    }
}
