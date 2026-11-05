/* Constructor of the ov255 partner object: installs its handlers (+8 update, +0xc draw, +0x1c
 * message, +0x30, +0x34, +0x1d0 hit filter), raises bits 1-4, 6 and 7 of the +0x60 high byte and
 * bits 2 and 4 of +0x1ae, sets the +0x70 scale to 0.125, builds the +0x388 binding of the rig's
 * pose 0x4a, creates the +0x3c4 effect (Ov255_CreateShakeTask), allocates the two-pair +0x3c0 table
 * (the first item from the gOv255MsXionSharePackPath_2 resource, the second from pose 0x4b; both hidden)
 * and reserves the +0x38c shape (a placement at the +0x64 pose, flag bit 1). */

#include "game/archive.h"
typedef void (*Callback)(void);
struct Word8 { unsigned int lo : 8; };

extern int Ov107_OpenCachedResourceByName(const char *name);
extern void *Ov107_PackTextureHandle(int obj, int index);
extern int JointModel_New(void *res, int size);
extern void Ov107_EnqueueValue(int self, int item);
extern int Ov255_CreateShakeTask(char *self);
extern int *CallocInstance(int size);
extern int CreateSubitemInstance0xB4(void *res);
extern int *List_InsertSorted(void *pool, int elementSize, int capacity);
extern int Ov107_CloneResourceTransform(const void *placement);
extern const char gOv255MsXionSharePackPath_2[];
extern void Ov255_Partner_Destroy(void);
extern void Ov255_TickSyncXform(void);
extern void Ov255_PartnerHandleMessage(void);
extern void func_ov255_020d1b6c(void);
extern void Ov255_CreateRegistryEntryAndLink(void);
extern void Ov255_ClearSubPhaseIfRequested(void);

void Ov255_PartnerCtor(char *self)
{
    int res = Ov107_OpenCachedResourceByName(gOv255MsXionSharePackPath_2);
    unsigned short hw;

    *(Callback *)(self + 0x8) = Ov255_Partner_Destroy;
    *(Callback *)(self + 0xc) = Ov255_TickSyncXform;
    *(Callback *)(self + 0x1c) = Ov255_PartnerHandleMessage;
    *(Callback *)(self + 0x34) = func_ov255_020d1b6c;
    *(Callback *)(self + 0x30) = Ov255_CreateRegistryEntryAndLink;
    *(Callback *)(self + 0x1d0) = Ov255_ClearSubPhaseIfRequested;
    hw = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xde) << 0x18) >> 0x10);
    *(unsigned short *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0x200;
    *(int *)(self + 0x388) = JointModel_New(Ov107_PackTextureHandle(*(int *)(self + 0x384), 0x4a), 0x20);
    Ov107_EnqueueValue(*(int *)(self + 0x384), *(int *)(self + 0x388));
    *(int *)(self + 0x3c4) = Ov255_CreateShakeTask(self);
    *(int **)(self + 0x3c0) = CallocInstance(0x10);
    (*(int **)(self + 0x3c0))[0] = CreateSubitemInstance0xB4((void *)(ARCHIVE_HANDLE(res, 1)));
    Ov107_EnqueueValue((int)self, (*(int **)(self + 0x3c0))[0]);
    *(int *)((*(int **)(self + 0x3c0))[0] + 0x5c) |= 2;
    (*(int **)(self + 0x3c0))[2] = CreateSubitemInstance0xB4(Ov107_PackTextureHandle(*(int *)(self + 0x384), 0x4b));
    Ov107_EnqueueValue((int)self, (*(int **)(self + 0x3c0))[2]);
    *(int *)((*(int **)(self + 0x3c0))[2] + 0x5c) |= 2;
    *(int **)(self + 0x38c) = List_InsertSorted(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x38c) = Ov107_CloneResourceTransform(self + 0x64);
    ((struct Word8 *)(*(int *)(self + 0x38c) + 8))->lo |= 2;
}
