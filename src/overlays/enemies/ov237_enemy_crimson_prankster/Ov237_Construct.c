/* Constructor of the ov237 enemy (and of its split partner). Installs the handlers (+8, +0xc, +0x1c
 * message, +0x20, +0x28, +0x2c, +0x30, +0x34 update, +0x48, +0x1d0 damage, +0x1dc, +0x1ec hit relay,
 * +0x1f0) and the +0x1fc bounds (-0.67 / 0.005 / -0.88 to 0.67 / 6.83 / 1.24), kind 1, bit 5 set and bit 6
 * cleared in the +0x60 high byte, bit 3 of +0x1ae, a 2.3 radius and the +0x64 pose. Builds the +0x384
 * body rig (pose 0, work list 1 at +0x388) with four bones (+0x444, +0x448, +0x44c, +0x3d4) and the
 * +0x3ac arm rig (pose 0x1a) with five joints for each arm (+0x41c, names data_ov237_020d19f8) and
 * work list 0x1b (+0x3b0) plus two bones (+0x454, +0x458); a 1/2 grab reach (+0x58); the 19 hidden
 * sub-items of data_ov237_020d1a20 in the +0x490 pair table; the 0x47 hand item (+0x3d8). Shapes: a
 * 1.25 placement (+0x488) and a unit capsule (+0x48c) on the +0x22c pool, a 0.5 placement (+0x3ec), a
 * unit capsule (+0x3f0) and ten 0.375 arm capsules (+0x3f4 / +0x408) on the +0x144 pool. Creates the
 * shot (020d0ab0, +0x3e0), the 0x3b effect rig (+0x3e4, hooked to 020cbfc4) and the spark emitter
 * (+0x3e8). The first one built also creates its partner ("Ms/40", +0x4a4, +0x4ac / +0x4b0 set), then
 * loads sound 0x12d. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*Callback)(void);
typedef struct { VecFx32 min; VecFx32 max; } Bounds;
typedef struct { VecFx32 pos; int scale; } Placement;
typedef struct { VecFx32 pos; VecFx32 axis; int length; int radius; } Capsule;
typedef struct { const char *name[2][5]; } JointNames;
typedef struct { int id[19]; } IdTable19;
struct Pair { int res; int handle; };
struct Ov237Body { char pad[0x3f4]; int arms[2][5]; int joints[2][5]; };

extern void Ov237_Actor_Destroy(void);
extern void Ov237_TickModelAndTransform(void);
extern void Ov237_SendMessage26(void);
extern void Ov237_OnMessage(void);
extern void Ov237_CreateBrain(void);
extern void Ov237_Update(void);
extern void Ov237_ForwardRegionEventToParts(void);
extern void Ov237_NotifyPartsThenBase(void);
extern void func_ov237_020cc800(void);
extern void Ov237_OnDamage(void);
extern void Ov237_PlayRigMove(void);
extern void Ov237_HitRelay(void);
extern void Ov237_NotifyPartnerThenBase(void);
extern void Ov237_DrawRingMarkEmpty(void);
extern void Ov237_Construct(char *self);
extern void *Ov107_PackTextureHandle(char *self, int index);
extern int CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, int item);
extern void Snd_RegisterSeqAndBind(void *slot, int bank, void *record, int d);
extern void MainBlob_ResetSlotRows(int rig, void *slot);
extern int InsertSortedEntryWithKey(int item, int kind, const char *name);
extern int CallocInstance(int size);
extern void Ov107_EnqueueValue(char *self, int item);
extern int Ov107_CreateNamedResourceBinding(void *item, const char *name);
extern int *List_InsertSorted(void *pool, int elementSize, int capacity);
extern int Ov107_Mover_New(const Capsule *capsule);
extern int Ov107_CloneResourceTransform(const Placement *placement);
extern int Ov237_New(char *self);
extern int JointModel_New(void *record, int kind);
extern int Ov237_CreateSparkEmitter(char *self);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int Ov107_OpenCachedResourceByName(char *buf);
extern void func_ov107_020c6624(int obj, int arg);
extern void Res_RequestIdPair(int resourceId);
extern const JointNames data_ov237_020d19f8;
extern const IdTable19 data_ov237_020d1a20;
extern const char gOv237PackPathFmt[];
extern const char gOv237BoneHeadName[];
extern const char gOv237031AName[];
extern const char gOv237BoneNeckName[];
extern const char gOv237BTagName[];
extern const char gOv237Tag00Name[];
extern const char gOv237Tag01Name[];
extern const char gOv237MoveName[];
/* read through a const view: lets the check load hoist above the effect-rig stores (ROM order) */
extern const signed char data_ov237_020d1ce0;
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;

void Ov237_Construct(char *self)
{
    IdTable19 ids;
    JointNames names;
    Bounds bounds;
    Placement place;
    Capsule cap;
    VecFx32 zero;
    VecFx32 up;
    int k;
    int i;
    int *slot;

    names = data_ov237_020d19f8;
    ids = data_ov237_020d1a20;
    bounds.min.x = -0xabd;
    bounds.min.y = 0x15;
    bounds.min.z = -0xe0c;
    bounds.max.x = bounds.min.x + 0x157a;
    bounds.max.y = bounds.min.y + 0x6d37;
    bounds.max.z = bounds.min.z + 0x21ee;
    *(Callback *)(self + 0x8) = Ov237_Actor_Destroy;
    *(Callback *)(self + 0xc) = Ov237_TickModelAndTransform;
    *(Callback *)(self + 0x20) = Ov237_SendMessage26;
    *(Callback *)(self + 0x1c) = Ov237_OnMessage;
    *(Callback *)(self + 0x30) = Ov237_CreateBrain;
    *(Callback *)(self + 0x34) = Ov237_Update;
    *(Callback *)(self + 0x28) = Ov237_ForwardRegionEventToParts;
    *(Callback *)(self + 0x2c) = Ov237_NotifyPartsThenBase;
    *(Callback *)(self + 0x48) = func_ov237_020cc800;
    *(Callback *)(self + 0x1d0) = Ov237_OnDamage;
    *(Callback *)(self + 0x1dc) = Ov237_PlayRigMove;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(u8 *)(self + 0x1c9) = 1;
    *(Callback *)(self + 0x1ec) = Ov237_HitRelay;
    *(Callback *)(self + 0x1f0) = Ov237_NotifyPartnerThenBase;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 8;
    *(int *)(self + 0x70) = 0x2500;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2500;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x1ae) |= 8;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    Snd_RegisterSeqAndBind(self + 0x388, *(int *)(*(int *)(self + 0x384) + 0x88), Ov107_PackTextureHandle(self, 1), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x384), self + 0x388);
    *(int *)(self + 0x444) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv237BoneHeadName);
    *(int *)(self + 0x448) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv237031AName);
    *(int *)(self + 0x44c) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 1, gOv237BoneNeckName);
    *(int *)(self + 0x3d4) = InsertSortedEntryWithKey(*(int *)(self + 0x384), 3, gOv237BTagName);
    *(int *)(self + 0x3ac) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0x1a));
    for (k = 0; k < 2; k++) {
        for (i = 0; i < 5; i++) {
            ((struct Ov237Body *)self)->joints[k][i] = InsertSortedEntryWithKey(*(int *)(self + 0x3ac), 1, names.name[k][i]);
        }
    }
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x3ac));
    Snd_RegisterSeqAndBind(self + 0x3b0, *(int *)(*(int *)(self + 0x3ac) + 0x88), Ov107_PackTextureHandle(self, 0x1b), 0xc);
    MainBlob_ResetSlotRows(*(int *)(self + 0x3ac), self + 0x3b0);
    *(int *)(self + 0x454) = InsertSortedEntryWithKey(*(int *)(self + 0x3ac), 3, gOv237Tag00Name);
    *(int *)(self + 0x458) = InsertSortedEntryWithKey(*(int *)(self + 0x3ac), 3, gOv237Tag01Name);
    *(int *)(self + 0x58) = 0x800;
    *(int *)(self + 0x490) = CallocInstance(0x98);
    for (i = 0; i < 0x13; i++) {
        ((struct Pair *)*(int *)(self + 0x490))[i].res = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        Ov107_EnqueueValue(self, ((struct Pair *)*(int *)(self + 0x490))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x490))[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x3d8) = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(self, 0x47), gOv237MoveName);
    *(int *)(self + 0x4b0) = 0;
    *(int *)(self + 0x4ac) = 0;
    zero = data_02041dc8;
    place.pos = zero;
    place.scale = 0x1400;
    *(int *)(self + 0x488) = (int)List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x488) = Ov107_CloneResourceTransform(&place);
    cap.pos = zero;
    up = data_02042264;
    cap.axis = up;
    cap.length = 0x1000;
    cap.radius = 0x1000;
    *(int *)(self + 0x48c) = (int)List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x48c) = Ov107_Mover_New(&cap);
    place.pos = zero;
    place.scale = 0x800;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3ec) = *slot = Ov107_CloneResourceTransform(&place);
    cap.pos = zero;
    cap.axis = up;
    cap.length = 0x1000;
    cap.radius = 0x1000;
    slot = List_InsertSorted(self + 0x144, 4, 100);
    *(int *)(self + 0x3f0) = *slot = Ov107_Mover_New(&cap);
    cap.pos = zero;
    cap.axis = up;
    cap.length = 0x1000;
    cap.radius = 0x600;
    for (i = 0; i < 5; i++) {
        slot = List_InsertSorted(self + 0x144, 4, 100);
        ((struct Ov237Body *)self)->arms[0][i] = *slot = Ov107_Mover_New(&cap);
        slot = List_InsertSorted(self + 0x144, 4, 100);
        ((struct Ov237Body *)self)->arms[1][i] = *slot = Ov107_Mover_New(&cap);
    }
    *(int *)(self + 0x3e0) = Ov237_New(self);
    *(int *)(*(int *)(*(int *)(self + 0x3e0) + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x3e4) = JointModel_New(Ov107_PackTextureHandle(self, 0x3b), 5);
    Ov107_EnqueueValue(self, *(int *)(self + 0x3e4));
    *(int *)(self + 0x3e8) = Ov237_CreateSparkEmitter(self);
    *(Callback *)(*(int *)(self + 0x3e4) + 0x6c) = Ov237_DrawRingMarkEmpty;
    *(char **)(*(int *)(self + 0x3e4) + 0x84) = self;
    *(int *)(*(int *)(self + 0x3e4) + 0x5c) |= 2;
    if (data_ov237_020d1ce0 == 0) {
        char buf[0x1d] = {0};

        *(int *)(self + 0x4b0) = 1;
        *(int *)(self + 0x4ac) = 1;
        *(signed char *)&data_ov237_020d1ce0 = 1;
        *(int *)(self + 0x4a4) = CallocInstance(0x4d0);
        *(u8 *)(*(int *)(self + 0x4a4) + 0x19c) = 0x40;
        OS_SPrintf(buf, gOv237PackPathFmt, *(u8 *)(*(int *)(self + 0x4a4) + 0x19c));
        *(int *)(*(int *)(self + 0x4a4) + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
        *(void **)(*(int *)(self + 0x4a4) + 0x18c) = Ov237_Construct;
        func_ov107_020c6624(*(int *)(self + 0x4a4), *(int *)(self + 0x1a0));
        *(u16 *)(*(int *)(self + 0x4a4) + 0x1ae) |= 8;
    }
    Res_RequestIdPair(0x12d);
}
