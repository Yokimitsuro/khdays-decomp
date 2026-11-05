/* Constructor of the ov146 actor: installs the handlers (+8 destroy, +0x1c spawn message, +0x28 /
 * +0x2c / +0x30 callbacks, +0x34 block-chain propagation, +0x1d0 damage, +0x1dc motion binding,
 * +0x1e0 / +0x1e4), the pose scale 0.75 and the +0x1fc bounds (min (-0.93, 0.006, -0.52), extent
 * (1.86, 1.76, 0.84)); builds the body model from pool entry 0 (+0x384, subscribed) with its Broot
 * joint (+0x3c0) and entry 1 as motion on the +0x388 track; five hidden parts (+0x3c4, stride 8) from
 * the ids of data_ov146_020cf4f8 -- the first three relative to the running thread's resource, the
 * last two from the pool; actions 2, 1 and 4 at 2.0; the pose as a hit shape on the +0x22c (+0x3ac)
 * and +0x144 (+0x3b0) lists; the two helpers 020ce308 / 020cee30 (+0x3b8 / +0x3bc) and sound 0x125. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef void (*Callback)(void);
typedef struct { VecFx32 min; VecFx32 max; } Box;
typedef struct { VecFx32 v; int nScale; } Pose;
typedef struct { int id[5]; } PartIds;
struct Ov146Part { int item; int pad; };

extern void Ov146_Actor_Destroy(void);
extern void Ov146_OnSpawnMessage(void);
extern void Ov146_CreateAiTask(void);
extern void Ov146_ForwardRegionEventToParts(void);
extern void Ov146_NotifyPartsThenBase(void);
extern void Ov146_PropagateBlockChainThenNotify(void);
extern void Ov146_OnDamage(void);
extern void Ov146_BindMotion(void);
extern void Ov146_RequestSubState10IfNotCurrent(void);
extern void Ov146_RequestSubState11IfIdle(void);
extern void *Ov107_PackTextureHandle(char *self, int index);
extern int CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, int item);
extern int InsertSortedEntryWithKey(int item, int kind, const char *name);
extern void Snd_RegisterSeqAndBind(void *track, int model, void *resource, int slot);
extern void MainBlob_ResetSlotRows(int item, void *track);
extern int Ov107_GetActorManager(void);
extern void Ov107_EnqueueValue(char *self, int item);
extern void Ov107_Actor_SetAttachSlot(char *self, int action, int a, int b, int scale);
extern int *List_InsertSorted(void *list, int stride, int max);
extern int Ov107_CloneResourceTransform(Pose *pose);
extern int Ov146_Rider_New(char *self);
extern int Ov146_Mount_New(char *self);
extern void Res_RequestIdPair(int id);
extern const PartIds data_ov146_020cf4f8;
extern const char gOv146BrootName[];
extern const VecFx32 data_02041dc8;

void Ov146_Actor_Construct(char *self)
{
    PartIds ids = data_ov146_020cf4f8;
    Box box;
    Pose pose;
    int minX;
    int minY;
    int minZ;
    int *slot;
    int i;

    minX = -0xeea;
    minZ = -0x858;
    minY = 0x17;
    *(Callback *)(self + 0x8) = Ov146_Actor_Destroy;
    *(Callback *)(self + 0x1c) = Ov146_OnSpawnMessage;
    box.min.x = minX;
    box.min.y = minY;
    box.min.z = minZ;
    box.max.x = box.min.x + 0x1dd3;
    box.max.y = box.min.y + 0x1c27;
    box.max.z = box.min.z + 0xd64;
    *(Callback *)(self + 0x30) = Ov146_CreateAiTask;
    *(Callback *)(self + 0x28) = Ov146_ForwardRegionEventToParts;
    *(Callback *)(self + 0x2c) = Ov146_NotifyPartsThenBase;
    *(Callback *)(self + 0x34) = Ov146_PropagateBlockChainThenNotify;
    *(Callback *)(self + 0x1d0) = Ov146_OnDamage;
    *(Callback *)(self + 0x1dc) = Ov146_BindMotion;
    *(Callback *)(self + 0x1e0) = Ov146_RequestSubState10IfNotCurrent;
    *(Callback *)(self + 0x1e4) = Ov146_RequestSubState11IfIdle;
    *(int *)(self + 0x70) = 0xc00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0xc00;
    *(int *)(self + 0x6c) = 0;
    *(Box *)(self + 0x1fc) = box;
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x3c0) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv146BrootName);
    Snd_RegisterSeqAndBind(self + 0x388, *(int *)(*(int *)(self + 0x384) + 0x88), Ov107_PackTextureHandle(self, 1), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x384), self + 0x388);
    for (i = 0; i < 5; i++) {
        int item;

        if (i < 3) {
            item = CreateSubitemInstance0xB4((void *)((ids.id[i] & 0x1ff)
                | (ARCHIVE_HANDLE(*(int *)(Ov107_GetActorManager() + 0x88), 0))));
        } else {
            item = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        }
        ((struct Ov146Part *)(self + 0x3c4))[i].item = item;
        Ov107_EnqueueValue(self, ((struct Ov146Part *)(self + 0x3c4))[i].item);
        *(int *)(((struct Ov146Part *)(self + 0x3c4))[i].item + 0x5c) |= 2;
    }
    Ov107_Actor_SetAttachSlot(self, 2, 1, 0, 0x2000);
    Ov107_Actor_SetAttachSlot(self, 1, 1, 0, 0x2000);
    Ov107_Actor_SetAttachSlot(self, 4, 1, 0, 0x2000);
    pose = *(Pose *)(self + 0x64);
    pose.v = data_02041dc8;
    *(int **)(self + 0x3ac) = List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3ac) = Ov107_CloneResourceTransform(&pose);
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3b0) = *slot = Ov107_CloneResourceTransform(&pose);
    *(int *)(self + 0x3b8) = Ov146_Rider_New(self);
    *(int *)(self + 0x3bc) = Ov146_Mount_New(self);
    Res_RequestIdPair(0x125);
}
