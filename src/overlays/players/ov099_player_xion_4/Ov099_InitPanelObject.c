/* Initialises the player actor from its configuration: model, bones and named resources, entity
 * links, and its handler table. */

#include "nitro/types.h"
#include "game/engine.h"

struct PanelInitConfig {
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

extern void Ov099_ApplyModeChange(void);
extern void Ov099_CommitScrollForFrame(void);
extern void Ov099_tailDispatch(void);
extern void Ov099_ReloadSceneResources(void);
extern void Ov099_MapSlotKindToAnim(void);
extern void Ov099_BeginActionStep(void);
extern void Ov099_SetupBuildBlock(void);
extern void Ov099_ForwardArmPlayerTarget(void);

extern void *data_ov099_020bcbc0;
extern const char gOv099StrFmt[];
extern const char gOv099XionDefHPackPath[];
extern const char gOv099XionDefPackPath[];
extern const char gOv099XionDefHhPackPath[];
extern const char gOv099XionDefHoPackPath[];
extern int gOv099XionTgName;
extern int gOv099XoHRName;
extern int gOv099XionRName;
extern int gOv099Bip01Name;

void Ov099_InitPanelObject(struct PanelInitConfig *config)
{
    char name[128];
    struct Ov044OpenParams params;
    char *object = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int bone;
    int nameGroup;
    int alternateName;

    data_ov099_020bcbc0 = object;
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
            OS_SPrintf(name, gOv099StrFmt, gOv099XionDefHPackPath);
        } else {
            OS_SPrintf(name, gOv099StrFmt, gOv099XionDefPackPath);
        }
        break;
    case 1:
        if (alternateName != 0) {
            OS_SPrintf(name, gOv099StrFmt, gOv099XionDefHhPackPath);
        } else {
            OS_SPrintf(name, gOv099StrFmt, gOv099XionDefHoPackPath);
        }
        break;
    }

    TailForwardTrackEntry(*(signed char *)(object + 0x4bc), name, 1,
                  config->objectType + 7);

    *(void **)(object + 0x664 + 0x00) = (void *)&Ov099_ApplyModeChange;
    *(void **)(object + 0x664 + 0x04) = (void *)&Ov099_CommitScrollForFrame;
    *(void **)(object + 0x664 + 0x08) = (void *)&Ov099_tailDispatch;
    *(void **)(object + 0x664 + 0x0c) = 0;
    *(void **)(object + 0x664 + 0x10) = 0;
    *(void **)(object + 0x664 + 0x14) = (void *)&Ov099_ReloadSceneResources;
    *(void **)(object + 0x664 + 0x18) = (void *)&Ov099_MapSlotKindToAnim;
    *(void **)(object + 0x664 + 0x20) = (void *)&Ov099_BeginActionStep;
    *(void **)(object + 0x664 + 0x28) = (void *)&Ov099_SetupBuildBlock;
    *(void **)(object + 0x664 + 0x24) = (void *)&Ov099_ForwardArmPlayerTarget;

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
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv099XionTgName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x518) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv099XoHRName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x51c) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv099XionRName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x524) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv099Bip01Name) : -1;

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
