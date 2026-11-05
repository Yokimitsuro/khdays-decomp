/* Constructor of the ov244 enemy (x2 with ov277). Installs the handlers (+8, +0xc, +0x1c message,
 * +0x28, +0x2c, +0x30, +0x34 update, +0x38, +0x1d0 hit filter, +0x1d4, +0x1d8, +0x1dc, +0x1ec),
 * sets kind 2, bits 2, 5 and 7 of the +0x60 high byte, the +0x64 pose (scale 4.0) and bits 3-4 of
 * +0x1ae; builds the +0x384 body rig (pose 0, subscribed to +0x9c) with its +0x390 work list
 * (pose 2) and fourteen bone attachments (+0x3a8..+0x3dc), and the +0x388 / +0x38c arm rigs (poses
 * 0xd / 0x1a, flagged, lists 0xf / 0x1c at +0x394 / +0x398); the eight hidden sub-items of
 * data_ov244_020d3638 go into the +0x40c pair table, the +0x424 list gets two 020d15ac entries
 * (+0x400), six parts (020cd438, +0x404) and four part controllers (020d0ca4, +0x408) are created.
 * Shapes: six capsules (length 1.0, radius 1.5, along z) at +0x3e0..+0x3f4 and two along y
 * (radius 3.0 / 2.0) at +0x3f8 / +0x3fc on the +0x144 pool; on the +0x22c pool a placement
 * (scale 2.0) at +0x39c and two capsules (radius 1.625, along x) at +0x3a0 / +0x3a4. Loads sound
 * 0x113. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*Callback)(void);
typedef struct { int id[8]; } IdTable8;
typedef struct { VecFx32 pos; int scale; } Placement;
typedef struct { VecFx32 pos; VecFx32 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
struct b1 { unsigned int b0 : 1; };

extern void Ov244_ReleaseNodeResources(void);
extern void Ov244_TickUnlessFrozen(void);
extern void Ov244_HandleMessage(void);
extern void Ov244_RemoveFromDrawList(void);
extern void Ov244_RegisterDrawList(void);
extern void Ov244_CreateRegistryEntryAndLink_2(void);
extern void Ov244_Update(void);
extern void Ov244_SetHeadingDegrees(void);
extern void Ov244_HitFilter(void);
extern void Ov244_SetAttackPower(void);
extern void Ov244_RebindCollisionSlot(void);
extern void func_ov244_020cd20c(void);
extern void Ov244_RunSubNodeCallbacksArg(void);
extern void *Ov107_PackTextureHandle(char *self, int index);
extern int CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, int item);
extern int CallocInstance(int size);
extern void Snd_RegisterSeqAndBind(int a, int b, void *c, int d);
extern void MainBlob_ResetSlotRows(int a, int b);
extern int InsertSortedEntryWithKey(int item, int kind, void *name);
extern void Ov107_EnqueueValue(char *self, int item);
extern void Ov107_LoadSpawnRecord(int a, void *list);
extern int Ov244_CreateNamedEntity(void *list);
extern int Ov244_Item_New(char *self);
extern int Ov244_PartController_New(char *self);
extern int *List_InsertSorted(void *pool, int elementSize, int capacity);
extern int Ov107_Mover_New(const Capsule *capsule);
extern int Ov107_CloneResourceTransform(const Placement *placement);
extern void Res_RequestIdPair(int resourceId);
extern IdTable8 data_ov244_020d3638;
extern char gOv244Bip01Spine1Name[];
extern char gOv244Bip01NeckName[];
extern char gOv244Bip01SpineName[];
extern char gOv244Bip01PelvisName[];
extern char gOv244Ds01Name[];
extern char gOv244Bip01HeadName[];
extern char gOv244Bip01RUpperArmName[];
extern char gOv244Bip01RForearmName[];
extern char gOv244Bip01RHandName[];
extern char gOv244Bip01RFinger1Name[];
extern char gOv244Bip01LUpperArmName[];
extern char gOv244Bip01LForearmName[];
extern char gOv244Bip01LHandName[];
extern char gOv244Bip01LFinger1Name[];
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042270;
extern const VecFx32 data_02042264;
extern const VecFx32 data_0204227c;

void Ov244_Construct(char *self)
{
    IdTable8 ids = data_ov244_020d3638;
    Capsule cap;
    Placement place;
    VecFx32 zero;
    VecFx32 axisX;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = Ov244_ReleaseNodeResources;
    *(Callback *)(self + 0xc) = Ov244_TickUnlessFrozen;
    *(Callback *)(self + 0x1c) = Ov244_HandleMessage;
    *(Callback *)(self + 0x28) = Ov244_RemoveFromDrawList;
    *(Callback *)(self + 0x2c) = Ov244_RegisterDrawList;
    *(Callback *)(self + 0x30) = Ov244_CreateRegistryEntryAndLink_2;
    *(Callback *)(self + 0x34) = Ov244_Update;
    *(Callback *)(self + 0x38) = Ov244_SetHeadingDegrees;
    *(Callback *)(self + 0x1d0) = Ov244_HitFilter;
    *(Callback *)(self + 0x1d8) = Ov244_SetAttackPower;
    *(Callback *)(self + 0x1dc) = Ov244_RebindCollisionSlot;
    *(Callback *)(self + 0x1d4) = func_ov244_020cd20c;
    *(Callback *)(self + 0x1ec) = Ov244_RunSubNodeCallbacksArg;
    *(unsigned char *)(self + 0x1c9) = 2;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xa4) << 0x18) >> 0x10);
    /* default scale first: the overwritten store is dropped after scheduling but spends the
     * block's scheduling budget (keeps the ROM's argument order of the attachment calls) */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x4000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x4000;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x390) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(int *)(self + 0x390), *(int *)(*(int *)(self + 0x384) + 0x88), Ov107_PackTextureHandle(self, 2), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x384), *(int *)(self + 0x390));
    *(int *)(self + 0x3a8) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv244Bip01Spine1Name);
    *(int *)(self + 0x3ac) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01NeckName);
    *(int *)(self + 0x3b0) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv244Bip01SpineName);
    *(int *)(self + 0x3b4) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01PelvisName);
    *(int *)(self + 0x3b8) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv244Ds01Name);
    *(int *)(self + 0x3bc) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv244Bip01HeadName);
    *(int *)(self + 0x3c0) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01RUpperArmName);
    *(int *)(self + 0x3c4) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01RForearmName);
    *(int *)(self + 0x3c8) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01RHandName);
    *(int *)(self + 0x3cc) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01RFinger1Name);
    *(int *)(self + 0x3d0) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01LUpperArmName);
    *(int *)(self + 0x3d4) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01LForearmName);
    *(int *)(self + 0x3d8) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01LHandName);
    *(int *)(self + 0x3dc) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv244Bip01LFinger1Name);
    *(int *)(self + 0x388) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0xd));
    ((struct b1 *)(*(int *)(self + 0x388) + 0x5c))->b0 = 1;
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    *(int *)(self + 0x394) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(int *)(self + 0x394), *(int *)(*(int *)(self + 0x388) + 0x88), Ov107_PackTextureHandle(self, 0xf), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x388), *(int *)(self + 0x394));
    *(int *)(self + 0x38c) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0x1a));
    ((struct b1 *)(*(int *)(self + 0x38c) + 0x5c))->b0 = 1;
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(int *)(self + 0x398) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(int *)(self + 0x398), *(int *)(*(int *)(self + 0x38c) + 0x88), Ov107_PackTextureHandle(self, 0x1c), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x38c), *(int *)(self + 0x398));
    *(int *)(self + 0x40c) = CallocInstance(0x40);
    for (i = 0; i < 8; i++) {
        ((struct Pair *)*(int *)(self + 0x40c))[i].res = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        Ov107_EnqueueValue(self, ((struct Pair *)*(int *)(self + 0x40c))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x40c))[i].res + 0x5c) |= 2;
    }
    Ov107_LoadSpawnRecord(0, self + 0x424);
    *(int *)(self + 0x400) = CallocInstance(8);
    for (i = 0; i < 2; i++) {
        (*(int **)(self + 0x400))[i] = Ov244_CreateNamedEntity(self + 0x424);
    }
    *(int *)(self + 0x404) = CallocInstance(0x18);
    for (i = 0; i < 6; i++) {
        (*(int **)(self + 0x404))[i] = Ov244_Item_New(self);
    }
    *(int *)(self + 0x408) = CallocInstance(0x10);
    for (i = 0; i < 4; i++) {
        (*(int **)(self + 0x408))[i] = Ov244_PartController_New(self);
    }
    zero = data_02041dc8;
    cap.pos = zero;
    cap.axis = data_02042270;
    cap.length = 0x1000;
    cap.radius = 0x1800;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3e0) = *slot = Ov107_Mover_New(&cap);
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3e4) = *slot = Ov107_Mover_New(&cap);
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3e8) = *slot = Ov107_Mover_New(&cap);
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3ec) = *slot = Ov107_Mover_New(&cap);
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3f0) = *slot = Ov107_Mover_New(&cap);
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3f4) = *slot = Ov107_Mover_New(&cap);
    cap.pos = zero;
    cap.axis = data_02042264;
    cap.length = 0x1000;
    cap.radius = 0x3000;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3f8) = *slot = Ov107_Mover_New(&cap);
    cap.radius = 0x2000;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3fc) = *slot = Ov107_Mover_New(&cap);
    place.pos = zero;
    place.scale = 0x2000;
    *(int *)(self + 0x39c) = (int)List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x39c) = Ov107_CloneResourceTransform(&place);
    cap.pos = zero;
    axisX = data_0204227c;
    cap.axis = axisX;
    cap.length = 0x1000;
    cap.radius = 0x1a00;
    *(int *)(self + 0x3a0) = (int)List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3a0) = Ov107_Mover_New(&cap);
    cap.pos = zero;
    cap.axis = axisX;
    cap.length = 0x1000;
    cap.radius = 0x1a00;
    *(int *)(self + 0x3a4) = (int)List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3a4) = Ov107_Mover_New(&cap);
    Res_RequestIdPair(0x113);
}
