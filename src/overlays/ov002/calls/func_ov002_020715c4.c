/* Ov002_ConfigureGateFromPeerRow: models, collision binding and gate effect.
 * Keep the u16 selector as &= then >>= to preserve derived-counter scheduling.
 * The five-slot codegen view has a placement in slot0 and four model slots.
 * Preserve the effect pointer across the tint/flag writes to avoid a reload. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef struct Ov002Vec3 { int x,y,z; } Ov002Vec3;
typedef struct Ov002PeerRow {
    u8 nKey,nTargetSlot,pad02;
    s8 nGateState;
    u16 wFlags;
    short nRadius;
} Ov002PeerRow;
typedef struct Ov002ModelDesc {
    s8 nKind; u8 bEnabled; u16 hTint;
    int nParams; char pad008[8]; Ov002Vec3 place;
} Ov002ModelDesc;
typedef struct Ov002GateModelEntry {
    s8 nKey; char pad001[3]; Ov002ModelDesc aModels[5];
} Ov002GateModelEntry;
typedef struct Ov002GatePlacement {
    s8 nKind; u8 bEnabled; u16 hTint;
    Ov002Vec3 vPosition,vScale;
} Ov002GatePlacement;
typedef struct Ov002GateBinding {
    u8 bEffect; s8 nTargetSlot,nKey,nGateState;
} Ov002GateBinding;
typedef struct Ov002NamedEntry {
    char aName[8],pad008[4]; u8 bEnabled; char pad00d[3];
    Ov002GateBinding *pGateBinding;
} Ov002NamedEntry;
typedef struct Ov002GateEffect {
    u16 wFlags; char pad002[0x7a]; u16 hTint; char pad07e[0x26];
    Ov002Vec3 vPosition,vScale; char pad0bc[0x24];
    short aTracks[5]; char pad0ea[0x1e];
} Ov002GateEffect;
typedef struct Ov002LinkCtx {
    char pad000[0x58]; Ov002GateEffect *apOwnedBlocks[8]; s8 nOwnedBlockCount;
} Ov002LinkCtx;
extern Ov002LinkCtx *data_ov002_0207fa10;
extern char data_ov002_0207f0d4[],data_ov002_0207f0dc[],data_ov002_0207f0e8[],data_ov002_0207f0f0[];
extern u8 data_0204c240;
extern Ov002GateModelEntry *func_ov002_020711d0(int nKey);
extern void func_ov002_0207145c(Ov002ModelDesc *,int,int);
extern int OS_SPrintf(char *,const char *,...);
extern unsigned int strlen(const char *);
extern void func_ov002_02072aa0(char *,unsigned int,int,int);
extern Ov002NamedEntry *func_0202bfe8(u16,char *);
extern void func_0202c13c(u16,char *,const void *,unsigned int);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int);
extern void *func_ov002_0206da70(const char *);
extern void func_0202a634(Ov002GateEffect *,void *,int,int);
extern void func_0202accc(Ov002GateEffect *,u16,short *,int);

void func_ov002_020715c4(Ov002PeerRow *pRow,int nWorld)
{
    char szWall[16];
    char szGate[8];
    Ov002GateBinding binding;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    Ov002GateModelEntry *pEntry;
    int bEffect;
    int bEnabled;
    int i;
    Ov002NamedEntry *pNamed;
    if(pRow->wFlags & 0x8000) return;
    pEntry=func_ov002_020711d0(pRow->nKey);
    bEnabled=(pRow->wFlags & 3)!=0;
    bEffect=(pRow->wFlags & 2)!=0;
    if(pEntry) {
        if(pRow->wFlags & 8) func_ov002_0207145c(&pEntry->aModels[1],nWorld,0);
        if(pRow->wFlags & 0x10) func_ov002_0207145c(&pEntry->aModels[2],nWorld,0);
        for(i=0;i<2;i++) {
            u16 nMode=pRow->wFlags;
            nMode &= (u16)(0x60 << (i*2));
            nMode >>= (i*2+5);
            if(nMode!=3) {
                int nFlag=bEnabled;
                switch(nMode) {
                case 0: break;
                case 1: nFlag=1; break;
                case 2: nFlag=0; break;
                }
                func_ov002_0207145c(&pEntry->aModels[i+3],nWorld,nFlag);
            }
        }
    }
    {
        int bDisable=1;
        OS_SPrintf(szWall,data_ov002_0207f0d4,data_ov002_0207f0dc,pRow->nKey);
        if(bEnabled) bDisable=0;
        func_ov002_02072aa0(szWall,strlen(szWall),bDisable,nWorld);
    }
    if(data_0204c240 & 4) bEnabled=(pRow->wFlags & 1)!=0;
    OS_SPrintf(szGate,data_ov002_0207f0d4,data_ov002_0207f0e8,pRow->nKey);
    if(!bEnabled) {
        pNamed=func_0202bfe8((u16)nWorld,szGate);
        if(pNamed) pNamed->bEnabled=0;
    } else {
        pNamed=func_0202bfe8((u16)nWorld,szGate);
        if(pNamed) {
            Ov002GateBinding *pBinding;
            pNamed->bEnabled=1;
            pBinding=pNamed->pGateBinding;
            if(!pBinding || pBinding->nTargetSlot!=pRow->nTargetSlot || pBinding->nKey!=pRow->nKey) {
                binding.nTargetSlot=pRow->nTargetSlot;
                binding.nKey=pRow->nKey;
                binding.nGateState=pRow->nGateState;
                binding.bEffect=bEffect?1:0;
                func_0202c13c((u16)nWorld,szGate,&binding,4);
            }
        }
    }
    if((data_0204c240 & 4) && bEffect) {
        Ov002GateEffect *pEffect;
        Ov002GatePlacement *pPlacement=(Ov002GatePlacement *)&pEntry->aModels[0];
        int nSlot=pCtx->nOwnedBlockCount;
        pCtx->apOwnedBlocks[nSlot]=NNSi_FndAllocFromDefaultExpHeap(0x108);
        func_0202a634(pCtx->apOwnedBlocks[nSlot],func_ov002_0206da70(data_ov002_0207f0f0),1,0);
        pCtx->nOwnedBlockCount++;
        pCtx->apOwnedBlocks[nSlot]->vPosition=pPlacement->vPosition;
        pEffect=pCtx->apOwnedBlocks[nSlot];
        pEffect->hTint=pPlacement->hTint;
        pEffect->wFlags |= 0x20;
        pCtx->apOwnedBlocks[nSlot]->vScale=pPlacement->vScale;
        for(i=0;i<5;i++) {
            if(pCtx->apOwnedBlocks[nSlot]->aTracks[(u16)i]>0)
                func_0202accc(pCtx->apOwnedBlocks[nSlot],(u16)i,pCtx->apOwnedBlocks[nSlot]->aTracks,0);
        }
    }
}
