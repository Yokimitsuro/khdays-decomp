/* Ov255_EnemyConstruct = Ov255_EnemyConstruct. Constructor of the ov255 enemy (the ov235 constructor's
 * sibling): looks up its effect resource (+0x3f4), installs its handlers (+8 update, +0xc draw, +0x1c
 * message, +0x28, +0x2c, +0x30, +0x34, +0x1d0 hit filter, +0x1dc motion set), raises bit 3 of +0x1ae and
 * bit 5 of the +0x60 high byte and sets the +0x64 pose (scale 1.625). It builds two rigs with their
 * bindings -- body (+0x384/+0x388, poses 0, 1) and arms (+0x38c/+0x390, poses 0x24, 0x25) -- and
 * resolves the +0x3ac, +0x3a8, +0x3b0, +0x3b4 and +0x3b8 parts, the +0x3a4 motion part (pose 0x48),
 * four collision capsules (+0x394, +0x398, +0x39c and a long thin one at +0x3a0) and a +0x3e8
 * placement (hidden), then the twelve effect pairs of +0x3ec (the first nine from the effect
 * resource, the rest from the data_ov255_020d29d8 poses; all hidden), nine sub-objects (+0x3f0, each
 * told its index at +0x3bc) and loads the voice bank (+0x3f8: 0x17f in the alternate language,
 * else 0x17a). */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef void (*Callback)(void);
typedef struct { int id[12]; } IdTable;
typedef struct { VecFx32 pos; int scale; } Placement;
typedef struct { VecFx32 pos; VecFx32 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
struct Nib { u8 lo : 4, hi : 4; };

extern int Ov107_OpenCachedResourceByName(const char *name);
extern void *Ov107_PackTextureHandle(char *self, int index);
extern int CreateSubitemInstance0xB4(void *res);
extern char *InsertSortedEntryWithKey(int rig, int kind, const char *name);
extern void RegisterSubscriberSlot(int subscriber, int item);
extern void *CallocInstance(int size);
extern void Snd_RegisterSeqAndBind(void *binding, int model, void *res, int count);
extern void MainBlob_ResetSlotRows(int rig, void *binding);
extern void *Ov107_CreateNamedResourceBinding(void *res, const char *name);
extern int *List_InsertSorted(void *pool, int elementSize, int capacity);
extern int Ov107_Mover_New(const Capsule *capsule);
extern int Ov107_CloneResourceTransform(const Placement *placement);
extern void Ov107_EnqueueValue(char *self, int item);
extern void Res_RequestIdPair(int resourceId);
extern char *Ov255_Partner_New(char *owner);
extern IdTable data_ov255_020d29d8;
extern const char gOv255MsXionSharePackPath[];
extern const char gOv255B50B01BodyName[];
extern const char gOv255BSpine01Name[];
extern const char gOv255T2Name[];
extern const char gOv25512Swd1Name[];
extern const char data_ov255_020d2c24[];
extern const char gOv255B50BMName[];
extern const VecFx32 data_02042270;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;
extern const VecFx32 data_02041dc8;
extern u8 data_0204c240;
extern void Ov255_Destroy(void);
extern void Ov255_Update(void);
extern void Ov255_HandleMessage(void);
extern void Ov255_CreateAiTask(void);
extern void Ov255_PingAllSubNodes(void);
extern void Ov255_PingAllSubNodes_2(void);
extern void Ov255_DrawPrePass(void);
extern void Ov255_FilterHit(void);
extern void Ov255_SetMotion(void);

void Ov255_EnemyConstruct(char *self)
{
    Capsule cap;
    Placement place;
    IdTable ids = data_ov255_020d29d8;
    VecFx32 up;
    int i;
    int *slot;
    u16 hw;

    *(int *)(self + 0x3f4) = Ov107_OpenCachedResourceByName(gOv255MsXionSharePackPath);
    /* written three times: the dead copies are dropped after scheduling but spend its budget, which
     * keeps the ROM's order further down (as in Ov235_EnemyConstruct) */
    *(Callback *)(self + 0x8) = Ov255_Destroy;
    *(Callback *)(self + 0x8) = Ov255_Destroy;
    *(Callback *)(self + 0x8) = Ov255_Destroy;
    *(Callback *)(self + 0xc) = Ov255_Update;
    *(Callback *)(self + 0x1c) = Ov255_HandleMessage;
    *(Callback *)(self + 0x30) = Ov255_CreateAiTask;
    *(Callback *)(self + 0x28) = Ov255_PingAllSubNodes;
    *(Callback *)(self + 0x2c) = Ov255_PingAllSubNodes_2;
    *(Callback *)(self + 0x34) = Ov255_DrawPrePass;
    *(Callback *)(self + 0x1d0) = Ov255_FilterHit;
    *(Callback *)(self + 0x1dc) = Ov255_SetMotion;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x1a00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1a00;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    *(char **)(self + 0x3ac) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv255B50B01BodyName);
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(void **)(self + 0x388) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(void **)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), Ov107_PackTextureHandle(self, 1), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x384), *(void **)(self + 0x388));
    *(char **)(self + 0x3a8) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv255BSpine01Name);
    *(int *)(self + 0x38c) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0x24));
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(void **)(self + 0x390) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(void **)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), Ov107_PackTextureHandle(self, 0x25), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x38c), *(void **)(self + 0x390));
    *(char **)(self + 0x3b0) = InsertSortedEntryWithKey(*(int *)(self + 0x38c), 3, gOv255T2Name);
    *(char **)(self + 0x3b4) = InsertSortedEntryWithKey(*(int *)(self + 0x38c), 3, gOv25512Swd1Name);
    *(char **)(self + 0x3b8) = InsertSortedEntryWithKey(*(int *)(self + 0x38c), 3, data_ov255_020d2c24);
    *(void **)(self + 0x3a4) = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(self, 0x48), gOv255B50BMName);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    up = data_02042270;
    cap.axis = up;
    *(int **)(self + 0x394) = List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x394) = Ov107_Mover_New(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = up;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x398) = *slot = Ov107_Mover_New(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0x1200;
    cap.pos.z = 0;
    cap.axis = data_02042264;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x39c) = *slot = Ov107_Mover_New(&cap);
    cap.length = 0x3000;
    cap.radius = 0x800;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = data_02042258;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3a0) = *slot = Ov107_Mover_New(&cap);
    place.pos = data_02041dc8;
    place.scale = 0x1000;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3e8) = *slot = Ov107_CloneResourceTransform(&place);
    ((struct Nib *)*(int *)(self + 0x3e8))->hi &= ~1;
    *(struct Pair **)(self + 0x3ec) = CallocInstance(0x60);
    for (i = 0; i < 9; i++) {
        (*(struct Pair **)(self + 0x3ec))[i].res = CreateSubitemInstance0xB4((void *)((ARCHIVE_HANDLE(*(int *)(self + 0x3f4), 0))
            | (i & 0x1ff)));
        Ov107_EnqueueValue(self, (*(struct Pair **)(self + 0x3ec))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3ec))[i].res + 0x5c) |= 2;
    }
    for (; i < 12; i++) {
        (*(struct Pair **)(self + 0x3ec))[i].res = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        Ov107_EnqueueValue(self, (*(struct Pair **)(self + 0x3ec))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3ec))[i].res + 0x5c) |= 2;
    }
    *(char ***)(self + 0x3f0) = CallocInstance(0x1fa4);
    for (i = 0; i < 9; i++) {
        (*(char ***)(self + 0x3f0))[i] = Ov255_Partner_New(self);
        *(int *)((*(char ***)(self + 0x3f0))[i] + 0x3bc) = i;
    }
    *(int *)(self + 0x3f8) = (data_0204c240 & 4) ? 0x17f : 0x17a;
    Res_RequestIdPair(*(int *)(self + 0x3f8));
}
