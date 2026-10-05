/* Ov022_BuildEffectSlots -- create the actor's effect contexts and load its
 * effect slots.
 *
 * The three effect pairs are cleared (no context, handle -1) with their two
 * bytes. The slot table is reset and the main effect context is
 * instantiated from its parameter block. Under flag bit 16 the second
 * context is instantiated instead of, without it and with global bit 2 set,
 * slot 4 being loaded from its block and the magic sequence registered. In
 * mode 0xf the third context is instantiated too. Then the named effects
 * are loaded as slots 1 (haziki, kind 4 for actor kinds 2 and 7, else 2), 2
 * (critical, kind 4 for actor kind 2) and, under global bit 2, 3 (dead,
 * kind 1). The track count is cleared and the charge started.
 */

#include "nitro/types.h"

#define FLAG_BIT16 (1 << 16)
#define GLOBAL_BIT2 0x4
#define MODE_SPECIAL 0xf
#define SLOT_MAGIC 4
#define SLOT_HAZIKI 1
#define SLOT_CRITICAL 2
#define SLOT_DEAD 3
#define KIND_DEFAULT 2
#define KIND_ALT 4
#define KIND_DEAD 1
#define ACTOR_KIND_2 2
#define ACTOR_KIND_7 7

/* Ov022SlotInitParams */
struct SlotInitParams {
    char *pszResourcePath;       /* 0x00 */
    int nResourceKind;           /* 0x04 */
    int aReserved[3];            /* 0x08 */
};

/* Ov022Actor */
struct Actor {
    u32 nFlagsLo;                /* 0x0000 */
    u32 nFlagsHi;                /* 0x0004 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[2];
    int nKind;                   /* 0x000c */
    u8 pad0010[0x7a8];
    void *pEffectA;              /* 0x07b8 */
    int nEffectB;                /* 0x07bc */
    void *pEffectC;              /* 0x07c0 */
    int nEffectD;                /* 0x07c4 */
    void *pEffectE;              /* 0x07c8 */
    int nEffectF;                /* 0x07cc */
    u8 bEffect18;                /* 0x07d0 */
    u8 bEffect19;                /* 0x07d1 */
    u8 pad07d2[0x10a];
    u16 nTrackCount;             /* 0x08dc */
    u8 pad08de[0x1d6a];
    void *aSlots[1];             /* 0x2648 */
};

extern const struct SlotInitParams data_ov022_020b2604;   /* the main effect context */
extern const struct SlotInitParams data_ov022_020b2618;   /* the second effect context */
extern const struct SlotInitParams data_ov022_020b262c;   /* the magic slot */
extern const struct SlotInitParams data_ov022_020b2640;   /* the third effect context */
extern u8 data_ov022_020b2930[];            /* the effect context class */
extern u8 data_0204c240;
extern char gOv022BaEfMgPackPath_2[];          /* "ba/ef/mg.p.z" */
extern char gOv022StrFmt[];          /* "%s" */
extern char gOv022BaEfHazikiPackPath[];          /* "ba/ef/haziki.p.z" */
extern char gOv022BaEfCriticalPackPath[];          /* "ba/ef/critical.p.z" */
extern char gOv022BaEfDeadPackPath[];          /* "ba/ef/dead.p.z" */

extern void Ov022_AcquireSlotBlock(void **papSlots);                                /* Ov022_AcquireSlotBlock */
extern void *InstantiateClass(u8 *pClass, struct SlotInitParams *pParams);         /* InstantiateClass */
extern void Ov022_AllocateSlotWithClass(void **papSlots, int nId, int nIndex, struct SlotInitParams *pParams);   /* Ov022_AllocateSlotWithClass */
extern void Ov022_RegisterSequence(struct Actor *pActor, char *pszDescriptor);      /* Ov022_RegisterSequence */
extern int Ov002_GetSlotTableByte(int nSlot);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov022_StartCharge(struct Actor *pActor);                          /* Ov022_StartCharge */

void Ov022_BuildEffectSlots(struct Actor *pActor)
{
    char szName[0x80];
    struct SlotInitParams params;
    struct SlotInitParams paramsMain;
    struct SlotInitParams paramsSecond;
    struct SlotInitParams paramsMagic;
    struct SlotInitParams paramsThird;

    pActor->pEffectA = 0;
    pActor->pEffectC = 0;
    pActor->pEffectE = 0;
    pActor->nEffectB = -1;
    pActor->nEffectD = -1;
    pActor->nEffectF = -1;
    pActor->bEffect18 = 0;
    pActor->bEffect19 = 0;
    Ov022_AcquireSlotBlock(pActor->aSlots);
    paramsMain = data_ov022_020b2604;
    pActor->pEffectA = InstantiateClass(data_ov022_020b2930, &paramsMain);
    if ((pActor->nFlagsLo & FLAG_BIT16) != 0) {
        paramsSecond = data_ov022_020b2618;
        pActor->pEffectC = InstantiateClass(data_ov022_020b2930, &paramsSecond);
    } else if ((data_0204c240 & GLOBAL_BIT2) != 0) {
        paramsMagic = data_ov022_020b262c;
        Ov022_AllocateSlotWithClass(pActor->aSlots, pActor->nId, SLOT_MAGIC, &paramsMagic);
        Ov022_RegisterSequence(pActor, gOv022BaEfMgPackPath_2);
    }
    if (Ov002_GetSlotTableByte(0) == MODE_SPECIAL) {
        paramsThird = data_ov022_020b2640;
        pActor->pEffectE = InstantiateClass(data_ov022_020b2930, &paramsThird);
    }
    params.pszResourcePath = szName;
    OS_SPrintf(szName, gOv022StrFmt, gOv022BaEfHazikiPackPath);
    params.nResourceKind = KIND_DEFAULT;
    switch (pActor->nKind) {
    case ACTOR_KIND_2:
        params.nResourceKind = KIND_ALT;
        break;
    case ACTOR_KIND_7:
        params.nResourceKind = KIND_ALT;
        break;
    }
    Ov022_AllocateSlotWithClass(pActor->aSlots, pActor->nId, SLOT_HAZIKI, &params);
    OS_SPrintf(szName, gOv022StrFmt, gOv022BaEfCriticalPackPath);
    params.nResourceKind = KIND_DEFAULT;
    if (pActor->nKind == ACTOR_KIND_2) {
        params.nResourceKind = KIND_ALT;
    }
    Ov022_AllocateSlotWithClass(pActor->aSlots, pActor->nId, SLOT_CRITICAL, &params);
    if ((data_0204c240 & GLOBAL_BIT2) != 0) {
        OS_SPrintf(szName, gOv022StrFmt, gOv022BaEfDeadPackPath);
        params.nResourceKind = KIND_DEAD;
        Ov022_AllocateSlotWithClass(pActor->aSlots, pActor->nId, SLOT_DEAD, &params);
    }
    pActor->nTrackCount = 0;
    Ov022_StartCharge(pActor);
}
