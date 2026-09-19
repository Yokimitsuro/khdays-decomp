typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

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

extern int func_ov107_020c9c24(const void *name);
extern void *func_ov107_020c9440(Ov239Actor *actor, int kind);
extern Ov239Subitem *func_0203b898(void *packedHandle);
extern int func_0203bfb4(void *owner, Ov239Subitem *subitem);
extern void *func_ov107_020c9e50(void *packedHandle, const void *name);
extern void func_ov107_020c9074(Ov239Actor *actor, Ov239Subitem *subitem);
extern void **func_01fffca8(void *pool, int stride, int priority);
extern void *func_ov107_020c319c(const Ov239ResourceTransform *transform);
extern void func_0203355c(int resourceId);

extern void func_ov239_020cc234(void);
extern void func_ov239_020cc27c(void);
extern void func_ov239_020cc2f0(void);
extern void func_ov239_020cc490(void);
extern void func_ov239_020cc424(void);
extern void func_ov239_020cc4ec(void);
extern void func_ov239_020cc458(void);
extern void func_ov239_020cc71c(void);
extern void func_ov239_020cc748(void);
extern const char data_ov239_020cdc4c[];
extern const char data_ov239_020cdc5c[];

#pragma opt_dead_assignments off
void func_ov239_020cbfc4(Ov239Actor *actor)
{
    int minX;
    int minY;
    int minZ;
    Ov239ActorBounds bounds;
    Ov239Subitem *subitem;
    void **descriptorSlot;
    void *descriptor;

    actor->cachedResourceId = func_ov107_020c9c24(data_ov239_020cdc4c);
    minX = -0xeea;
    minY = 0x17;
    minZ = -0x858;
    bounds.minX = minX;
    bounds.minY = minY;
    bounds.minZ = minZ;
    bounds.maxX = bounds.minX + 0x1dd3;
    bounds.maxY = bounds.minY + 0x1c27;
    bounds.maxZ = bounds.minZ + 0xd64;
    actor->release = func_ov239_020cc234;
    actor->propagateBlockChain = func_ov239_020cc27c;
    actor->handleMessage = func_ov239_020cc2f0;
    actor->createNodeRegistryEntry = func_ov239_020cc490;
    actor->advanceSubState = func_ov239_020cc424;
    actor->onHit = func_ov239_020cc4ec;
    actor->applyActorConfig = func_ov239_020cc458;
    actor->requestSubState8 = func_ov239_020cc71c;
    actor->requestSubState9 = func_ov239_020cc748;

    actor->camera[3] = 0xf00;
    actor->camera[0] = 0;
    actor->camera[1] = 0xf00;
    actor->camera[2] = 0;
    actor->actorBounds = bounds;

    actor->primarySubitem =
        func_0203b898(func_ov107_020c9440(actor, 0));
    func_0203bfb4(actor->subscriberOwner, actor->primarySubitem);

    actor->moveBinding =
        func_ov107_020c9e50(func_ov107_020c9440(actor, 1),
                            data_ov239_020cdc5c);

    actor->subitem39c =
        func_0203b898(func_ov107_020c9440(actor, 2));
    subitem = *(Ov239Subitem *volatile *)&actor->subitem39c;
    func_ov107_020c9074(actor, subitem);
    subitem->flags |= 2;

    subitem = actor->subitem3a4 =
        func_0203b898(func_ov107_020c9440(actor, 3));
    func_ov107_020c9074(actor, subitem);
    subitem->flags |= 2;

    subitem = actor->subitem3ac =
        func_0203b898((void *)((((actor->cachedResourceId + 0x8000) & 0xfffffc) << 7)
                      | 0x80000001));
    func_ov107_020c9074(actor, subitem);
    subitem->flags |= 2;

    actor->subitem3b4 =
        func_0203b898((void *)((((actor->cachedResourceId + 0x8000) & 0xfffffc) << 7)
                      | 0x80000000));
    subitem = actor->subitem3b4;
    func_ov107_020c9074(actor, subitem);
    subitem->flags |= 2;

    actor->primaryDescriptorSlot =
        func_01fffca8(actor->subitemSlotPool, 0x10, 100);
    *actor->primaryDescriptorSlot =
        func_ov107_020c319c((const Ov239ResourceTransform *)actor->camera);

    descriptorSlot = func_01fffca8(actor->descriptorSlotPool, 4, 100);
    descriptor = (*descriptorSlot =
        func_ov107_020c319c((const Ov239ResourceTransform *)actor->camera));
    actor->resourceDescriptor = descriptor;
    func_0203355c(0x138);
}
