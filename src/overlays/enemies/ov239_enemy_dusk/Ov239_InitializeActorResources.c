/* Install callbacks and bounds; create actor resources, six subitems and two transform descriptors;
 * request pair 0x138. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef struct Ov239ResourceTransform {
    VecFx32 position;
    int scale;
} Ov239ResourceTransform;

typedef struct Ov239ActorBounds {
    int minX;
    int minY;
    int minZ;
    int maxX;
    int maxY;
    int maxZ;
} Ov239ActorBounds;

typedef struct Ov239Subitem {
    unsigned char pad00[0x5c];
    u32 flags;
} Ov239Subitem;

typedef struct Ov239SubitemSlot {
    Ov239Subitem *item;
    int state;
} Ov239SubitemSlot;

typedef struct Ov239Actor {
    unsigned char pad000[0x08];
    void (*release)(void);
    void (*propagateBlockChain)(void);
    unsigned char pad010[0x0c];
    void (*handleMessage)(void);
    unsigned char pad020[0x10];
    void (*createNodeRegistryEntry)(void);
    void (*advanceSubState)(void);
    unsigned char pad038[0x2c];
    int camera[4];
    unsigned char pad074[0x28];
    void *subscriberOwner;
    unsigned char pad0a0[0xa4];
    unsigned char descriptorSlotPool[0x8c];
    void (*onHit)(void);
    unsigned char pad1d4[0x08];
    void (*applyActorConfig)(void);
    void (*requestSubState8)(void);
    void (*requestSubState9)(void);
    unsigned char pad1e8[0x14];
    Ov239ActorBounds actorBounds;
    unsigned char pad214[0x18];
    unsigned char subitemSlotPool[0x158];
    int cachedResourceId;
    Ov239Subitem *primarySubitem;
    void **primaryDescriptorSlot;
    void *resourceDescriptor;
    unsigned char pad394[0x04];
    void *moveBinding;
    Ov239Subitem *subitem39c;
    int subitemState3a0;
    Ov239Subitem *subitem3a4;
    int subitemState3a8;
    Ov239Subitem *subitem3ac;
    int subitemState3b0;
    Ov239Subitem *subitem3b4;
    int subitemState3b8;
} Ov239Actor;

extern int Ov107_OpenCachedResourceByName(const void *name);
extern void *Ov107_PackTextureHandle(Ov239Actor *actor, int kind);
extern Ov239Subitem *CreateSubitemInstance0xB4(void *packedHandle);
extern int RegisterSubscriberSlot(void *owner, Ov239Subitem *subitem);
extern void *Ov107_CreateNamedResourceBinding(void *packedHandle, const void *name);
extern void Ov107_EnqueueValue(Ov239Actor *actor, Ov239Subitem *subitem);
extern void **List_InsertSorted(void *pool, int stride, int priority);
extern void *Ov107_CloneResourceTransform(const Ov239ResourceTransform *transform);
extern void Res_RequestIdPair(int resourceId);

extern void Ov239_ReleaseSubObjectsAndSlotsThenNotify(void);
extern void Ov239_PropagateBlockChain(void);
extern void Ov239_HandleMessage(void);
extern void Ov239_CreateNodeRegistryEntry(void);
extern void Ov239_MaybeForceSubState7ThenAdvance(void);
extern void Ov239_OnHit(void);
extern void Ov239_ApplyActorConfig310(void);
extern void Ov239_RequestSubState8IfNotAlready(void);
extern void Ov239_RequestSubState9IfIdle(void);
extern const char gOv239MsNbSharePackPath[];
extern const char gOv239MoveName[];

#pragma opt_dead_assignments off
void Ov239_InitializeActorResources(Ov239Actor *actor)
{
    int minX;
    int minY;
    int minZ;
    Ov239ActorBounds bounds;
    Ov239Subitem *subitem;
    void **descriptorSlot;
    void *descriptor;

    actor->cachedResourceId = Ov107_OpenCachedResourceByName(gOv239MsNbSharePackPath);
    minX = -0xeea;
    minY = 0x17;
    minZ = -0x858;
    bounds.minX = minX;
    bounds.minY = minY;
    bounds.minZ = minZ;
    bounds.maxX = bounds.minX + 0x1dd3;
    bounds.maxY = bounds.minY + 0x1c27;
    bounds.maxZ = bounds.minZ + 0xd64;
    actor->release = Ov239_ReleaseSubObjectsAndSlotsThenNotify;
    actor->propagateBlockChain = Ov239_PropagateBlockChain;
    actor->handleMessage = Ov239_HandleMessage;
    actor->createNodeRegistryEntry = Ov239_CreateNodeRegistryEntry;
    actor->advanceSubState = Ov239_MaybeForceSubState7ThenAdvance;
    actor->onHit = Ov239_OnHit;
    actor->applyActorConfig = Ov239_ApplyActorConfig310;
    actor->requestSubState8 = Ov239_RequestSubState8IfNotAlready;
    actor->requestSubState9 = Ov239_RequestSubState9IfIdle;

    actor->camera[3] = 0xf00;
    actor->camera[0] = 0;
    actor->camera[1] = 0xf00;
    actor->camera[2] = 0;
    actor->actorBounds = bounds;

    actor->primarySubitem =
        CreateSubitemInstance0xB4(Ov107_PackTextureHandle(actor, 0));
    RegisterSubscriberSlot(actor->subscriberOwner, actor->primarySubitem);

    actor->moveBinding =
        Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(actor, 1),
                            gOv239MoveName);

    actor->subitem39c =
        CreateSubitemInstance0xB4(Ov107_PackTextureHandle(actor, 2));
    subitem = *(Ov239Subitem *volatile *)&actor->subitem39c;
    Ov107_EnqueueValue(actor, subitem);
    subitem->flags |= 2;

    subitem = actor->subitem3a4 =
        CreateSubitemInstance0xB4(Ov107_PackTextureHandle(actor, 3));
    Ov107_EnqueueValue(actor, subitem);
    subitem->flags |= 2;

    subitem = actor->subitem3ac =
        CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(actor->cachedResourceId, 1)));
    Ov107_EnqueueValue(actor, subitem);
    subitem->flags |= 2;

    actor->subitem3b4 =
        CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(actor->cachedResourceId, 0)));
    subitem = actor->subitem3b4;
    Ov107_EnqueueValue(actor, subitem);
    subitem->flags |= 2;

    actor->primaryDescriptorSlot =
        List_InsertSorted(actor->subitemSlotPool, 0x10, 100);
    *actor->primaryDescriptorSlot =
        Ov107_CloneResourceTransform((const Ov239ResourceTransform *)actor->camera);

    descriptorSlot = List_InsertSorted(actor->descriptorSlotPool, 4, 100);
    descriptor = (*descriptorSlot =
        Ov107_CloneResourceTransform((const Ov239ResourceTransform *)actor->camera));
    actor->resourceDescriptor = descriptor;
    Res_RequestIdPair(0x138);
}
