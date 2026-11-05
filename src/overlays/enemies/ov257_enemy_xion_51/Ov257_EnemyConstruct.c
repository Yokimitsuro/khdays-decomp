/* Ov257_EnemyConstruct = Ov257_EnemyConstruct. Constructor of the ov257 enemy (sibling of the ov235 and
 * ov255 constructors): looks up its effect resource (+0x404), installs its handlers (+8 update, +0xc
 * draw, +0x10, +0x1c message, +0x28, +0x2c, +0x30, +0x34, +0x1d0 hit filter, +0x1dc motion set),
 * raises bit 3 of +0x1ae and bit 5 of the +0x60 high byte and sets the +0x64 pose (scale 2.0). It
 * builds two rigs with their bindings -- body (+0x384/+0x388, poses 0, 1) and arms (+0x38c/+0x390,
 * poses 0x23, 0x24) -- resolves the +0x3d8 and +0x3d4 body parts and, on the arms rig, the four
 * +0x3dc (kind 1) and +0x3ec (kind 3) parts named by data_ov257_020d3074/020d3084; subscribes the
 * four +0x394 items of the data_ov257_020d3064 poses and attaches four +0x3a4 pose-0x4b items (all
 * hidden, +0x3a4 ones flagged), keeps the +0x3d0 motion part (pose 0x46), three collision capsules
 * (+0x3b4, +0x3b8, +0x3bc) plus four thin ones (+0x3c0..+0x3cc) and a +0x3fc placement (hidden), then
 * the twelve effect pairs of +0x400 (nine from the effect resource, three from the
 * data_ov257_020d3094 poses) and loads the voice bank (+0x408: 0x17f in the alternate language,
 * else 0x17a). */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef void (*Callback)(void);
typedef struct { int id[12]; } IdTable;
typedef struct { int id[4]; } IdTable4;
typedef struct { void *name[4]; } NameTable4;
typedef struct { VecFx32 pos; int scale; } Placement;
typedef struct { VecFx32 pos; VecFx32 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
struct Nib { u8 lo : 4, hi : 4; };
struct Bit0 { unsigned bit0 : 1; };

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
extern IdTable4 data_ov257_020d3064;
extern NameTable4 data_ov257_020d3074;
extern NameTable4 data_ov257_020d3084;
extern IdTable data_ov257_020d3094;
extern const char gOv257MsXionSharePackPath[];
extern const char gOv25700Name[];
extern const char gOv257BSpine01Name[];
extern const char gOv257B50CMName[];
extern const VecFx32 data_02042270;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;
extern const VecFx32 data_02041dc8;
extern u8 data_0204c240;
extern void Ov257_Actor_Destroy(void);
extern void Ov257_TickWithChildRefresh(void);
extern void Ov257_DrawPrePass(void);
extern void Ov257_HandleMessage(void);
extern void Ov257_CreateAiTask(void);
/* ov257 handlers 020cca20 / 020cca2c; the symbol table names them after an SDK routine */
extern void func_ov257_020cca20(void);
extern void func_ov257_020cca2c(void);
extern void Ov257_DrawPrePass2(void);
extern void Ov257_FilterHit(void);
extern void Ov257_SetMotion(void);

void Ov257_EnemyConstruct(char *self)
{
    Capsule cap;
    Placement place;
    IdTable ids = data_ov257_020d3094;
    IdTable4 armIds = data_ov257_020d3064;
    NameTable4 names1;
    NameTable4 names3;
    VecFx32 up;
    int i;
    int *slot;
    u16 hw;

    *(int *)(self + 0x404) = Ov107_OpenCachedResourceByName(gOv257MsXionSharePackPath);
    /* written three times: the dead copies are dropped after scheduling but spend its budget, which
     * keeps the ROM's order further down (as in Ov255_EnemyConstruct) */
    *(Callback *)(self + 0x8) = Ov257_Actor_Destroy;
    *(Callback *)(self + 0x8) = Ov257_Actor_Destroy;
    *(Callback *)(self + 0x8) = Ov257_Actor_Destroy;
    *(Callback *)(self + 0xc) = Ov257_TickWithChildRefresh;
    *(Callback *)(self + 0x10) = Ov257_DrawPrePass;
    *(Callback *)(self + 0x1c) = Ov257_HandleMessage;
    *(Callback *)(self + 0x30) = Ov257_CreateAiTask;
    *(Callback *)(self + 0x28) = func_ov257_020cca20;
    *(Callback *)(self + 0x2c) = func_ov257_020cca2c;
    *(Callback *)(self + 0x34) = Ov257_DrawPrePass2;
    *(Callback *)(self + 0x1d0) = Ov257_FilterHit;
    *(Callback *)(self + 0x1dc) = Ov257_SetMotion;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2000;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    *(char **)(self + 0x3d8) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv25700Name);
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(void **)(self + 0x388) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(void **)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), Ov107_PackTextureHandle(self, 1), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x384), *(void **)(self + 0x388));
    *(char **)(self + 0x3d4) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv257BSpine01Name);
    *(int *)(self + 0x38c) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0x23));
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(void **)(self + 0x390) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(void **)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), Ov107_PackTextureHandle(self, 0x24), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x38c), *(void **)(self + 0x390));
    names1 = data_ov257_020d3074;
    names3 = data_ov257_020d3084;
    for (i = 0; i < 4; i++) {
        ((char **)(self + 0x3dc))[i] = InsertSortedEntryWithKey(*(int *)(self + 0x38c), 1, names1.name[i]);
        ((char **)(self + 0x3ec))[i] = InsertSortedEntryWithKey(*(int *)(self + 0x38c), 3, names3.name[i]);
    }
    for (i = 0; i < 4; i++) {
        ((int *)(self + 0x394))[i] = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, armIds.id[i]));
        RegisterSubscriberSlot(*(int *)(self + 0x9c), ((int *)(self + 0x394))[i]);
        *(int *)(((int *)(self + 0x394))[i] + 0x5c) |= 2;
    }
    for (i = 0; i < 4; i++) {
        ((int *)(self + 0x3a4))[i] = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0x4b));
        Ov107_EnqueueValue(self, ((int *)(self + 0x3a4))[i]);
        *(int *)(((int *)(self + 0x3a4))[i] + 0x5c) |= 2;
        ((struct Bit0 *)(((int *)(self + 0x3a4))[i] + 0x5c))->bit0 = 1;
    }
    *(void **)(self + 0x3d0) = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(self, 0x46), gOv257B50CMName);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    up = data_02042270;
    cap.axis = up;
    *(int **)(self + 0x3b4) = List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3b4) = Ov107_Mover_New(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1600;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = up;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3b8) = *slot = Ov107_Mover_New(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1600;
    cap.pos.x = 0;
    cap.pos.y = 0x1600;
    cap.pos.z = 0;
    cap.axis = data_02042264;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3bc) = *slot = Ov107_Mover_New(&cap);
    cap.length = 0x2c00;
    cap.radius = 0x600;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = data_02042258;
    for (i = 0; i < 4; i++) {
        slot = List_InsertSorted(self + 0x144, 4, 100);
        ((int *)(self + 0x3c0))[i] = *slot = Ov107_Mover_New(&cap);
    }
    place.pos = data_02041dc8;
    place.scale = 0x1000;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3fc) = *slot = Ov107_CloneResourceTransform(&place);
    ((struct Nib *)*(int *)(self + 0x3fc))->hi &= ~1;
    *(struct Pair **)(self + 0x400) = CallocInstance(0x60);
    for (i = 0; i < 9; i++) {
        (*(struct Pair **)(self + 0x400))[i].res = CreateSubitemInstance0xB4((void *)((ARCHIVE_HANDLE(*(int *)(self + 0x404), 0))
            | (i & 0x1ff)));
        Ov107_EnqueueValue(self, (*(struct Pair **)(self + 0x400))[i].res);
        *(int *)((*(struct Pair **)(self + 0x400))[i].res + 0x5c) |= 2;
    }
    for (; i < 12; i++) {
        (*(struct Pair **)(self + 0x400))[i].res = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        Ov107_EnqueueValue(self, (*(struct Pair **)(self + 0x400))[i].res);
        *(int *)((*(struct Pair **)(self + 0x400))[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x408) = (data_0204c240 & 4) ? 0x17f : 0x17a;
    Res_RequestIdPair(*(int *)(self + 0x408));
}
