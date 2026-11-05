/* Constructs the ov107 status-effect node: base-init via 020c2a9c, set flag bit 2, install its
 * callbacks, look up its table entry, create two effect groups, reset three child lists, then
 * load the burn/frost/shock effect models plus one more, attach each to the second group and
 * point each back at this node. */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

typedef void (*Callback)(void);

typedef struct List28 { int w[10]; } List28; /* initialised by List_Init */

typedef struct EffectNode {
    char pad00[0x5c];
    int flags;                 /* 0x5c */
    char pad60[0x6c - 0x60];
    Callback onBusy;           /* 0x6c */
    char pad70[0x84 - 0x70];
    void *owner;               /* 0x84 */
} EffectNode;

typedef struct StatusNode {
    u16 flags;                 /* 0x00 */
    char pad02[0x8 - 0x2];
    Callback field_08;         /* 0x08 */
    Callback field_0c;         /* 0x0c */
    Callback field_10;         /* 0x10 */
    Callback field_14;         /* 0x14 */
    Callback field_18;         /* 0x18 */
    Callback field_1c;         /* 0x1c */
    char pad20[0x40 - 0x20];
    int field_40;              /* 0x40 */
    char pad44[0x70 - 0x44];
    Callback field_70;         /* 0x70 */
    Callback field_74;         /* 0x74 */
    int tableIndex;            /* 0x78 */
    void *tableEntry;          /* 0x7c */
    List28 list80;             /* 0x80 */
    List28 lista8;             /* 0xa8 */
    List28 listd0;             /* 0xd0 */
    int field_f8;              /* 0xf8 */
    char padfc[0x100 - 0xfc];
    EffectNode *group100;      /* 0x100 */
    EffectNode *group104;      /* 0x104 */
    EffectNode *burnFx;        /* 0x108 */
    EffectNode *frostFx;       /* 0x10c */
    EffectNode *shockFx;       /* 0x110 */
    EffectNode *field_114;     /* 0x114 */
} StatusNode;

extern void Ov107_InitBehaviorNode(StatusNode *node);
extern void *GetTrackEntryBase(int idx);
extern EffectNode *ModelNode_New(void);
extern void List_Init(List28 *list);
extern EffectNode *CreateSubitemInstance0xB4(void *modelName);
typedef struct Ov107Global {
    char pad00[0x88];
    int field_88;              /* 0x88 */
} Ov107Global;

extern Ov107Global *Ov107_GetActorManager(void);

extern void Ov107_ReleaseEmitterResources(void);
extern void Ov107_Region_Update(void);
extern void Ov107_Region_OnEvent(void);
extern void Ov107_Region_SetEnabled(void);
extern void Ov107_Region_SetVisible(void);
extern void Ov107_Region_OnSyncMessage(void);
extern void Ov107_Region_AddMember(void);
extern void Ov107_Region_RemoveMember(void);
extern void Ov107_Region_OnBusy(void);
extern void Ov107_Region_DrawStatusFx2(void);
extern void Ov107_Region_DrawStatusFx4(void);
extern void Ov107_Region_DrawStatusFx8(void);

extern char gOv107BaEfSBurnPackPath[]; /* "ba/ef/s_burn.p.z" */
extern char gOv107BaEfSFrostPackPath[]; /* "ba/ef/s_frost.p.z" */
extern char gOv107BaEfSShockPackPath[]; /* "ba/ef/s_shock.p.z" */

void Ov107_Region_Init(StatusNode *self, int tableIndex)
{
    EffectNode *fx;

    Ov107_InitBehaviorNode(self);

    self->flags |= 4;
    self->field_08 = Ov107_ReleaseEmitterResources;
    self->field_0c = Ov107_Region_Update;
    self->field_10 = Ov107_Region_OnEvent;
    self->field_14 = Ov107_Region_SetEnabled;
    self->field_18 = Ov107_Region_SetVisible;
    self->field_1c = Ov107_Region_OnSyncMessage;
    self->field_70 = Ov107_Region_AddMember;
    self->field_74 = Ov107_Region_RemoveMember;
    self->tableIndex = tableIndex;
    self->tableEntry = GetTrackEntryBase((u16)self->tableIndex);

    self->field_40 |= 4;

    self->group100 = ModelNode_New();
    self->group104 = ModelNode_New();
    self->group104->flags |= 2;

    self->field_f8 &= ~0xf;

    List_Init(&self->list80);
    List_Init(&self->lista8);
    List_Init(&self->listd0);

    fx = CreateSubitemInstance0xB4(gOv107BaEfSBurnPackPath);
    self->burnFx = fx;
    RegisterSubscriberSlot(self->group104, fx);
    SetSubitemState(fx, 0, 0, 1);
    SetSubitemState(fx, 2, 0, 1);
    SetSubitemState(fx, 3, 0, 1);
    fx->onBusy = Ov107_Region_OnBusy;
    fx->owner = self;

    fx = CreateSubitemInstance0xB4(gOv107BaEfSFrostPackPath);
    self->frostFx = fx;
    RegisterSubscriberSlot(self->group104, fx);
    SetSubitemState(fx, 0, 0, 1);
    SetSubitemState(fx, 2, 0, 1);
    fx->onBusy = Ov107_Region_DrawStatusFx2;
    fx->owner = self;

    fx = CreateSubitemInstance0xB4(gOv107BaEfSShockPackPath);
    self->shockFx = fx;
    RegisterSubscriberSlot(self->group104, fx);
    SetSubitemState(fx, 0, 0, 1);
    SetSubitemState(fx, 2, 0, 1);
    fx->onBusy = Ov107_Region_DrawStatusFx4;
    fx->owner = self;

    fx = CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(Ov107_GetActorManager()->field_88, 8)));
    self->field_114 = fx;
    RegisterSubscriberSlot(self->group104, fx);
    fx->onBusy = Ov107_Region_DrawStatusFx8;
    fx->owner = self;
}
