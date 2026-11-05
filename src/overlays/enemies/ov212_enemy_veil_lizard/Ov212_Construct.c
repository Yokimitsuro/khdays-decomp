/* Constructor of the ov212 enemy (x3 with ov266/ov267). Installs the handlers (+8, +0xc draw,
 * +0x1c message, +0x20, +0x24 message pack, +0x28, +0x2c, +0x30, +0x34 update, +0x38, +0x1d0 hit
 * filter, +0x1dc, +0x1e0, +0x1e4), clears the +0x5e4 list, sets the +0x64 pose (scale 2.97), the
 * +0x1fc bounds box (+/-2.0 wide, 2.0 tall), bits 5 and 7 of the +0x60 high byte and bit 3 of
 * +0x1ae; builds the +0x384 rig from pose 0 (owned by the enemy, callback Ov212_BoneCallback,
 * subscribed to +0x9c, lowered 1.7) and resolves its six bones (+0x58c, +0x590, +0x598, +0x59c,
 * +0x5a0, +0x5a4); builds the sixteen +0x38c chain items (pose 1, the last one pose 2; each keeps
 * the "tip" bone at +0x594, the first one is owned by the enemy with callback
 * Ov212_ProbeAndCacheHit), all hidden, subscribed and posed with the identity quaternion at +0x3cc;
 * builds the +0x388 grab part from pose 0xd (callback Ov212_RefreshAimPoint, bone at +0x588);
 * registers action 2/3 lowered by the scale (rate 0.51) and action 1/2 (rate 0.68); builds the
 * ten sub-items of data_ov212_020d212c into the +0x60c pair table (the first two from the shared
 * scene resource), reserves the +0x22c/+0x144 handles of three shapes (+0x4cc/+0x4d8: a capsule
 * of length 0.85 and radius 1.7, then two placements of scale 0.85), creates the two +0x5cc
 * trails (Ov212_New) and the +0x5d4 shadow (Ov212_Tail_New), and loads sound
 * 0x128. */

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

extern void Ov212_Teardown(void);
extern void Ov212_TickWithCallbacks(void);
extern void Ov212_OnMessage(void);
extern void Ov212_CreateNodeRegistryEntry(void);
extern void Ov212_ForwardRegionEventToParts(void);
extern void Ov212_NotifyPartsThenBase(void);
extern void Ov212_PreUpdate(void);
extern void Ov212_SendStatusShortOrFull(void);
extern void Ov212_HandleMessagePack(void);
extern void Ov212_BuildPathPointList(void);
extern void Ov212_OnHit(void);
extern void Ov212_PushStanceToChannels(void);
extern void Ov212_RequestState13(void);
extern void Ov212_RequestState14(void);
extern void Ov212_BoneCallback(void);
extern void Ov212_ProbeAndCacheHit(void);
extern void Ov212_RefreshAimPoint(void);
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
extern int Ov212_New(char *self);
extern int Ov212_Tail_New(char *self);
extern void Res_RequestIdPair(int resourceId);
extern IdTable data_ov212_020d212c;
extern const char gOv212BoneSpine01Name[];
extern const char gOv212TagBeroName[];
extern const char gOv212BoneHeadName[];
extern const char gOv212BoneTail02Name[];
extern const char gOv212BoneLHandName[];
extern const char gOv212BoneRHandName[];
extern const char gOv212TagE01Name[];
extern const char gOv212MoveName[];
extern const Quat data_020420f8;
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;

void Ov212_Construct(char *self)
{
    IdTable ids = data_ov212_020d212c;
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
    *(Callback *)(self + 0x8) = Ov212_Teardown;
    *(Callback *)(self + 0xc) = Ov212_TickWithCallbacks;
    *(Callback *)(self + 0x1c) = Ov212_OnMessage;
    *(Callback *)(self + 0x30) = Ov212_CreateNodeRegistryEntry;
    *(Callback *)(self + 0x28) = Ov212_ForwardRegionEventToParts;
    *(Callback *)(self + 0x2c) = Ov212_NotifyPartsThenBase;
    *(Callback *)(self + 0x34) = Ov212_PreUpdate;
    *(Callback *)(self + 0x20) = Ov212_SendStatusShortOrFull;
    *(Callback *)(self + 0x24) = Ov212_HandleMessagePack;
    *(Callback *)(self + 0x38) = Ov212_BuildPathPointList;
    *(Callback *)(self + 0x1d0) = Ov212_OnHit;
    *(Callback *)(self + 0x1dc) = Ov212_PushStanceToChannels;
    *(Callback *)(self + 0x1e0) = Ov212_RequestState13;
    *(Callback *)(self + 0x1e4) = Ov212_RequestState14;
    List_Init(self + 0x5e4);
    /* the default scale first: the overwritten store is dropped after scheduling but still
     * spends the scheduler's budget for this block, which keeps the rig callback's load order */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x2f9b;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2f9b;
    *(int *)(self + 0x6c) = 0;
    *(Box *)(self + 0x1fc) = params;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xa0) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = Ov212_BoneCallback;
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    Srt_SetTranslationXYZ((void *)(*(int *)(self + 0x384) + 4), 0, 0, -0x1b34);
    *(int *)(self + 0x58c) = FindResourceIndexByName(*(int *)(self + 0x384), gOv212BoneSpine01Name);
    *(int *)(self + 0x590) = FindResourceIndexByName(*(int *)(self + 0x384), gOv212TagBeroName);
    *(int *)(self + 0x598) = FindResourceIndexByName(*(int *)(self + 0x384), gOv212BoneHeadName);
    *(int *)(self + 0x59c) = FindResourceIndexByName(*(int *)(self + 0x384), gOv212BoneTail02Name);
    *(int *)(self + 0x5a0) = FindResourceIndexByName(*(int *)(self + 0x384), gOv212BoneLHandName);
    *(int *)(self + 0x5a4) = FindResourceIndexByName(*(int *)(self + 0x384), gOv212BoneRHandName);
    *(char **)(self + 0x2cc) = self + 0x514;
    quat = data_020420f8;
    for (i = 0; i < 16; i++) {
        if (i < 15) {
            ((struct Items *)self)->items[i] = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 1));
            *(int *)(self + 0x594) = FindResourceIndexByName(((struct Items *)self)->items[i], gOv212TagE01Name);
        } else {
            ((struct Items *)self)->items[i] = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 2));
        }
        if (i == 0) {
            *(Callback *)(((struct Items *)self)->items[i] + 0x6c) = Ov212_ProbeAndCacheHit;
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
    *(Callback *)(*(int *)(self + 0x388) + 0x6c) = Ov212_RefreshAimPoint;
    *(char **)(*(int *)(self + 0x388) + 0x84) = self;
    RefreshObjectCallbacks(*(int *)(self + 0x388), 0);
    *(int *)(self + 0x588) = FindResourceIndexByName(*(int *)(self + 0x388), gOv212MoveName);
    lift.x = 0;
    lift.y = -0x2f9b;
    lift.z = 0;
    Ov107_Actor_SetAttachSlot(self, 2, 3, &lift, 0x82a);
    Ov107_Actor_SetAttachSlot(self, 1, 2, 0, 0xae2);
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
    place.scale = 0xd9a;
    place.pos = zero;
    cap.pos = zero;
    cap.axis = data_02042264;
    cap.length = 0xd9a;
    cap.radius = 0xd9a * 2;
    for (i = 0; i < 3; i++) {
        ((int **)(self + 0x4cc))[i] = List_InsertSorted(self + 0x22c, 0x10, 100);
        *((int **)(self + 0x4cc))[i] = i == 0 ? Ov107_Mover_New(&cap) : Ov107_CloneResourceTransform(&place);
        slot = List_InsertSorted(self + 0x144, 4, 100);
        node = i == 0 ? Ov107_Mover_New(&cap) : Ov107_CloneResourceTransform(&place);
        ((int *)(self + 0x4d8))[i] = *slot = node;
    }
    for (i = 0; i < 2; i++) {
        ((int *)(self + 0x5cc))[i] = Ov212_New(self);
    }
    *(int *)(self + 0x5d4) = Ov212_Tail_New(self);
    Res_RequestIdPair(0x128);
}
