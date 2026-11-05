/* Ov235_EnemyConstruct = Ov235_EnemyConstruct. Constructor of the ov235 enemy: looks up its effect resource (+0x3c0), installs its handlers
 * (+8 update, +0xc draw, +0x1c message, +0x28, +0x2c, +0x30, +0x34, +0x1d0 hit filter, +0x1dc
 * motion set), raises bit 3 of +0x1ae and bit 5 of the +0x60 high byte and sets the +0x64 pose
 * (scale 1.5). It builds three rigs with their bindings -- body (+0x384/+0x388, pose 0, 1),
 * head (+0x394/+0x398, poses 0x50, 0x51) and wings (+0x38c/+0x390, poses 0x28, 0x29) -- and
 * resolves the +0x3b0, +0x3ac and +0x3b4 parts, the +0x3a8 motion part (pose 0x78), three
 * collision capsules (+0x39c, +0x3a0, +0x3a4; radius 1.125, length 0.625) and a +0x3b8 placement
 * (hidden), then the eleven effect pairs of +0x3bc (the first eight from the effect resource, the
 * rest from the data_ov235_020d22d0 poses; all hidden) and loads the voice bank (+0x3c8: 0x17f
 * in the alternate language, else 0x17a). */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef void (*Callback)(void);
typedef struct { int id[11]; } IdTable;
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
extern IdTable data_ov235_020d22d0;
extern const char gOv235MsXionSharePackPath[];
extern const char gOv235B50A01BodyName[];
extern const char gOv235BSpine01Name[];
extern const char gOv23511SwordName[];
extern const char gOv235B50AMName[];
extern const VecFx32 data_02042270;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02041dc8;
extern u8 data_0204c240;
extern void Ov235_Destroy(void);
extern void Ov235_TickWithChildRefresh(void);
extern void Ov235_HandleMessage(void);
extern void Ov235_CreateRegistryEntryAndLink(void);
/* ov235 handlers 020cc8a0 / 020cc8ac; the symbol table names them after an SDK routine */
extern void func_ov235_020cc8a0(void);
extern void func_ov235_020cc8ac(void);
extern void Ov235_DrawPrePass(void);
extern void Ov235_FilterHit(void);
extern void Ov235_SetMotion(void);

void Ov235_EnemyConstruct(char *self)
{
    Capsule cap;
    Placement place;
    IdTable ids = data_ov235_020d22d0;
    VecFx32 up;
    int i;
    int *slot;
    u16 hw;

    *(int *)(self + 0x3c0) = Ov107_OpenCachedResourceByName(gOv235MsXionSharePackPath);
    /* The first handler is stored five times (two statements and a triple chained assignment): the
     * dead copies are dropped after scheduling but spend its budget, which keeps the ROM's order
     * further down (as in Ov261_EnemyConstruct). */
    *(Callback *)(self + 0x8) = Ov235_Destroy;
    *(Callback *)(self + 0x8) = Ov235_Destroy;
    *(Callback *)(self + 0x8) = *(Callback *)(self + 0x8) = *(Callback *)(self + 0x8) = Ov235_Destroy;
    *(Callback *)(self + 0xc) = Ov235_TickWithChildRefresh;
    *(Callback *)(self + 0x1c) = Ov235_HandleMessage;
    *(Callback *)(self + 0x30) = Ov235_CreateRegistryEntryAndLink;
    *(Callback *)(self + 0x28) = func_ov235_020cc8a0;
    *(Callback *)(self + 0x2c) = func_ov235_020cc8ac;
    *(Callback *)(self + 0x34) = Ov235_DrawPrePass;
    *(Callback *)(self + 0x1d0) = Ov235_FilterHit;
    *(Callback *)(self + 0x1dc) = Ov235_SetMotion;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x1800;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1800;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    *(char **)(self + 0x3b0) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv235B50A01BodyName);
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(void **)(self + 0x388) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(void **)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), Ov107_PackTextureHandle(self, 1), 0xc);
    slot = (int *)(self + 0x9c);    /* the owner, through the same slot local as the placements below */
    MainBlob_ResetSlotRows(*(int *)(self + 0x384), *(void **)(self + 0x388));
    *(char **)(self + 0x3ac) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv235BSpine01Name);
    *(int *)(self + 0x394) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0x50));
    RegisterSubscriberSlot(*slot, *(int *)(self + 0x394));
    *(void **)(self + 0x398) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(void **)(self + 0x398), *(int *)(*(int *)(self + 0x394) + 0x88), Ov107_PackTextureHandle(self, 0x51), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x394), *(void **)(self + 0x398));
    *(char **)(self + 0x3b4) = InsertSortedEntryWithKey(*(int *)(self + 0x394), 3, gOv23511SwordName);
    *(int *)(self + 0x38c) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0x28));
    RegisterSubscriberSlot(*slot, *(int *)(self + 0x38c));
    *(void **)(self + 0x390) = CallocInstance(0x24);
    Snd_RegisterSeqAndBind(*(void **)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), Ov107_PackTextureHandle(self, 0x29), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x38c), *(void **)(self + 0x390));
    *(void **)(self + 0x3a8) = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(self, 0x78), gOv235B50AMName);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    up = data_02042270;
    cap.axis = up;
    *(int **)(self + 0x39c) = List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x39c) = Ov107_Mover_New(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = up;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3a0) = *slot = Ov107_Mover_New(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0x1200;
    cap.pos.z = 0;
    cap.axis = data_02042264;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3a4) = *slot = Ov107_Mover_New(&cap);
    place.pos = data_02041dc8;
    place.scale = 0x1000;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3b8) = *slot = Ov107_CloneResourceTransform(&place);
    ((struct Nib *)*(int *)(self + 0x3b8))->hi &= ~1;
    *(struct Pair **)(self + 0x3bc) = CallocInstance(0x58);
    for (i = 0; i < 8; i++) {
        (*(struct Pair **)(self + 0x3bc))[i].res = CreateSubitemInstance0xB4((void *)((ARCHIVE_HANDLE(*(int *)(self + 0x3c0), 0))
            | (i & 0x1ff)));
        Ov107_EnqueueValue(self, (*(struct Pair **)(self + 0x3bc))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3bc))[i].res + 0x5c) |= 2;
    }
    for (; i < 11; i++) {
        (*(struct Pair **)(self + 0x3bc))[i].res = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        Ov107_EnqueueValue(self, (*(struct Pair **)(self + 0x3bc))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3bc))[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x3c8) = (data_0204c240 & 4) ? 0x17f : 0x17a;
    Res_RequestIdPair(*(int *)(self + 0x3c8));
}
