/* Ov002_LoadWorldLinkResources: load and relocate the world's peer tables.
 * Publish the allocation through both context fields before capturing pTable.
 * Keeping that ownership sequence and an explicit object cursor reproduces
 * the original THUMB register lifetimes without a spilled context pointer.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov002PeerRow Ov002PeerRow;
typedef struct Ov002PeerRecord {
    s8 bKind,nRows,nObjects; char pad003[0x19];
    Ov002PeerRow *pRows; void *apObjects[1];
} Ov002PeerRecord;
typedef struct Ov002RosterTable {
    u8 nCount; char pad001[3]; Ov002PeerRecord *entries[1];
} Ov002RosterTable;
typedef struct Ov002LinkCtx {
    void *pOwnedTable; Ov002RosterTable *pTable; void *pArchiveIndex;
    s8 nLinkMode,nCurrentSlot; u8 bFlags; char pad00f[8];
    s8 aSlotMappings[24],slots[4]; char pad033[0x2266];
    u8 bWorldReady; char pad229a[2]; u32 nNoticeBits;
    void *apPrimaryHooks[4],*apSecondaryHooks[4]; u8 aHookState[4][32];
} Ov002LinkCtx;
extern Ov002LinkCtx *data_ov002_0207fa10;
extern char gOv002MiWdWdPathFmt[];
extern const char *data_ov002_0207f0a4[];
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(const char *,int);
extern void Ov002_SetRootWord8a28(int,void *);
extern void NNSi_FndFreeFromDefaultHeap(void *);
extern Ov002RosterTable *Archive_LoadFile(u32,int);
extern void MI_CpuFill8(void *,int,u32);
extern void Ov002_LoadGateModelTable(u32);
extern void INITi_CpuClear32_0x01ff86fc(int,void *,u32);

void Ov002_LoadWorldLinkResources(int nWorld,int nResourceContext)
{
    char szPath[32];
    int i,j;
    Ov002PeerRecord *pObjectWalk;
    Ov002RosterTable *pTable;
    Ov002PeerRecord *pPeer;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    StoreToGlobalDblPtr(nResourceContext);
    OS_SPrintf(szPath,gOv002MiWdWdPathFmt,data_ov002_0207f0a4[nWorld]);
    if(pCtx->pArchiveIndex) ZeroHalfThenFree(pCtx->pArchiveIndex);
    pCtx->pArchiveIndex=Msg_OpenContainerAndReadHeader(szPath,2);
    Ov002_SetRootWord8a28(2,pCtx->pArchiveIndex);
    if(pCtx->pOwnedTable) {
        NNSi_FndFreeFromDefaultHeap(pCtx->pOwnedTable);
        pCtx->pOwnedTable=0;
    }
    pCtx->pOwnedTable=Archive_LoadFile(((((u32)pCtx->pArchiveIndex+0x8000)&0xfffffc)<<7)|0x80000000,2);
    pCtx->pTable=pCtx->pOwnedTable;
    pTable=pCtx->pTable;
    for(i=0;i<pTable->nCount;i++) {
        pTable->entries[i]=(Ov002PeerRecord *)((char *)pTable+(u32)pTable->entries[i]);
    }
    for(i=0;i<pTable->nCount;i++) {
        pPeer=pTable->entries[i];
        pPeer->pRows=(Ov002PeerRow *)((u32)pPeer->pRows+(u32)pPeer);
        j=0;
        if(j<pPeer->nObjects) {
            pObjectWalk=pPeer;
            do {
                pObjectWalk->apObjects[0]=(char *)pPeer+(u32)pObjectWalk->apObjects[0];
                j++;
                pObjectWalk=(Ov002PeerRecord *)((char *)pObjectWalk+4);
            } while(j<pPeer->nObjects);
        }
    }
    MI_CpuFill8(pCtx->aSlotMappings,0xff,24);
    MI_CpuFill8(pCtx->slots,0xff,4);
    pCtx->bWorldReady=1;
    pCtx->nNoticeBits=0;
    pCtx->nLinkMode=nWorld;
    Ov002_LoadGateModelTable(((((u32)pCtx->pArchiveIndex+0x8000)&0xfffffc)<<7)|0x80000001);
    INITi_CpuClear32_0x01ff86fc(0,pCtx->apPrimaryHooks,16);
    INITi_CpuClear32_0x01ff86fc(0,pCtx->apSecondaryHooks,16);
    MI_CpuFill8(pCtx->aHookState,0,128);
    pCtx->bFlags &= ~2;
}
