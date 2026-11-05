
#include "game/archive.h"
#pragma opt_dead_assignments off
#pragma opt_propagation off
/* Constructor of the ov240 enemy: resolves the overlay's config into +0x384, installs the
 * handlers (+8 tick, +0xc draw, +0x1c message, +0x30 callback, +0x1d0 hit, +0x1dc config,
 * +0x1e0/+0x1e4 callbacks), seeds the +0x64 pose (scale 0x1000, y 0x1000) and the +0x1fc
 * bounding box; builds the primary item from pool entry 0 (subscribed), keeps the "move" motion
 * handle (+0x398), creates the pool entry 3/4 sub-items (+0x39c/+0x3a4, attached, bit 1), the
 * kind-1/kind-0 sub-items derived from the config (+0x3ac/+0x3b4, attached, bit 1) and the pool
 * entry 2 sub-item (+0x3bc, attached, bit 1), two placements on the +0x22c/+0x144 lists
 * (+0x38c/+0x390) and loads sound 0x139. */
typedef void (*Callback)(void);

struct Subitem {
    char pad000[0x5c];
    unsigned int flags5c;
};

struct Box {
    int xmin, ymin, zmin;
    int xmax, ymax, zmax;
};

struct Ov240Actor {
    char pad000[0x8];
    Callback fn08;
    Callback fn0c;
    char pad010[0xc];
    Callback fn1c;
    char pad020[0x10];
    Callback fn30;
    char pad034[0x30];
    int camera[4];
    char pad074[0x28];
    int subscriberList9c;
    char pad0a0[0xa4];
    char pool144[0x8c];
    Callback fn1d0;
    char pad1d4[8];
    Callback fn1dc;
    Callback fn1e0;
    Callback fn1e4;
    char pad1e8[0x14];
    struct Box box;
    char pad214[0x18];
    char pool22c[0x158];
    int config384;
    struct Subitem *subitem388;
    void **poolEntry38c;
    void *poolValue390;
    char pad394[4];
    int motion398;
    struct Subitem *subitem39c;
    char pad3a0[4];
    struct Subitem *subitem3a4;
    char pad3a8[4];
    struct Subitem *subitem3ac;
    char pad3b0[4];
    struct Subitem *subitem3b4;
    char pad3b8[4];
    struct Subitem *subitem3bc;
};

extern int Ov107_OpenCachedResourceByName(const char *buf);
extern void Ov240_ReleaseSubObjectsAndSlotsThenNotify(void);
extern void Ov240_PropagateBlockChain(void);
extern void Ov240_HandleMessage(void);
extern void Ov240_CreateNodeRegistryEntry(void);
extern void Ov240_OnHit(void);
extern void Ov240_ApplyActorConfig310(void);
extern void Ov240_RequestSubState9IfNotCurrent(void);
extern void Ov240_TryBeginSubState10IfIdle(void);
extern void *Ov107_PackTextureHandle(struct Ov240Actor *self, int index);
extern struct Subitem *CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, struct Subitem *item);
extern int Ov107_CreateNamedResourceBinding(void *item, const char *name);
extern void Ov107_EnqueueValue(struct Ov240Actor *self, struct Subitem *item);
extern void **List_InsertSorted(void *pool, int size, int count);
extern void *Ov107_CloneResourceTransform(void *camera);
extern void Res_RequestIdPair(int id);
extern const char gOv240MsNbSharePackPath[];
extern const char gOv240MoveName[];

void Ov240_InitializeActor(struct Ov240Actor *self)
{
    int minX;
    int minY;
    int minZ;
    struct Box box;
    struct Subitem *item;
    void **slot;
    void *value;

    self->config384 = Ov107_OpenCachedResourceByName(gOv240MsNbSharePackPath);
    minX = -0xeea;
    box.xmin = minX;
    minY = 0x17;
    box.ymin = minY;
    minZ = -0x858;
    box.zmin = minZ;
    box.xmax = box.xmin + 0x1dd3;
    box.ymax = box.ymin + 0x1c27;
    box.zmax = box.zmin + 0xd64;

    self->fn08 = Ov240_ReleaseSubObjectsAndSlotsThenNotify;
    self->fn0c = Ov240_PropagateBlockChain;
    self->fn1c = Ov240_HandleMessage;
    self->fn30 = Ov240_CreateNodeRegistryEntry;
    self->fn1d0 = Ov240_OnHit;
    self->fn1dc = Ov240_ApplyActorConfig310;
    self->fn1e0 = Ov240_RequestSubState9IfNotCurrent;
    self->fn1e4 = Ov240_TryBeginSubState10IfIdle;
    self->camera[3] = 0x1000;
    self->camera[0] = 0;
    self->camera[1] = 0x1000;
    self->camera[2] = 0;
    self->box = box;
    self->subitem388 = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    RegisterSubscriberSlot(self->subscriberList9c, self->subitem388);
    self->motion398 = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(self, 1), gOv240MoveName);
    item = self->subitem39c =
        CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 3));
    Ov107_EnqueueValue(self, item);
    item->flags5c |= 2;
    item = self->subitem3a4 = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 4));
    Ov107_EnqueueValue(self, item);
    item->flags5c |= 2;
    #pragma opt_scheduling off
        { struct Ov240Actor *owner = self; struct Subitem **out = &self->subitem3ac;
        item = *out = CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(self->config384, 1)));
        Ov107_EnqueueValue(owner, item); }
    item->flags5c |= 2;
    item = self->subitem3b4 = CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(self->config384, 0)));
    Ov107_EnqueueValue(self, item);
    item->flags5c |= 2;
    item = self->subitem3bc = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 2));
    Ov107_EnqueueValue(self, item);
    { struct Ov240Actor *owner = self; void *pool = self->pool22c;
        owner->poolEntry38c = List_InsertSorted(pool, (item->flags5c |= 2, 0x10), 0x64); }
    *self->poolEntry38c = Ov107_CloneResourceTransform(self->camera);
    slot = List_InsertSorted(self->pool144, 4, 0x64);
    value = (*slot = Ov107_CloneResourceTransform(self->camera));
    self->poolValue390 = value;
    Res_RequestIdPair(0x139);
}
