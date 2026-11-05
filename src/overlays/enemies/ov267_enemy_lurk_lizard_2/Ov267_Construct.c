/* Constructor of the ov267 enemy. Installs the handlers (+8, +0xc draw,
 * +0x1c message, +0x20, +0x24 message pack, +0x28, +0x2c, +0x30, +0x34 update, +0x38, +0x1d0 hit
 * filter, +0x1dc, +0x1e0, +0x1e4), clears the +0x5e4 list, sets the +0x64 pose (scale 3.5), the
 * +0x1fc bounds box (+/-2.0 wide, 2.0 tall), bits 5 and 7 of the +0x60 high byte and bit 3 of
 * +0x1ae; builds the +0x384 rig from pose 0 (owned by the enemy, callback Ov267_BoneCallback,
 * subscribed to +0x9c, lowered 2.0) and resolves its six bones (+0x58c, +0x590, +0x598, +0x59c,
 * +0x5a0, +0x5a4); builds the sixteen +0x38c chain items (pose 1, the last one pose 2; each keeps
 * the "tip" bone at +0x594, the first one is owned by the enemy with callback
 * Ov267_ProbeAndCacheHit), all hidden, subscribed and posed with the identity quaternion at +0x3cc;
 * builds the +0x388 grab part from pose 0xd (callback Ov267_RefreshAimPoint, bone at +0x588);
 * registers action 2/3 lowered by the scale (rate 0.6) and action 1/2 (rate 0.8); builds the
 * ten sub-items of data_ov267_020d5d40 into the +0x60c pair table (the first two from the shared
 * scene resource), reserves the +0x22c/+0x144 handles of three shapes (+0x4cc/+0x4d8: a capsule
 * of length 1.0 and radius 2.0, then two placements of scale 1.0), creates the two +0x5cc
 * trails (Ov267_New) and the +0x5d4 shadow (Ov267_New_2), and loads sound
 * 0x15e. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef void (*Callback)(void);
typedef struct { int w[4]; } Quat;
typedef struct { int id[10]; } IdTable;
typedef struct { int w[6]; } Box;
typedef struct { VecFx32 pos; int scale; } Placement;
typedef struct { VecFx32 pos; VecFx32 axis; int length; int radius; } Capsule;
struct Items { char pad[0x38c]; int items[16]; };
struct Poses { char pad[0x3cc]; Quat pose[16]; };
struct Pair { int res; int handle; };
struct Pairs { char pad[0x60c]; struct Pair pairs[10]; };
struct b1 { unsigned int b0 : 1; };

extern void Ov267_Teardown(void);
extern void Ov267_TickWithCallbacks(void);
extern void Ov267_OnMessage(void);
extern void Ov267_CreateNodeRegistryEntry(void);
extern void Ov267_ForwardRegionEventToParts(void);
extern void Ov267_NotifyPartsThenBase(void);
extern void Ov267_PreUpdate(void);
extern void Ov267_SendStatusShortOrFull(void);
extern void Ov267_HandleMessagePack(void);
extern void Ov267_BuildPathPointList(void);
extern void Ov267_OnHit(void);
extern void Ov267_PushStanceToChannels(void);
extern void Ov267_RequestState13(void);
extern void Ov267_RequestState14(void);
extern void Ov267_BoneCallback(void);
extern void Ov267_ProbeAndCacheHit(void);
extern void Ov267_RefreshAimPoint(void);
extern void List_Init(void *list);
extern void *Ov107_PackTextureHandle(char *self, int index);
extern int CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, int item);
extern void Srt_SetTranslationXYZ(void *srt, int x, int y, int z);
extern int FindResourceIndexByName(int item, const char *name);
extern void RefreshObjectCallbacks(int item, int a);
extern void Ov107_Actor_SetAttachSlot(char *self, int slot, int a, const VecFx32 *v, int c);
extern char *Ov107_GetActorManager(void);
extern void Ov107_EnqueueValue(char *self, int item);
extern int *List_InsertSorted(void *pool, int elementSize, int capacity);
extern int Ov107_Mover_New(const Capsule *capsule);
extern int Ov107_CloneResourceTransform(const Placement *placement);
extern int Ov267_New(char *self);
extern int Ov267_New_2(char *self);
extern void Res_RequestIdPair(int resourceId);
extern IdTable data_ov267_020d5d40;
extern const char gOv267BoneSpine01Name[];
extern const char gOv267TagBeroName[];
extern const char gOv267BoneHeadName[];
extern const char gOv267BoneTail02Name[];
extern const char gOv267BoneLHandName[];
extern const char gOv267BoneRHandName[];
extern const char gOv267TagE01Name[];
extern const char gOv267MoveName[];
extern const Quat data_020420f8;
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;

void Ov267_Construct(char *self)
{
    IdTable ids = data_ov267_020d5d40;
    Box params;
    Placement place;
    Capsule cap;
    VecFx32 lift;
    Quat quat;
    VecFx32 zero;
    u16 hw;
    int i;
    int *slot;
    int node;

    params.w[0] = -0x2000;
    params.w[1] = 0;
    params.w[2] = -0x2000;
    params.w[3] = 0x2000;
    params.w[4] = 0x2000;
    params.w[5] = 0x2000;
    *(Callback *)(self + 0x8) = Ov267_Teardown;
    *(Callback *)(self + 0xc) = Ov267_TickWithCallbacks;
    *(Callback *)(self + 0x1c) = Ov267_OnMessage;
    *(Callback *)(self + 0x30) = Ov267_CreateNodeRegistryEntry;
    *(Callback *)(self + 0x28) = Ov267_ForwardRegionEventToParts;
    *(Callback *)(self + 0x2c) = Ov267_NotifyPartsThenBase;
    *(Callback *)(self + 0x34) = Ov267_PreUpdate;
    *(Callback *)(self + 0x20) = Ov267_SendStatusShortOrFull;
    *(Callback *)(self + 0x24) = Ov267_HandleMessagePack;
    *(Callback *)(self + 0x38) = Ov267_BuildPathPointList;
    *(Callback *)(self + 0x1d0) = Ov267_OnHit;
    *(Callback *)(self + 0x1dc) = Ov267_PushStanceToChannels;
    *(Callback *)(self + 0x1e0) = Ov267_RequestState13;
    *(Callback *)(self + 0x1e4) = Ov267_RequestState14;
    List_Init(self + 0x5e4);
    /* the default scale first: the overwritten store is dropped after scheduling but still
     * spends the scheduler's budget for this block, which keeps the rig callback's load order */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x3800;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x3800;
    *(int *)(self + 0x6c) = 0;
    *(Box *)(self + 0x1fc) = params;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xa0) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = Ov267_BoneCallback;
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    Srt_SetTranslationXYZ((void *)(*(int *)(self + 0x384) + 4), 0, 0, -0x2000);
    *(int *)(self + 0x58c) = FindResourceIndexByName(*(int *)(self + 0x384), gOv267BoneSpine01Name);
    *(int *)(self + 0x590) = FindResourceIndexByName(*(int *)(self + 0x384), gOv267TagBeroName);
    *(int *)(self + 0x598) = FindResourceIndexByName(*(int *)(self + 0x384), gOv267BoneHeadName);
    *(int *)(self + 0x59c) = FindResourceIndexByName(*(int *)(self + 0x384), gOv267BoneTail02Name);
    *(int *)(self + 0x5a0) = FindResourceIndexByName(*(int *)(self + 0x384), gOv267BoneLHandName);
    *(int *)(self + 0x5a4) = FindResourceIndexByName(*(int *)(self + 0x384), gOv267BoneRHandName);
    *(char **)(self + 0x2cc) = self + 0x514;
    quat = data_020420f8;
    for (i = 0; i < 16; i++) {
        if (i < 15) {
            ((struct Items *)self)->items[i] = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 1));
            *(int *)(self + 0x594) = FindResourceIndexByName(((struct Items *)self)->items[i], gOv267TagE01Name);
        } else {
            ((struct Items *)self)->items[i] = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 2));
        }
        if (i == 0) {
            *(Callback *)(((struct Items *)self)->items[i] + 0x6c) = Ov267_ProbeAndCacheHit;
            *(char **)(((struct Items *)self)->items[i] + 0x84) = self;
        }
        *(int *)(((struct Items *)self)->items[i] + 0x5c) |= 2;
        ((struct b1 *)(((struct Items *)self)->items[i] + 0x5c))->b0 = 1;
        RegisterSubscriberSlot(*(int *)(self + 0x9c), ((struct Items *)self)->items[i]);
        RefreshObjectCallbacks(((struct Items *)self)->items[i], 0);
        ((struct Poses *)self)->pose[i] = quat;
    }
    *(int *)(self + 0x57c) = 0;
    *(int *)(self + 0x388) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0xd));
    *(Callback *)(*(int *)(self + 0x388) + 0x6c) = Ov267_RefreshAimPoint;
    *(char **)(*(int *)(self + 0x388) + 0x84) = self;
    RefreshObjectCallbacks(*(int *)(self + 0x388), 0);
    *(int *)(self + 0x588) = FindResourceIndexByName(*(int *)(self + 0x388), gOv267MoveName);
    lift.x = 0;
    lift.y = -0x3800;
    lift.z = 0;
    Ov107_Actor_SetAttachSlot(self, 2, 3, &lift, 0x99a);
    Ov107_Actor_SetAttachSlot(self, 1, 2, 0, 0xccd);
    for (i = 0; i < 10; i++) {
        if (i <= 1) {
            node = CreateSubitemInstance0xB4((void *)((ids.id[i] & 0x1ff)
                | (ARCHIVE_HANDLE(*(int *)(Ov107_GetActorManager() + 0x88), 0))));
        } else {
            node = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        }
        Ov107_EnqueueValue(self, ((struct Pairs *)self)->pairs[i].res = node);
        *(int *)(((struct Pairs *)self)->pairs[i].res + 0x5c) |= 2;
    }
    zero = data_02041dc8;
    place.scale = 0x1000;
    place.pos = zero;
    cap.pos = zero;
    cap.axis = data_02042264;
    cap.length = 0x1000;
    cap.radius = 0x2000;
    for (i = 0; i < 3; i++) {
        ((int **)(self + 0x4cc))[i] = List_InsertSorted(self + 0x22c, 0x10, 100);
        *((int **)(self + 0x4cc))[i] = i == 0 ? Ov107_Mover_New(&cap) : Ov107_CloneResourceTransform(&place);
        slot = List_InsertSorted(self + 0x144, 4, 100);
        node = i == 0 ? Ov107_Mover_New(&cap) : Ov107_CloneResourceTransform(&place);
        ((int *)(self + 0x4d8))[i] = *slot = node;
    }
    for (i = 0; i < 2; i++) {
        ((int *)(self + 0x5cc))[i] = Ov267_New(self);
    }
    *(int *)(self + 0x5d4) = Ov267_New_2(self);
    Res_RequestIdPair(0x15e);
}
