/* Ov022_SpawnVoiceCue -- start the cue that goes with an actor's action.
 *
 * Nothing happens unless the actor belongs to the party the active entry does.
 * The cue itself comes from one of two tables of four, chosen by the actor's
 * model: one model has its own table, everything else shares the other and can
 * still move the cue on at the higher levels. One model's first cue also asks
 * for the second flag, and the local player asks for the first while it is
 * close enough to the point and not silenced.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct Actor {
    unsigned int nFlags;         /* 0x0000 */
    u8 pad0004[4];
    u8 nOwner;                   /* 0x0008 */
    u8 nId;                      /* 0x0009 */
    u8 pad000a[2];
    int nModelId;                /* 0x000c */
    u8 pad0010[0x47c];
    struct VecFx32 vecAim;       /* 0x048c */
    u8 pad0498[0x30e];
    short nHandlerId;            /* 0x07a6 */
};

struct CueSet {
    unsigned int aCues[4];
};

extern struct CueSet data_ov022_020b25c4;
extern struct CueSet data_ov022_020b25d4;

extern u16 func_01fffe14(void);
extern int func_ov022_02088474(unsigned int nId);
extern int func_02030788(void);
extern int func_01ff8e94(struct VecFx32 *pA, struct VecFx32 *pB);
extern void func_02033d0c(int nHandlerId, unsigned int nCue,
                          struct VecFx32 *pPos, u16 nFlags);

#define ACTOR_SILENCED 0x10000
#define CUE_NEAR 1
#define CUE_SECOND 2
#define NEAR_RANGE 0x2000

#define MODEL_OWN_TABLE 2
#define MODEL_SHIFTED 0x13
#define MODEL_FIXED 0xf
#define MODEL_FLAGGED 3

void func_ov022_020a48c8(struct Actor *pActor, int nIndex,
                         struct VecFx32 *pPos, int nLevel)
{
    struct CueSet setOwn;
    struct CueSet setShared;
    unsigned int nCue;
    short nHandlerId;
    u16 nFlags;
    int nModelId;

    nHandlerId = pActor->nHandlerId;
    nFlags = 0;
    if (func_ov022_02088474(func_01fffe14())
        != func_ov022_02088474(pActor->nId)) {
        return;
    }
    nModelId = pActor->nModelId;
    if (nModelId == MODEL_OWN_TABLE) {
        setOwn = data_ov022_020b25c4;
        nCue = setOwn.aCues[nIndex];
    } else {
        setShared = data_ov022_020b25d4;
        nCue = setShared.aCues[nIndex];
        if (nLevel >= 2) {
            if (nModelId == MODEL_SHIFTED) {
                nCue = nCue + 0xe;
            } else if (nModelId == MODEL_FIXED) {
                nCue = 0xa;
            }
        }
        if (nModelId == MODEL_FLAGGED && nIndex == 0) {
            nFlags |= CUE_SECOND;
        }
    }
    if (pActor->nOwner == func_02030788()
        && (pActor->nFlags & ACTOR_SILENCED) == 0
        && func_01ff8e94(&pActor->vecAim, pPos) <= NEAR_RANGE) {
        nFlags = nFlags | CUE_NEAR;
    }
    if (nHandlerId >= 0) {
        func_02033d0c(nHandlerId, nCue, pPos, nFlags);
    }
}
