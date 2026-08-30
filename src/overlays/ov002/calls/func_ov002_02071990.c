/* Ov002_LoadWorldLinkResources: load and relocate the world's peer tables.
 * Publish the allocation through both context fields before capturing pTable.
 * Keeping that ownership sequence and an explicit object cursor reproduces
 * the original THUMB register lifetimes without a spilled context pointer.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
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
extern char data_ov002_0207f0f4[];
extern const char *data_ov002_0207f0a4[];
extern void func_0202b80c(int nContext);
extern int OS_SPrintf(char *,const char *,...);
extern void func_02024fd4(void *);
extern void *func_02024ee8(const char *,int);
extern void func_ov002_0206da54(int,void *);
extern void NNSi_FndFreeFromDefaultHeap(void *);
extern Ov002RosterTable *func_0201ef9c(u32,int);
extern void MI_CpuFill8(void *,int,u32);
extern void func_ov002_02071190(u32);
extern void INITi_CpuClear32_0x01ff86fc(int,void *,u32);

void func_ov002_02071990(int nWorld,int nResourceContext)
{
    char szPath[32];
    int i,j;
    Ov002PeerRecord *pObjectWalk;
    Ov002RosterTable *pTable;
    Ov002PeerRecord *pPeer;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    func_0202b80c(nResourceContext);
    OS_SPrintf(szPath,data_ov002_0207f0f4,data_ov002_0207f0a4[nWorld]);
    if(pCtx->pArchiveIndex) func_02024fd4(pCtx->pArchiveIndex);
    pCtx->pArchiveIndex=func_02024ee8(szPath,2);
    func_ov002_0206da54(2,pCtx->pArchiveIndex);
    if(pCtx->pOwnedTable) {
        NNSi_FndFreeFromDefaultHeap(pCtx->pOwnedTable);
        pCtx->pOwnedTable=0;
    }
    pCtx->pOwnedTable=func_0201ef9c(((((u32)pCtx->pArchiveIndex+0x8000)&0xfffffc)<<7)|0x80000000,2);
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
    func_ov002_02071190(((((u32)pCtx->pArchiveIndex+0x8000)&0xfffffc)<<7)|0x80000001);
    INITi_CpuClear32_0x01ff86fc(0,pCtx->apPrimaryHooks,16);
    INITi_CpuClear32_0x01ff86fc(0,pCtx->apSecondaryHooks,16);
    MI_CpuFill8(pCtx->aHookState,0,128);
    pCtx->bFlags &= ~2;
}
