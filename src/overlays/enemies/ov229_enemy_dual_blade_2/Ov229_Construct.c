/* Constructor of the ov229 enemy. Installs the handlers (+8, +0xc, +0x1c message, +0x28, +0x2c, +0x30,
 * +0x34, +0x1d0, +0x1dc, +0x1e0, +0x1e4), the +0x1fc bounds box, the +0x64 pose (scale 2.0) and bit 3
 * of +0x1ae; builds the +0x3a8 rig from pose 0 (owned by the enemy, callback 020d1a28, subscribed to
 * +0x9c), binds its +0x384 animation (pose 1, 12 frames), resolves two bones (+0x3b4, +0x3b8) and
 * resets the four transforms at +0x3e0..+0x464; the +0x490 bone of pose 0x1c; builds the ten sub-items
 * of data_ov229_020d686c into the +0x4a8 pair table (the first from the shared scene resource, the
 * others with texture frames 3..30 cycling); registers action 2/3 lowered 2.0 (rate 0.6), 1/2 (0.8)
 * and 4/2 (1.0); reserves the +0x22c/+0x144 handles of a placement of scale 2.0 (+0x3ac, +0x3b0),
 * creates the eight +0x3c0 projectiles (020d5c84) and loads sound 0x12b. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef void (*Callback)(void);
typedef struct { int w[11]; } SrtTransform;
typedef struct { int id[10]; } IdTable;
typedef struct { VecFx32 min; VecFx32 max; } Bounds;
typedef struct { VecFx32 pos; int scale; } Placement;
struct Pair { int res; int handle; };
struct Pairs { char pad[0x4a8]; struct Pair pairs[10]; };
struct Xforms { char pad[0x40c]; SrtTransform xf[2]; };
struct Shots { char pad[0x3c0]; int shots[8]; };

extern void Ov229_Destroy(void);
extern void Ov229_TickAndUpdateAnchor(void);
extern void Ov229_OnEffectMessage(void);
extern void Ov229_CreateNodeRegistryEntry(void);
extern void Ov229_ForwardEventToChildren(void);
extern void Ov229_NotifyPartsThenBase(void);
extern void Ov229_PostTickCleanup(void);
extern void Ov229_OnHit(void);
extern void Ov229_RebindClip(void);
extern void Ov229_RequestSubState12IfNotCurrent(void);
extern void Ov229_RequestSubState13IfIdle(void);
extern void Ov229_SyncEffectNodesToJoints(void);
extern void *Ov107_PackTextureHandle(char *self, int index);
extern int CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, int item);
extern void Snd_RegisterSeqAndBind(void *dst, int a, void *b, int n);
extern void MainBlob_ResetSlotRows(int obj, void *block);
extern int FindResourceIndexByName(int item, const char *name);
extern void RefreshObjectCallbacks(int item, int a);
extern void SrtTransform_SetIdentity(void *transform);
extern int Ov107_CreateNamedResourceBinding(void *item, const char *name);
extern char *Ov107_GetActorManager(void);
extern void Ov107_EnqueueValue(char *self, int item);
extern void NNS_G3dMdlSetMdlPolygonID(int a, int b, int c);
extern void Ov107_Actor_SetAttachSlot(char *self, int slot, int a, const VecFx32 *v, int c);
extern int *List_InsertSorted(void *pool, int elementSize, int capacity);
extern int Ov107_CloneResourceTransform(const Placement *placement);
extern int Ov229_Companion_New(char *self);
extern void Res_RequestIdPair(int resourceId);
extern IdTable data_ov229_020d686c;
extern const char gOv229Bip01Spine1Name[];
extern const char gOv229Bip01LHandName[];
extern const char gOv229AMoveName[];
extern const VecFx32 data_02041dc8;

void Ov229_Construct(char *self)
{
    IdTable ids = data_ov229_020d686c;
    Bounds bounds;
    Placement place;
    VecFx32 lift;
    int i;
    int frame = 3;
    int node;
    int *slot;

    bounds.min.x = -0x1c7c;
    bounds.min.y = 0;
    bounds.min.z = -0xa44;
    bounds.max.x = bounds.min.x + 0x38f9;
    bounds.max.y = bounds.min.y + 0x20a8;
    bounds.max.z = bounds.min.z + 0x107a;
    *(Callback *)(self + 0x8) = Ov229_Destroy;
    *(Callback *)(self + 0xc) = Ov229_TickAndUpdateAnchor;
    *(Callback *)(self + 0x1c) = Ov229_OnEffectMessage;
    *(Callback *)(self + 0x30) = Ov229_CreateNodeRegistryEntry;
    *(Callback *)(self + 0x28) = Ov229_ForwardEventToChildren;
    *(Callback *)(self + 0x2c) = Ov229_NotifyPartsThenBase;
    *(Callback *)(self + 0x34) = Ov229_PostTickCleanup;
    *(Callback *)(self + 0x1d0) = Ov229_OnHit;
    *(Callback *)(self + 0x1dc) = Ov229_RebindClip;
    *(Callback *)(self + 0x1e0) = Ov229_RequestSubState12IfNotCurrent;
    *(Callback *)(self + 0x1e4) = Ov229_RequestSubState13IfIdle;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2000;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x3a8) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    *(Callback *)(*(int *)(self + 0x3a8) + 0x74) = Ov229_SyncEffectNodesToJoints;
    *(char **)(*(int *)(self + 0x3a8) + 0x84) = self;
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x3a8));
    {
        void *anim = Ov107_PackTextureHandle(self, 1);

        Snd_RegisterSeqAndBind(self + 0x384, *(int *)(*(int *)(self + 0x3a8) + 0x88), anim, 0xc);
    }
    MainBlob_ResetSlotRows(*(int *)(self + 0x3a8), self + 0x384);
    *(int *)(self + 0x3b4) = FindResourceIndexByName(*(int *)(self + 0x3a8), gOv229Bip01Spine1Name);
    *(int *)(self + 0x3b8) = FindResourceIndexByName(*(int *)(self + 0x3a8), gOv229Bip01LHandName);
    RefreshObjectCallbacks(*(int *)(self + 0x3a8), 0);
    SrtTransform_SetIdentity(self + 0x3e0);
    SrtTransform_SetIdentity(self + 0x464);
    for (i = 0; i < 2; i++) {
        SrtTransform_SetIdentity(&((struct Xforms *)self)->xf[i]);
    }
    *(int *)(self + 0x490) = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(self, 0x1c), gOv229AMoveName);
    for (i = 0; i < 10; i++) {
        if (i < 1) {
            node = CreateSubitemInstance0xB4((void *)((ids.id[i] & 0x1ff)
                | (ARCHIVE_HANDLE(*(int *)(Ov107_GetActorManager() + 0x88), 0))));
        } else {
            node = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, ids.id[i]));
        }
        Ov107_EnqueueValue(self, ((struct Pairs *)self)->pairs[i].res = node);
        *(int *)(((struct Pairs *)self)->pairs[i].res + 0x5c) |= 2;
        if (i >= 1) {
            NNS_G3dMdlSetMdlPolygonID(*(int *)(*(int *)(((struct Pairs *)self)->pairs[i].res + 0x88) + 0x78), 0, frame);
            frame++;
            if (frame >= 0x1f) {
                frame = 3;
            }
        }
    }
    lift.x = 0;
    lift.y = -0x2000;
    lift.z = 0;
    Ov107_Actor_SetAttachSlot(self, 2, 3, &lift, 0x99a);
    Ov107_Actor_SetAttachSlot(self, 1, 2, 0, 0xccd);
    Ov107_Actor_SetAttachSlot(self, 4, 2, 0, 0x1000);
    place.pos = data_02041dc8;
    place.scale = 0x2000;
    *(int **)(self + 0x3ac) = List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3ac) = Ov107_CloneResourceTransform(&place);
    slot = List_InsertSorted(self + 0x144, 4, 100);
    node = Ov107_CloneResourceTransform(&place);
    *(int *)(self + 0x3b0) = *slot = node;
    for (i = 0; i < 8; i++) {
        ((struct Shots *)self)->shots[i] = Ov229_Companion_New(self);
    }
    Res_RequestIdPair(0x12b);
}
