/* Ov002_ConfigureGateFromPeerRow: models, collision binding and gate effect.
 * Keep the u16 selector as &= then >>= to preserve derived-counter scheduling.
 * The five-slot codegen view has a placement in slot0 and four model slots.
 * Preserve the effect pointer across the tint/flag writes to avoid a reload. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct Ov002PeerRow {
    u8 nKey,nTargetSlot,pad02;
    s8 nGateState;
    u16 wFlags;
    short nRadius;
} Ov002PeerRow;
typedef struct Ov002ModelDesc {
    s8 nKind; u8 bEnabled; u16 hTint;
    int nParams; char pad008[8]; VecFx32 place;
} Ov002ModelDesc;
typedef struct Ov002GateModelEntry {
    s8 nKey; char pad001[3]; Ov002ModelDesc aModels[5];
} Ov002GateModelEntry;
typedef struct Ov002GatePlacement {
    s8 nKind; u8 bEnabled; u16 hTint;
    VecFx32 vPosition,vScale;
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
    VecFx32 vPosition,vScale; char pad0bc[0x24];
    short aTracks[5]; char pad0ea[0x1e];
} Ov002GateEffect;
typedef struct Ov002LinkCtx {
    char pad000[0x58]; Ov002GateEffect *apOwnedBlocks[8]; s8 nOwnedBlockCount;
} Ov002LinkCtx;
extern Ov002LinkCtx *data_ov002_0207fa10;
extern char gOv002StrIntFmt[],gOv002ColWallName[],gOv002GateName[],gOv00210Name[];
extern u8 data_0204c240;
extern Ov002GateModelEntry *Ov002_FindEntryAddrByKey(int nKey);
extern void Ov002_BuildModelSlot(Ov002ModelDesc *,int,int);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern unsigned int strlen(const char *);
extern void Ov002_RebindGroupAnimations(char *,unsigned int,int,int);
extern Ov002NamedEntry *SymbolGroup_FindName(int, char *);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int);
extern void *Ov002_LookupChannelEntry(const char *);
extern void BindAnimTrack(Ov002GateEffect *,u16,short *,int);

void Ov002_ConfigureGateFromPeerRow(Ov002PeerRow *pRow,int nWorld)
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
    pEntry=Ov002_FindEntryAddrByKey(pRow->nKey);
    bEnabled=(pRow->wFlags & 3)!=0;
    bEffect=(pRow->wFlags & 2)!=0;
    if(pEntry) {
        if(pRow->wFlags & 8) Ov002_BuildModelSlot(&pEntry->aModels[1],nWorld,0);
        if(pRow->wFlags & 0x10) Ov002_BuildModelSlot(&pEntry->aModels[2],nWorld,0);
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
                Ov002_BuildModelSlot(&pEntry->aModels[i+3],nWorld,nFlag);
            }
        }
    }
    {
        int bDisable=1;
        OS_SPrintf(szWall,gOv002StrIntFmt,gOv002ColWallName,pRow->nKey);
        if(bEnabled) bDisable=0;
        Ov002_RebindGroupAnimations(szWall,strlen(szWall),bDisable,nWorld);
    }
    if(data_0204c240 & 4) bEnabled=(pRow->wFlags & 1)!=0;
    OS_SPrintf(szGate,gOv002StrIntFmt,gOv002GateName,pRow->nKey);
    if(!bEnabled) {
        pNamed=SymbolGroup_FindName((u16)nWorld, szGate);
        if(pNamed) pNamed->bEnabled=0;
    } else {
        pNamed=SymbolGroup_FindName((u16)nWorld, szGate);
        if(pNamed) {
            Ov002GateBinding *pBinding;
            pNamed->bEnabled=1;
            pBinding=pNamed->pGateBinding;
            if(!pBinding || pBinding->nTargetSlot!=pRow->nTargetSlot || pBinding->nKey!=pRow->nKey) {
                binding.nTargetSlot=pRow->nTargetSlot;
                binding.nKey=pRow->nKey;
                binding.nGateState=pRow->nGateState;
                binding.bEffect=bEffect?1:0;
                EntityMgr_AttachTrackData((u16)nWorld, szGate, &binding, 4);
            }
        }
    }
    if((data_0204c240 & 4) && bEffect) {
        Ov002GateEffect *pEffect;
        Ov002GatePlacement *pPlacement=(Ov002GatePlacement *)&pEntry->aModels[0];
        int nSlot=pCtx->nOwnedBlockCount;
        pCtx->apOwnedBlocks[nSlot]=NNSi_FndAllocFromDefaultExpHeap(0x108);
        RegisterSeqAndInit(pCtx->apOwnedBlocks[nSlot],Ov002_LookupChannelEntry(gOv00210Name),1,0);
        pCtx->nOwnedBlockCount++;
        pCtx->apOwnedBlocks[nSlot]->vPosition=pPlacement->vPosition;
        pEffect=pCtx->apOwnedBlocks[nSlot];
        pEffect->hTint=pPlacement->hTint;
        pEffect->wFlags |= 0x20;
        pCtx->apOwnedBlocks[nSlot]->vScale=pPlacement->vScale;
        for(i=0;i<5;i++) {
            if(pCtx->apOwnedBlocks[nSlot]->aTracks[(u16)i]>0)
                BindAnimTrack(pCtx->apOwnedBlocks[nSlot],(u16)i,pCtx->apOwnedBlocks[nSlot]->aTracks,0);
        }
    }
}
