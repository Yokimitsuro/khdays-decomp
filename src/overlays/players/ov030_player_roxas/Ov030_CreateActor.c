/* Constructor for the ov030 actor. Same routine as the ov031 panel-class
 * constructor and built on the same helpers, but with its own tuning: an open
 * limit of 0xf00, a THREE-WAY name choice -- the config's nameGroup picks the
 * family and, inside group 0, alternateName picks between two members -- a
 * ten-entry handler table, and a fourth flag raised when story flag 0x208a is
 * set. The five bone lookups are the family's usual inline: a rig of zero
 * yields -1 rather than being passed on.
 */

#include "nitro/types.h"
#include "game/engine.h"

struct PanelInitConfig {
    int objectType;                         /* 0x00 */
    int slotId;                             /* 0x04 */
    u8 bitIndex;                            /* 0x08 */
    u8 pad09[3];
    int enableLowFlag;                      /* 0x0c */
    int enableMidFlag;                      /* 0x10 */
    int enableHighFlag;                     /* 0x14 */
    int alternateName;                      /* 0x18 */
    int nameGroup;                          /* 0x1c */
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

extern void Ov030_ApplyModeChange(void);
extern void Ov030_CommitScrollForFrame(void);
extern void Ov030_TickExtraClass(void);
extern void Ov030_SubmitPanel(void);
extern void Ov030_CueForKind(void);
extern void Ov030_HandleMessage(void);
extern void Ov030_BuildActorHandles(void);
extern void Ov030_ForwardGlobalCtx2cb0(void);

extern void *data_ov030_020b5a00;
extern const char gOv030StrFmt[];
extern const char gOv030RoxasDefPackPath[];
extern const char gOv030RoxasDefHbPackPath[];
extern const char gOv030RoxasDefHhoPackPath[];
extern int gOv030RoxasTgName;
extern int gOv030RoWTgRName;
extern int gOv030RoWTgLName;
extern int gOv030RoxasRName;
extern int gOv030Bip01Name;

void Ov030_CreateActor(struct PanelInitConfig *config)
{
    struct Ov044OpenParams params;
    char name[0x80];
    char *object = (char *)NNSi_FndGetCurrentRootHeap();
    int bone;

    data_ov030_020b5a00 = object;
    object[9] = (char)config->objectType;
    object[0x4bc] = (char)config->slotId;
    object[8] = config->bitIndex;
    *(int *)(object + 0xc) = 0;
    *(long long *)object = 0;

    params.enabled = 1;
    params.scale = 9 << 8;
    params.limit = 0xf << 8;
    Entity_ForwardToSlot(*(signed char *)(object + 0x4bc), (u16)(1 << *(u8 *)(object + 8)), 0,
                         &params, 0);

    switch (config->nameGroup) {
    case 0:
        if (config->alternateName == 0) {
            OS_SPrintf(name, gOv030StrFmt, gOv030RoxasDefPackPath);
        } else {
            OS_SPrintf(name, gOv030StrFmt, gOv030RoxasDefHbPackPath);
        }
        break;
    case 1:
        OS_SPrintf(name, gOv030StrFmt, gOv030RoxasDefHhoPackPath);
        break;
    }

    TailForwardTrackEntry(*(signed char *)(object + 0x4bc), name, 1,
                  config->objectType + 7);

    *(void **)(object + 0x664 + 0x00) = (void *)&Ov030_ApplyModeChange;
    *(void **)(object + 0x664 + 0x04) = (void *)&Ov030_CommitScrollForFrame;
    *(void **)(object + 0x664 + 0x08) = (void *)&Ov030_TickExtraClass;
    *(void **)(object + 0x664 + 0x0c) = 0;
    *(void **)(object + 0x664 + 0x10) = 0;
    *(void **)(object + 0x664 + 0x14) = (void *)&Ov030_SubmitPanel;
    *(void **)(object + 0x664 + 0x18) = (void *)&Ov030_CueForKind;
    *(void **)(object + 0x664 + 0x20) = (void *)&Ov030_HandleMessage;
    *(void **)(object + 0x664 + 0x28) = (void *)&Ov030_BuildActorHandles;
    *(void **)(object + 0x664 + 0x24) = (void *)&Ov030_ForwardGlobalCtx2cb0;

    Actor_InitEntityLink(object + 0x20,
                  ArrayEntryPtrD0(*(signed char *)(object + 0x4bc)));

    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x520) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv030RoxasTgName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x518) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv030RoWTgRName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x514) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv030RoWTgLName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x51c) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv030RoxasRName) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x524) = bone != 0
        ? NNS_G3dGetResDictIdxByName((void *)bone, &gOv030Bip01Name) : -1;

    if (config->enableLowFlag != 0) {
        *(long long *)object |= 0x20;
    }
    if (config->enableMidFlag != 0) {
        *(long long *)object |= 0x10000;
    }
    if (config->enableHighFlag != 0) {
        *(long long *)object |= 0x1000000000LL;
    }
    if (GameState_IsFlagSet(0x208a) != 0) {
        *(long long *)object |= 0x8000000000LL;
    }
    Ov022_InitActor(object);
}
