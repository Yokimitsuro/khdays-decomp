/* Ov002_CreatePlacedPiece: claim, position and register a destructible piece. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct Ov002PlaceParams {int nKind,nParamB,nParamA,nParamC,nAngle;} Ov002PlaceParams;
typedef struct Ov002PiecePlacementBytes {s8 bPlaceKind,bSlotKind;} Ov002PiecePlacementBytes;
typedef union Ov002PiecePlacementParamB {short nParamB;Ov002PiecePlacementBytes fields;} Ov002PiecePlacementParamB;
typedef struct Ov002PieceClass {char pad0[0x68];short nRequestA;char pad6a[10];s8 bKind,bVariant;short nParamA;Ov002PiecePlacementParamB placeParamB;short nParamC;} Ov002PieceClass;
typedef void *Ov002StateFn(void *);
typedef struct Ov002PieceElement {
    char pad0[0xc];Ov002StateFn *pfnPhase;u8 bBucket,pad11;u16 wFlags,wRequestId;u8 bRequestSlot,bStateDirty;
    short nAngle;char pad1a[2];VecFx32 vPlace;int nNodeFlags;char aBodyNode[12];int nBuildFlags;u16 wAnimFlags;
    char pad3e[0x7a];short nHomeAngle;char padba[0xf6];int aClock[1];short nDropScale;u8 bDropsOn:1,nReplays:7;u8 nAnimCounter;
} Ov002PieceElement;
extern Ov002PieceElement *Ov002_ClaimPoolEntry(Ov002PieceClass *,int);
extern int Ov002_PlaceElementNode(void *,void *,Ov002PlaceParams *,int,int,int,int,int,int,int);
extern void Ov002_BuildSpawnPosition(VecFx32 *,VecFx32 *,Ov002PlaceParams *);
extern Ov002StateFn Ov002_OnPieceDefeated;
extern void Ov002_PushBucketNode(int,Ov002PieceElement *);
extern int Ov002_List_SetBit(int,int);
Ov002PieceElement *Ov002_CreatePlacedPiece(Ov002PieceClass *pClass,u16 nEntry,int nRoom,VecFx32 *pPosition,short nAngle,short nDropScale,u16 nRequestId,u8 nRequestSlot)
{
    Ov002PlaceParams placement;
    VecFx32 vPlaced;
    Ov002PieceElement *pPiece=Ov002_ClaimPoolEntry(pClass,nEntry);
    int nPlaceAngle=nAngle;
    Ov002_PlaceElementNode(pPiece,pPiece->aBodyNode,&placement,nEntry,pClass->bKind,pClass->nParamA,pClass->placeParamB.nParamB,pClass->nParamC,nPlaceAngle,1);
    Ov002_BuildSpawnPosition(&vPlaced,pPosition,&placement);
    Actor_SetVecAndSyncChild(&pPiece->nBuildFlags,pPosition);
    if(!(pPiece->nBuildFlags&0x20)){pPiece->nHomeAngle=nPlaceAngle;pPiece->wAnimFlags|=0x20;}
    pPiece->nAngle=nAngle;
    pPiece->vPlace=vPlaced;
    pPiece->nNodeFlags=0;
    pPiece->aClock[0]=0;
    pPiece->nDropScale=nDropScale;
    pPiece->bDropsOn=0;
    pPiece->nAnimCounter=0;
    pPiece->nReplays=0;
    pPiece->bBucket=nRoom;
    pPiece->pfnPhase=Ov002_OnPieceDefeated;
    pPiece->wFlags|=8;
    pPiece->wFlags|=0x40;
    pPiece->wRequestId=nRequestId;
    pPiece->bRequestSlot=nRequestSlot;
    pPiece->bStateDirty=0;
    Ov002_PushBucketNode(nRoom,pPiece);
    if(pClass->nRequestA==0x2b)Ov002_List_SetBit(nRoom,2);
    else Ov002_List_SetBit(nRoom,1);
    return pPiece;
}
