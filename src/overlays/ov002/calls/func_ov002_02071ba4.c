/* Ov002_LoadPeerIntoSlot: publish a peer slot and preload collision resources.
 * The u16 API boundaries deliberately narrow each slot argument at the call.
 * Keep nOne outside the model loop: its lifetime puts the unit in r7 and
 * leaves the resource counter in its original stack slot. The declaration
 * order j, group, blob fixes the three spills at +18, +14, +10 respectively.
 * The unsigned-byte comparison against -1 is retained exactly as in the ROM.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Ov002PeerRecord { s8 bKind,nRows,nObjects,nArchiveMember; } Ov002PeerRecord;
typedef struct Ov002RosterTable { u8 nCount; char pad1[3]; Ov002PeerRecord *entries[1]; } Ov002RosterTable;
typedef struct Ov002LinkCtx {
    void *pOwnedTable; Ov002RosterTable *pTable; void *pArchiveIndex;
    char pad00c[11]; s8 aSlotMappings[24],slots[4]; char pad033[0x2266];
    u8 bResourceKinds; char pad229a[2]; u32 dwRequestedResources;
    void *apPrimaryHooks[4],*apSecondaryHooks[4];
} Ov002LinkCtx;
typedef struct Ov002MissionMember { char pad0[3]; u8 bMemberKind; char pad4[0x100]; } Ov002MissionMember;
typedef struct CollisionModelBlob { char pad0[0x70]; u32 dwResourceFlags; } CollisionModelBlob;
typedef struct TrackEntryGroup { u16 wPad,wCount; CollisionModelBlob **apEntry; } TrackEntryGroup;
typedef struct Ov002SurfaceTagTemplate { const char *pName; s8 nTag; char pad5[3]; } Ov002SurfaceTagTemplate;
extern Ov002LinkCtx *data_ov002_0207fa10;
extern u8 data_02042a1d;
extern Ov002MissionMember data_0204c678[];
extern u8 data_ov002_0207e610[];
extern Ov002SurfaceTagTemplate data_ov002_0207e640[];
extern char data_ov002_0207f0dc[];
extern int func_0202b820(u16,u32);
extern int func_ov002_0207298c(void);
extern void func_0203355c(int);
extern TrackEntryGroup *func_0202bfa0(u16);
extern void func_02025640(void *,int);
extern int func_02025694(void *,int);
extern int func_ov002_02076984(int,int);
extern void func_0202c0dc(u16,const char *,u8 *);
extern void func_ov002_02071804(int,void **,void **);
extern void func_ov002_02072aa0(const char *,int,int,int);

void func_ov002_02071ba4(int nSlot,int nPeer)
{
    int i;
    int j,nOne;
    TrackEntryGroup *pGroup;
    CollisionModelBlob *pBlob;
    int k,nResource;
    u32 nTag;
    Ov002PeerRecord *pPeer;
    Ov002SurfaceTagTemplate *pTemplate;
    u8 *pIds;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    pPeer=pCtx->pTable->entries[nPeer];
    if(pCtx->slots[nSlot]>=0) pCtx->aSlotMappings[pCtx->slots[nSlot]]=-1;
    pCtx->aSlotMappings[nPeer]=nSlot;
    pCtx->slots[nSlot]=nPeer;
    func_0202b820((u16)nSlot,(((((u32)pCtx->pArchiveIndex+0x8000)&0xfffffc)<<7)|0x80000000)|(pPeer->nArchiveMember&0x1ff));
    for(i=0;i<data_02042a1d;i++) {
        int nKind=data_0204c678[i].bMemberKind;
        if(nKind==0x11) pCtx->bResourceKinds|=4;
        else if(nKind!=0 && nKind!=5 && nKind!=0x13) pCtx->bResourceKinds|=2;
    }
    if(func_ov002_0207298c()==7 || func_ov002_0207298c()==4) {
        if(pCtx->bResourceKinds&1) func_0203355c(12);
        if(pCtx->bResourceKinds&2) func_0203355c(25);
        if(pCtx->bResourceKinds&4) func_0203355c(38);
    }
    pGroup=func_0202bfa0((u16)nSlot);
    nOne=1;
    for(i=0;i<pGroup->wCount;i++) {
        pBlob=pGroup->apEntry[i];
        pIds=data_ov002_0207e610;
        j=0;
        do {
            if(pBlob->dwResourceFlags&(1<<j)) {
                for(k=0;k<3;k++) {
                    if((pCtx->bResourceKinds&(nOne<<k)) && *pIds!=-1) func_0203355c(pIds[k]);
                }
                func_02025640(&pCtx->dwRequestedResources,j);
            }
            pIds+=3;
        } while(++j<=14);
    }
    pIds=data_ov002_0207e610;
    for(nResource=0;nResource<=14;nResource++,pIds+=3) {
        if(!func_02025694(&pCtx->dwRequestedResources,nResource) && func_ov002_02076984(nPeer,nResource)) {
            for(k=0;k<3;k++) {
                if((pCtx->bResourceKinds&(1<<k)) && *pIds!=-1) func_0203355c(pIds[k]);
            }
            func_02025640(&pCtx->dwRequestedResources,nResource);
        }
    }
    pTemplate=data_ov002_0207e640;
    for(nTag=0;nTag<7;nTag++,pTemplate++) {
        u8 aTags[4]={0,0,0,0};
        aTags[0]=pTemplate->nTag;
        func_0202c0dc((u16)nSlot,pTemplate->pName,aTags);
    }
    func_ov002_02071804(nPeer,&pCtx->apPrimaryHooks[nSlot],&pCtx->apSecondaryHooks[nSlot]);
    func_ov002_02072aa0(data_ov002_0207f0dc,8,0,nSlot);
}
