/* Ov002_StepPeerObjectLoading: poll an asynchronous peer resource, publish its
 * render entry, then configure the peer's gate rows. The explicit descriptor
 * array cursor preserves the original reload across the request call. The
 * chained zero assignment stores x, y, z in ascending stack order. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef struct VecFx32 { int x,y,z; } VecFx32;
typedef struct Slot_0201f468 { char pad0[12]; int nRequestId; } Slot_0201f468;
typedef struct Ov002PeerObjectDesc { u8 bFlags,nArchiveMember; } Ov002PeerObjectDesc;
typedef struct Ov002PendingPeerObject { Slot_0201f468 *pResource; Ov002PeerObjectDesc *pDescriptor; } Ov002PendingPeerObject;
typedef struct Ov002PeerRow { char bytes[8]; } Ov002PeerRow;
typedef struct Ov002PeerRecord {
    s8 bKind,nRows,nObjects,nArchiveMember; char pad4[24];
    Ov002PeerRow *pRows; Ov002PeerObjectDesc *apObjects[1];
} Ov002PeerRecord;
typedef struct Ov002RosterTable { u8 nCount; char pad1[3]; Ov002PeerRecord *entries[1]; } Ov002RosterTable;
typedef struct Ov002LinkEntry {
    char pad0[0xa4]; VecFx32 position; char padb0[0x30];
    s16 aTrackCounts[5]; char padea[0x1e]; u8 bActive,nVariant; char pad10a[2];
} Ov002LinkEntry;
typedef struct Ov002LinkCtx {
    void *pOwnedTable; Ov002RosterTable *pTable; void *pArchiveIndex;
    s8 nLinkMode,nCurrentSlot; char pade[0x21]; s8 slots[4];
    char pad33[0xd1]; u8 nLoadState; s8 nNextObject; char pad106[2];
    Ov002PendingPeerObject pendingObject; s8 nEntryCount,nSeatSplit; char pad112[2];
    Ov002LinkEntry aEntries[32];
} Ov002LinkCtx;
extern Ov002LinkCtx *data_ov002_0207fa10;
extern int func_0201eea8(int);
extern int func_0202a66c(Ov002LinkEntry *,Slot_0201f468 *,int,int);
extern void func_0202ad74(Ov002LinkEntry *,u16,s16 *,s16,int);
extern int func_0201f468(u32,Slot_0201f468 **,int);
extern void func_ov002_020715c4(Ov002PeerRow *,int);

int func_ov002_02071e08(void)
{
    int i;
    int nSlot;
    Ov002PendingPeerObject *pPending;
    Ov002LinkEntry *pEntry;
    Ov002PeerObjectDesc **pObjects;
    int nAnimation;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    VecFx32 zero;
    Ov002PeerRecord *pPeer;
    nSlot=pCtx->nCurrentSlot;
    zero.z=zero.y=zero.x=0;
    pPeer=pCtx->pTable->entries[pCtx->slots[nSlot]];
    if(pCtx->nLoadState==2) {
        pPending=&pCtx->pendingObject;
        if(pPending->pResource && func_0201eea8(pPending->pResource->nRequestId)) {
            nAnimation=(pPending->pDescriptor->bFlags&0x70)>>4;
            pEntry=&pCtx->aEntries[pCtx->nEntryCount];
            func_0202a66c(pEntry,pPending->pResource,1,0);
            pEntry->nVariant=pPending->pDescriptor->bFlags&0xf;
            pEntry->position=zero;
            for(i=0;i<5;i++) {
                if(pEntry->aTrackCounts[(u16)i]>0) func_0202ad74(pEntry,(u16)i,pEntry->aTrackCounts,(s16)nAnimation,0);
            }
            pEntry->bActive|=1;
            pCtx->nEntryCount++;
            pPending->pResource=0;
            pPending->pDescriptor=0;
            pCtx->nLoadState=0;
        }
    }
    if(pCtx->nLoadState==0) {
        for(i=pCtx->nNextObject;i<pPeer->nObjects;i=pCtx->nNextObject) {
            pCtx->nNextObject++;
            if(pPeer->apObjects[i]->bFlags&0x80) {
                pObjects=pPeer->apObjects;
                func_0201f468((((((u32)pCtx->pArchiveIndex+0x8000)&0xfffffc)<<7)|0x80000000)|(pObjects[i]->nArchiveMember&0x1ff),&pCtx->pendingObject.pResource,0);
                pCtx->pendingObject.pDescriptor=pObjects[i];
                pCtx->nLoadState=2;
                break;
            }
        }
        if(pCtx->nLoadState==0) pCtx->nLoadState=3;
    }
    if(pCtx->nLoadState==3) {
        if(pPeer->nRows>0) pCtx->nLoadState=1;
        else pCtx->nLoadState=4;
        if(pCtx->nSeatSplit==0) pCtx->nSeatSplit=pCtx->nEntryCount;
    }
    if(pCtx->nLoadState==1) {
        for(i=0;i<pPeer->nRows;i++) func_ov002_020715c4(&pPeer->pRows[i],nSlot);
        pCtx->nLoadState=4;
    }
    if(pCtx->nLoadState==4) return 1;
    return 0;
}
