/* Constructor of the ov144 enemy (and its byte-identical twin): installs the handlers (+8 tick,
 * +0xc draw, +0x30/+0x38 hit callbacks, +0x1c message, +0x20/+0x24 callbacks, +0x1dc finish,
 * +0x1e0 callback), sets +0x1c9 to 2, seeds the +0x1fc bounding box, the +0x64 pose (scale
 * 0x1000, y 0x1000), bit 3 of +0x1ae and bit 5 of the +0x60 high byte; builds the primary item
 * from pool entry 0 (subscribed, back-linked into its render object's +0x4c, its named joint
 * resolved into +0x3a0 and the node matrix callback armed with mode 6/3), runs the finish
 * handler once, keeps the named motion handle (+0x394), creates the kind-7 sub-item (+0x388,
 * attached, bits 0/1, channel 2 bound), an effect node (+0x398, subscribed, bit 0) hosting the
 * pool entry 2 item (+0x38c, bit 1), the kind-0 sub-item (+0x3f8, attached, bit 1), a placement
 * on the +0x144 list (+0x390) and loads sound 0x123.
 *
 * MATCH NOTE: the bounding box is assigned field by field before the handlers (max = min +
 * size keeps the ROM's add chains; folded constants become pool loads) and copied as a whole
 * after the sub-state byte; the sub-item/list tail goes through the typed actor view, which
 * keeps the `orr r1` flag store ahead of the list call's argument setup. */

#include "nitro/types.h"
#include "game/archive.h"

struct Bit0 {
    unsigned bit0 : 1;
};

struct Subitem {
    char pad000[0x5c];
    unsigned int flags5c;
};

struct Ov144Actor {
    char pad000[0x64];
    int camera[4];
    char pad074[0x144 - 0x74];
    char pool144[0x390 - 0x144];
    int poolValue390;
    char pad394[0x3f8 - 0x394];
    struct Subitem *subitem3f8;
};

struct Box {
    int xmin, ymin, zmin;
    int xmax, ymax, zmax;
};

extern void Ov144_ReleaseActorSubObjects(void);
extern void Ov144_SetupAndPropagateBlock(void);
extern void Ov144_CreateRegistryEntryAndLink(void);
extern void Ov144_Configure(void);
extern void Ov144_HandleMessage(void);
extern void Ov144_SendBlankStatus(void);
extern void Ov144_StampActorBytesToMsgAndForward(void);
extern void Ov144_Model_SetTracks0And3(void);
extern void Ov144_RequestSubState9IfNotCurrent(void);
extern void Ov144_NodeMatrixCallback(void);
extern void *Ov107_PackTextureHandle(int pool, int index);
extern int CreateSubitemInstance0xB4(void *item);
extern int RegisterSubscriberSlot(int subscriber, int item);
extern int FindResourceIndexByName(int item, const char *name);
extern void NNS_G3dRenderObjSetCallBack(int renderObj, void *cb, int ptr, int timing, int opt);
extern int Ov107_CreateNamedResourceBinding(void *item, const char *name);
extern int *Ov107_GetActorManager(void);
extern void Ov107_EnqueueValue(int self, int item);
extern void SetSubitemState(int item, int channel, int a, int b);
extern int ModelNode_New(void);
extern int *List_InsertSorted(void *list, int stride, int max);
extern int Ov107_CloneResourceTransform(char *pose);
extern void Res_RequestIdPair(int id);
extern const char gOv144BoneHeadName[];
extern const char gOv144MoveName[];

void Ov144_Construct(char *self)
{
    struct Box box;
    int *p;
    struct Subitem *item;
    struct Ov144Actor *actor = (struct Ov144Actor *)self;
    int pose;

    box.xmin = -0x122d;
    box.ymin = -0xb;
    box.zmin = -0x742;
    box.xmax = box.xmin + 0x23ec;
    box.ymax = box.ymin + 0x1b60;
    box.zmax = box.zmin + 0x2014;
    *(void **)(self + 0x8) = Ov144_ReleaseActorSubObjects;
    *(void **)(self + 0xc) = Ov144_SetupAndPropagateBlock;
    *(void **)(self + 0x30) = Ov144_CreateRegistryEntryAndLink;
    *(void **)(self + 0x38) = Ov144_Configure;
    *(void **)(self + 0x1c) = Ov144_HandleMessage;
    *(void **)(self + 0x20) = Ov144_SendBlankStatus;
    *(void **)(self + 0x24) = Ov144_StampActorBytesToMsgAndForward;
    *(void **)(self + 0x1dc) = Ov144_Model_SetTracks0And3;
    *(void **)(self + 0x1e0) = Ov144_RequestSubState9IfNotCurrent;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(struct Box *)(self + 0x1fc) = box;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x384) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle((int)self, 0));
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(char **)(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x4c) = self;
    *(u16 *)(self + 0x3a0) = FindResourceIndexByName(*(int *)(self + 0x384), gOv144BoneHeadName);
    NNS_G3dRenderObjSetCallBack(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x20, Ov144_NodeMatrixCallback, 0, 6, 3);
    (*(void (**)(char *, int, int))(self + 0x1dc))(self, 0, 1);
    *(int *)(self + 0x394) = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle((int)self, 1), gOv144MoveName);
    *(int *)(self + 0x388) = CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(Ov107_GetActorManager()[0x22], 7)));
    ((struct Bit0 *)(*(int *)(self + 0x388) + 0x5c))->bit0 = 1;
    Ov107_EnqueueValue((int)self, *(int *)(self + 0x388));
    *(int *)(*(int *)(self + 0x388) + 0x5c) |= 2;
    SetSubitemState(*(int *)(self + 0x388), 2, 0, 1);
    *(int *)(self + 0x398) = ModelNode_New();
    RegisterSubscriberSlot(*(int *)(self + 0x9c), *(int *)(self + 0x398));
    ((struct Bit0 *)(*(int *)(self + 0x398) + 0x5c))->bit0 = 1;
    *(int *)(self + 0x38c) = CreateSubitemInstance0xB4(Ov107_PackTextureHandle((int)self, 2));
    RegisterSubscriberSlot(*(int *)(self + 0x398), *(int *)(self + 0x38c));
    *(int *)(*(int *)(self + 0x38c) + 0x5c) |= 2;
    item = actor->subitem3f8 = (struct Subitem *)CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(Ov107_GetActorManager()[0x22], 0)));
    Ov107_EnqueueValue((int)self, (int)item);
    item->flags5c |= 2;
    p = List_InsertSorted(actor->pool144, 4, 0x64);
    pose = Ov107_CloneResourceTransform((char *)actor->camera);
    *p = pose;
    actor->poolValue390 = pose;
    Res_RequestIdPair(0x123);
}
