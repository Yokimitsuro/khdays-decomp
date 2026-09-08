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

typedef unsigned char u8;

/* Ov022Actor */
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
extern const char data_ov022_020b2d40[];

extern void OS_SPrintf(char *pBuf, const char *pFmt, ...);
extern void *func_02024ee8(const char *pPath, int nKind);
extern void func_02024fd4(void *pContainer);
extern unsigned int func_020358f4(int nId, int nKey);
extern void func_ov022_02097bd8(struct Actor *pActor);
extern int func_ov022_0209fc78(struct Actor *pActor, int nMask);
extern void func_ov022_02092658(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void func_ov022_02092880(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void func_ov022_02092a14(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void func_ov022_02092e8c(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void func_ov022_02093f94(void *pEffect, unsigned int nParam,
                                struct Actor *pActor);
extern void func_ov022_02093b68(void *pReaction);
extern void func_ov022_020901d4(void *pPool, struct Actor *pActor);
extern void func_ov022_02094c70(void *pOwner, struct Actor *pActor, int nArg);

#define CONTAINER_KIND 6
#define ANY_SLOT (-1)

#define PARAM_TRAIL 0x15
#define PARAM_POSE 0x10
#define PARAM_WIND 0x25
#define PARAM_SPARK 0x22
#define PARAM_ARM 0x28

void func_ov022_0209cda8(struct Actor *pActor)
{
    char szPath[128];
    const char *pName;

    pName = data_02042a70[pActor->nModelId];
    OS_SPrintf(szPath, data_ov022_020b2d40, pName);
    pActor->pContainer = func_02024ee8(szPath, CONTAINER_KIND);
    func_ov022_02097bd8(pActor);
    if (func_ov022_0209fc78(pActor, ANY_SLOT) != 0) {
        func_ov022_02092658(pActor->trail,
                            func_020358f4(pActor->nId, PARAM_TRAIL), pActor);
    }
    func_ov022_02092880(pActor->pose,
                        func_020358f4(pActor->nId, PARAM_POSE), pActor);
    func_ov022_02092a14(pActor->wind,
                        func_020358f4(pActor->nId, PARAM_WIND), pActor);
    func_ov022_02092e8c(pActor->spark,
                        func_020358f4(pActor->nId, PARAM_SPARK), pActor);
    func_ov022_02093f94(pActor->arm,
                        func_020358f4(pActor->nId, PARAM_ARM), pActor);
    func_02024fd4(pActor->pContainer);
    func_ov022_02093b68(pActor->reaction);
    func_ov022_020901d4(pActor->pool, pActor);
    func_ov022_02094c70(pActor->owner, pActor, 0);
}
