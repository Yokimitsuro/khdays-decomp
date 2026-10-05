/* Initialises the player actor from its configuration: model, bones and named resources, entity
 * links, and its handler table. */

#include "nitro/types.h"
#include "game/engine.h"

struct Ov044InitConfig {
    int objectType;
    int slotId;
    u8 bitIndex;
    u8 pad09[3];
    int enableLowFlag;
    int enableMidFlag;
    int enableHighFlag;
    int alternateName;
    int nameGroup;
};

struct Ov044OpenParams {
    int enabled;
    int limit;
    int scale;
    int unused0c;
    int unused10;
};

struct Ov044RigHeader {
    int pad0;
    int rig;
};

static inline int Ov044_GetBoneBase(char *object)
{
    int rig = ((struct Ov044RigHeader *)(
        *(int *)(object + 0x20) + 0x24))->rig;
    return rig != 0 ? rig + 0x40 : 0;
}

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int NNS_G3dGetResDictIdxByName(void *, void *);
extern void Ov022_InitActor(void *);

extern void Ov044_ApplyModeChange(void);
extern void Ov044_CommitScrollForFrame(void);
extern void Ov044_tailDispatch(void);
extern void Ov044_ReloadSceneResources(void);
extern void Ov044_MapSlotKindToAnim(void);
extern void Ov044_BeginActionStep(void);
extern void Ov044_SetupBuildBlock(void);
extern void Ov044_ForwardArmPlayerTarget(void);

extern void *data_ov044_020b5620;
extern const char gOv044StrFmt[];
extern const char gOv044XionDefHPackPath[];
extern const char gOv044XionDefPackPath[];
extern const char gOv044XionDefHhPackPath[];
extern const char gOv044XionDefHoPackPath[];
extern int gOv044XionTgName;
extern int gOv044XoHRName;
extern int gOv044XionName;
extern int gOv044Bip01Name;

void Ov044_InitPanelObject(struct Ov044InitConfig *config)
{
    char name[128];
    struct Ov044OpenParams params;
    char *object = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int bone;
    int nameGroup;
    int alternateName;

    data_ov044_020b5620 = object;
    object[9] = (char)config->objectType;
    object[0x4bc] = (char)config->slotId;
    object[8] = config->bitIndex;
    *(int *)(object + 0xc) = 0xe;
    *(long long *)object = 0;

    params.enabled = 1;
    params.scale = 9 << 8;
    params.limit = 0xf << 8;
    Entity_ForwardToSlot(*(signed char *)(object + 0x4bc), (u16)(1 << *(u8 *)(object + 8)), 0,
                         &params, 0);

    nameGroup = config->nameGroup;
    alternateName = config->alternateName;
    switch (nameGroup) {
    case 0:
        if (alternateName != 0) {
            OS_SPrintf(name, gOv044StrFmt, gOv044XionDefHPackPath);
        } else {
            OS_SPrintf(name, gOv044StrFmt, gOv044XionDefPackPath);
        }
        break;
    case 1:
        if (alternateName != 0) {
            OS_SPrintf(name, gOv044StrFmt, gOv044XionDefHhPackPath);
        } else {
            OS_SPrintf(name, gOv044StrFmt, gOv044XionDefHoPackPath);
        }
        break;
    }

    TailForwardTrackEntry(*(signed char *)(object + 0x4bc), name, 1,
                  config->objectType + 7);

    *(void **)(object + 0x664 + 0x00) = (void *)&Ov044_ApplyModeChange;
    *(void **)(object + 0x664 + 0x04) = (void *)&Ov044_CommitScrollForFrame;
    *(void **)(object + 0x664 + 0x08) = (void *)&Ov044_tailDispatch;
    *(void **)(object + 0x664 + 0x0c) = 0;
    *(void **)(object + 0x664 + 0x10) = 0;
    *(void **)(object + 0x664 + 0x14) = (void *)&Ov044_ReloadSceneResources;
    *(void **)(object + 0x664 + 0x18) = (void *)&Ov044_MapSlotKindToAnim;
    *(void **)(object + 0x664 + 0x20) = (void *)&Ov044_BeginActionStep;
    *(void **)(object + 0x664 + 0x28) = (void *)&Ov044_SetupBuildBlock;
    *(void **)(object + 0x664 + 0x24) = (void *)&Ov044_ForwardArmPlayerTarget;

    Actor_InitEntityLink(object + 0x20,
                  ArrayEntryPtrD0(*(signed char *)(object + 0x4bc)));

    i = 0;
    goto test;
body:
    *(int *)(object + i * sizeof(int) + 0x514) = -1;
    i++;
test:
    if (i < 5) {
        goto body;
    }

    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x520) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv044XionTgName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x518) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv044XoHRName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x51c) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv044XionName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x524) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv044Bip01Name) : -1;

    if (config->enableLowFlag != 0) {
        *(long long *)object |= 0x20;
    }
    if (config->enableMidFlag != 0) {
        *(long long *)object |= 0x10000;
    }
    if (config->enableHighFlag != 0) {
        *(long long *)object |= 0x1000000000LL;
    }
    Ov022_InitActor(object);
}
