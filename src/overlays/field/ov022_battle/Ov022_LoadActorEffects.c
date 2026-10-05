/* Ov022_LoadActorEffects -- open an actor's effect container and build everything
 * that comes out of it.
 *
 * The container's path is spelled from the actor's model name, opened, and kept
 * on the actor while every effect that reads from it is set up: the trail only
 * when the actor still has a slot flagged, then the pose row, the wind, the
 * third effect block and the arm. Once they are all built the container is
 * closed, and what is left is bound and started: the reaction animations, the
 * slot pool and the action owner's run.
 */

/* Ov022Actor */

#include "nitro/types.h"

struct Actor {
    u8 pad0000[9];
    u8 nId;                          /* 0x0009 */
    u8 pad000a[2];
    int nModelId;                    /* 0x000c */
    u8 pad0010[0x1060];
    u8 trail[0x11c];                 /* 0x1070 */
    u8 pose[0xc];                    /* 0x118c */
    u8 wind[0x180];                  /* 0x1198 */
    u8 spark[0x974];                 /* 0x1318 */
    u8 arm[0x11c];                   /* 0x1c8c */
    u8 reaction[0x4e0];              /* 0x1da8 */
    u8 pool[0x70];                   /* 0x2288 */
    u8 owner[0x8d8];                 /* 0x22f8 */
    void *pContainer;                /* 0x2bd0 */
};

/* one path per model, indexed by the actor's model id */
extern const char *data_02042a70[];
extern const char gOv022BaChAbPathFmt[];

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(const char *pPath, int nKind);
extern void ZeroHalfThenFree(void *pContainer);
extern unsigned int Slot_EvalPackedParam(int nId, int nKey);
extern void Ov022_LoadEffectFiles(struct Actor *pActor);
extern int func_ov022_0209fc78(struct Actor *pActor, int nMask);
extern void Ov022_SetUpTrailEffect(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void func_ov022_02092880(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void Ov022_SetUpWindEffect(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void Ov022_SetUpDustEffect(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void Ov022_SetUpArmEffect(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void Ov022_BindReactionAnims(void *pReaction);
extern void Ov022_BuildSlotPool(void *pPool, struct Actor *pActor);
extern void Ov022_StartRun(void *pOwner, struct Actor *pActor, int nArg);

#define CONTAINER_KIND 6
#define ANY_SLOT (-1)

#define PARAM_TRAIL 0x15
#define PARAM_POSE 0x10
#define PARAM_WIND 0x25
#define PARAM_SPARK 0x22
#define PARAM_ARM 0x28

void Ov022_LoadActorEffects(struct Actor *pActor)
{
    char szPath[128];
    const char *pName;

    pName = data_02042a70[pActor->nModelId];
    OS_SPrintf(szPath, gOv022BaChAbPathFmt, pName);
    pActor->pContainer = Msg_OpenContainerAndReadHeader(szPath, CONTAINER_KIND);
    Ov022_LoadEffectFiles(pActor);
    if (func_ov022_0209fc78(pActor, ANY_SLOT) != 0) {
        Ov022_SetUpTrailEffect(pActor->trail,
                            Slot_EvalPackedParam(pActor->nId, PARAM_TRAIL), pActor);
    }
    func_ov022_02092880(pActor->pose,
                        Slot_EvalPackedParam(pActor->nId, PARAM_POSE), pActor);
    Ov022_SetUpWindEffect(pActor->wind,
                        Slot_EvalPackedParam(pActor->nId, PARAM_WIND), pActor);
    Ov022_SetUpDustEffect(pActor->spark,
                        Slot_EvalPackedParam(pActor->nId, PARAM_SPARK), pActor);
    Ov022_SetUpArmEffect(pActor->arm,
                        Slot_EvalPackedParam(pActor->nId, PARAM_ARM), pActor);
    ZeroHalfThenFree(pActor->pContainer);
    Ov022_BindReactionAnims(pActor->reaction);
    Ov022_BuildSlotPool(pActor->pool, pActor);
    Ov022_StartRun(pActor->owner, pActor, 0);
}
