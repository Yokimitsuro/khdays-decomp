/*
 * Ov128_ChaserInit -- class initialiser for the ov128 chaser.
 *
 * Same function as ov130's initialiser; only the tuning constants differ:
 * speed pair 0x900 (ov130: 0x1400), channel range 0x2000 (0x4000),
 * spawn radius 0x1800 (0x3000), spawn height 0x900 (0x1400),
 * resource id 0x118 (0x15c).
 *
 * Installs the seven handlers the framework calls into, sets the two speed
 * pairs, builds the sub-objects (the model instance kept at +0x384, the effect
 * at +0x390 and the boxed instance at +0x394), opens three subscriber channels,
 * takes a sorted slot for the id list and finally requests the spawn volume:
 * a zero position, an up axis, a 0x3000 radius and a 0x1400 height. The request
 * returns a 64-bit id pair -- the low half is stored, the high half is handed
 * straight to the resource request.
 *
 * The object is addressed as an array of words; the indices below are the byte
 * offsets divided by four:
 *
 *   [2]=+0x08 [3]=+0x0c [7]=+0x1c [0xc]=+0x30 [0xe]=+0x38   handler slots
 *   [0x74]=+0x1d0 [0x77]=+0x1dc                             handler slots
 *   [0x19]=+0x64 .. [0x1c]=+0x70                            speed pairs
 *   [0x27]=+0x9c   owner list      [0x51]=+0x144  id list
 *   [0x8b]=+0x22c  sorted slots    [0xe1]=+0x384  model instance
 *   [0xe2]=+0x388  list slot       [0xe3]=+0x38c  spawn id
 *   [0xe4]=+0x390  effect          [0xe5]=+0x394  boxed instance
 *   [0xe6]=+0x398  child list
 *
 * aOwnerTag is a zeroed word whose low nine bits are or'ed into the subitem id
 * together with the tag derived from the current thread's stack bottom.
 */

#include "game/archive.h"

typedef struct { int nX, nY, nZ; } VecFx32;

struct SpawnVolume {
    VecFx32 vPos;
    VecFx32 vUp;
    int nRadius;
    int nHeight;
};

extern void Ov128_ReleaseSubObjectsAndListThenNotify(void);
extern void Ov128_PropagateBlockChain(void);
extern void Ov128_SpawnSlotEffectOnce(void);
extern void Ov128_registryCreateEntry(void);
extern void Ov128_RebuildIdList(void);
extern void Ov128_HandleHit(void);
extern void Ov128_Model_SetTrack0(void);

extern int Ov107_PackTextureHandle(int *self, int nKind);
extern int CreateSubitemInstance0xB4(unsigned int uId);
extern void RegisterSubscriberSlot(int a, int b);
extern int Ov107_CreateNamedResourceBinding(int a, const void *b);
extern void List_Init(void *pList);
extern int CallocInstance(int nSize);
extern int Ov107_GetActorManager(void);
extern void Ov107_EnqueueValue(int *self, int a);
extern void Ov107_Actor_SetAttachSlot(int *self, int nChannel, int b, int c, int nRange);
extern int List_InsertSorted(void *a, int b, int c);
extern int Ov107_CloneResourceTransform(void *a);
extern long long Ov107_Mover_New(VecFx32 *pReq);
extern void Res_RequestIdPair(int nId);

extern const char gOv128MoveName[];
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;

void Ov128_ChaserInit(int *self)
{
    struct SpawnVolume req;
    int aOwnerTag[1] = { 0 };
    int nInst;
    int nThread;
    int *pSlot;
    long long idPair;

    ((void **)self)[2] = (void *)Ov128_ReleaseSubObjectsAndListThenNotify;
    ((void **)self)[3] = (void *)Ov128_PropagateBlockChain;
    ((void **)self)[7] = (void *)Ov128_SpawnSlotEffectOnce;
    ((void **)self)[0xc] = (void *)Ov128_registryCreateEntry;
    ((void **)self)[0xe] = (void *)Ov128_RebuildIdList;
    ((void **)self)[0x74] = (void *)Ov128_HandleHit;
    ((void **)self)[0x77] = (void *)Ov128_Model_SetTrack0;

    self[0x1c] = 0x900;
    self[0x19] = 0;
    self[0x1a] = 0x900;
    self[0x1b] = 0;

    nInst = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(self, 0));
    self[0xe1] = nInst;
    RegisterSubscriberSlot(self[0x27], self[0xe1]);

    self[0xe4] = Ov107_CreateNamedResourceBinding(Ov107_PackTextureHandle(self, 1), gOv128MoveName);
    List_Init((void *)&self[0xe6]);
    self[0xe5] = CallocInstance(8);

    nThread = Ov107_GetActorManager();
    *(int *)self[0xe5] =
        CreateSubitemInstance0xB4((aOwnerTag[0] & 0x1ff) |
                      (ARCHIVE_HANDLE(*(int *)(nThread + 0x88), 0)));
    Ov107_EnqueueValue(self, *(int *)self[0xe5]);
    *(unsigned int *)(*(int *)self[0xe5] + 0x5c) |= 2;

    Ov107_Actor_SetAttachSlot(self, 0, 1, 0, 0x2000);
    Ov107_Actor_SetAttachSlot(self, 2, 1, 0, 0x2000);
    Ov107_Actor_SetAttachSlot(self, 1, 1, 0, 0x2000);

    self[0xe2] = List_InsertSorted((void *)&self[0x8b], 0x10, 100);
    *(int *)self[0xe2] = Ov107_CloneResourceTransform((void *)&self[0x19]);

    req.nRadius = 0x1800;
    req.vPos = data_02041dc8;
    req.vUp = data_02042264;
    req.nHeight = 0x900;
    pSlot = (int *)List_InsertSorted((void *)&self[0x51], 4, 100);
    idPair = Ov107_Mover_New(&req.vPos);
    *pSlot = (int)idPair;
    self[0xe3] = (int)idPair;
    Res_RequestIdPair(0x118);
}
