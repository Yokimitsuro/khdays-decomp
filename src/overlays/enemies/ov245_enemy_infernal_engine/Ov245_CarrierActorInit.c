/* Ov245_CarrierActorInit -- constructor of the ov245 carrier actor: installs the handlers (+8 tick,
 * +0xc draw, +0x1c message, +0x30 / +0x28 / +0x2c / +0x34 / +0x20 callbacks, +0x24 hook, +0x1d0
 * hit, +0x1dc finish), raises bits 1-3 of the +0x60 high byte and bits 2, 3, 7 and 11 of +0x1b0,
 * seeds the +0x64 pose at scale 1.0, builds the primary item from pool entry 0x10 of the +0x3dc
 * pool (+0x384, subscribed, motion halted) and its named joint (+0x3a0, kind 3), two items from
 * the shared +0x88 model base (kinds 0 and 3, +0x3e0 / +0x3e8) and one from entry 0x1a (+0x3f0),
 * all three attached (bit 1 of +0x5c), two placements from the +0x64 pose (+0x388 on the +0x22c
 * list with bit 1 of its +8 low byte, +0x38c on the +0x144 list) and three +0x394 slots (020d07f0). */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef void (*Callback)(void);
struct w8 { unsigned int lo : 8, rest : 24; };
struct Ov245Slot { int pItem; int pad4; };
struct Ov245Self { char pad[0x3e0]; struct Ov245Slot slots[3]; };
struct Ov245Nodes { char pad[0x394]; int nodes[3]; };

extern void Ov245_Actor2_Destroy(void);
extern void Ov245_OwnedPoseSync(void);
extern void Ov245_PlacementMsgHook(void);
extern void Ov245_SpawnActorRegistryEntry_2(void);
extern void Ov245_Carrier_ForwardRegionEventToParts(void);
extern void Ov245_Carrier_NotifyPartsThenBase(void);
extern void Ov245_ReleaseHeld3f4(void);
extern void Ov245_SendBlankStatusWide(void);
extern void Ov245_PackPosMsg(void);
extern void Ov245_StockHitFilter(void);
extern void Ov245_Model_ReapplyTrack0(void);
extern void *Ov107_PackTextureHandle(int pool, int index);
extern int CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, int item);
extern void RefreshObjectCallbacks(int item, int a);
extern int InsertSortedEntryWithKey(int item, int kind, const char *name);
extern void *Ov107_GetActorManager(void);
extern void Ov107_EnqueueValue(int self, int item);
extern int *List_InsertSorted(void *list, int stride, int max);
extern int Ov107_CloneResourceTransform(void *pose);
extern int Ov245_Child_New(int self);
extern const char gOv245BoneTag00Name[];

static inline void VEC_Set(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void Ov245_CarrierActorInit(int selfArg) {
    char *self = (char *)selfArg;
    int pool = *(int *)(self + 0x3dc);
    int *slot;
    int i;
    void *os;

    *(Callback *)(self + 0x8) = Ov245_Actor2_Destroy;
    *(Callback *)(self + 0xc) = Ov245_OwnedPoseSync;
    *(Callback *)(self + 0x1c) = Ov245_PlacementMsgHook;
    *(Callback *)(self + 0x30) = Ov245_SpawnActorRegistryEntry_2;
    *(Callback *)(self + 0x28) = Ov245_Carrier_ForwardRegionEventToParts;
    *(Callback *)(self + 0x2c) = Ov245_Carrier_NotifyPartsThenBase;
    *(Callback *)(self + 0x34) = Ov245_ReleaseHeld3f4;
    *(Callback *)(self + 0x20) = Ov245_SendBlankStatusWide;
    *(Callback *)(self + 0x24) = Ov245_PackPosMsg;
    *(Callback *)(self + 0x1d0) = Ov245_StockHitFilter;
    *(Callback *)(self + 0x1dc) = Ov245_Model_ReapplyTrack0;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xb0) |= 0x88c;
    *(int *)(self + 0x70) = 0x1000;
    VEC_Set((VecFx32 *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(pool, 0x10));
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    RefreshObjectCallbacks(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x3a0) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv245BoneTag00Name);
    os = Ov107_GetActorManager();
    ((struct Ov245Self *)self)->slots[0].pItem =
        CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(*(int *)((char *)os + 0x88), 0)));
    os = Ov107_GetActorManager();
    ((struct Ov245Self *)self)->slots[1].pItem =
        CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(*(int *)((char *)os + 0x88), 3)));
    ((struct Ov245Self *)self)->slots[2].pItem = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(pool, 0x1a));
    for (i = 0; i < 3; i++) {
        Ov107_EnqueueValue(self, ((struct Ov245Self *)self)->slots[i].pItem);
        *(int *)(((struct Ov245Self *)self)->slots[i].pItem + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = List_InsertSorted((void *)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = Ov107_CloneResourceTransform((void *)(self + 0x64));
    ((struct w8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
    slot = List_InsertSorted((void *)(self + 0x144), 4, 0x64);
    *(int *)(self + 0x38c) = *slot = Ov107_CloneResourceTransform((void *)(self + 0x64));
    for (i = 0; i < 3; i++) {
        ((struct Ov245Nodes *)self)->nodes[i] = Ov245_Child_New(self);
    }
}
