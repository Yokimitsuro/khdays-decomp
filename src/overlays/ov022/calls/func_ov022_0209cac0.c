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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
extern char data_ov022_020b2cf4[];          /* "ba/ef/mg.p.z" */
extern char data_ov022_020b2d04[];          /* "%s" */
extern char data_ov022_020b2d08[];          /* "ba/ef/haziki.p.z" */
extern char data_ov022_020b2d1c[];          /* "ba/ef/critical.p.z" */
extern char data_ov022_020b2d30[];          /* "ba/ef/dead.p.z" */

extern void func_ov022_02092320(void **papSlots);                                /* Ov022_AcquireSlotBlock */
extern void *func_02023930(u8 *pClass, struct SlotInitParams *pParams);         /* InstantiateClass */
extern void func_ov022_02092384(void **papSlots, int nId, int nIndex, struct SlotInitParams *pParams);   /* Ov022_AllocateSlotWithClass */
extern void func_ov022_0209d1d8(struct Actor *pActor, char *pszDescriptor);      /* Ov022_RegisterSequence */
extern int func_ov002_02072754(int nSlot);
extern void OS_SPrintf(char *pszOut, char *pszFormat, char *pszName);
extern void func_ov022_0209adfc(struct Actor *pActor);                          /* Ov022_StartCharge */

void func_ov022_0209cac0(struct Actor *pActor)
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
    func_ov022_02092320(pActor->aSlots);
    paramsMain = data_ov022_020b2604;
    pActor->pEffectA = func_02023930(data_ov022_020b2930, &paramsMain);
    if ((pActor->nFlagsLo & FLAG_BIT16) != 0) {
        paramsSecond = data_ov022_020b2618;
        pActor->pEffectC = func_02023930(data_ov022_020b2930, &paramsSecond);
    } else if ((data_0204c240 & GLOBAL_BIT2) != 0) {
        paramsMagic = data_ov022_020b262c;
        func_ov022_02092384(pActor->aSlots, pActor->nId, SLOT_MAGIC, &paramsMagic);
        func_ov022_0209d1d8(pActor, data_ov022_020b2cf4);
    }
    if (func_ov002_02072754(0) == MODE_SPECIAL) {
        paramsThird = data_ov022_020b2640;
        pActor->pEffectE = func_02023930(data_ov022_020b2930, &paramsThird);
    }
    params.pszResourcePath = szName;
    OS_SPrintf(szName, data_ov022_020b2d04, data_ov022_020b2d08);
    params.nResourceKind = KIND_DEFAULT;
    switch (pActor->nKind) {
    case ACTOR_KIND_2:
        params.nResourceKind = KIND_ALT;
        break;
    case ACTOR_KIND_7:
        params.nResourceKind = KIND_ALT;
        break;
    }
    func_ov022_02092384(pActor->aSlots, pActor->nId, SLOT_HAZIKI, &params);
    OS_SPrintf(szName, data_ov022_020b2d04, data_ov022_020b2d1c);
    params.nResourceKind = KIND_DEFAULT;
    if (pActor->nKind == ACTOR_KIND_2) {
        params.nResourceKind = KIND_ALT;
    }
    func_ov022_02092384(pActor->aSlots, pActor->nId, SLOT_CRITICAL, &params);
    if ((data_0204c240 & GLOBAL_BIT2) != 0) {
        OS_SPrintf(szName, data_ov022_020b2d04, data_ov022_020b2d30);
        params.nResourceKind = KIND_DEAD;
        func_ov022_02092384(pActor->aSlots, pActor->nId, SLOT_DEAD, &params);
    }
    pActor->nTrackCount = 0;
    func_ov022_0209adfc(pActor);
}
