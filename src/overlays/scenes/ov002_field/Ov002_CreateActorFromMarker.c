/* Ov002_CreateActorFromMarker: spawn the enemy a marker row names, at its level (the mission's level
 * plus the row's adjustment, Ov002_GetMarkerEnemyLevel): the actor's +0x1ec hook loads that level's
 * stats (Ov107_AiState_LoadStats), its +0x1f0 hook the row's Ms up record (Ov107_LoadMsUpRecord). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorFlags40 {int pad:1;int bActive:1;} ActorFlags40;
typedef struct Actor Actor;
struct Actor {
    char pad0[0xc];void (*pfnHandler0c)(Actor *,int);char pad10[0x30];
    ActorFlags40 flags40;char pad44[0x15b];u8 nMarkerBoost;char pad1a0[14];u16 wFlags1ae;
    char pad1b0[0x3c];void (*pLoadStats)(Actor *,int nLevel);void (*pLoadMsUpRecord)(Actor *,int);
    char pad1f4[0x2c];int nMarkerValue;char pad224[0xd0];u32 nMarkerOverride;int nMarkerParam;
};
typedef struct Ov002MarkerRow {u8 bId,nKinds,nBoost,nProfile;s8 nLevelAdjustment,nParam;short nActorValue,nActorParam;char padA[6];} Ov002MarkerRow;
typedef struct Ov002RecordList {u8 nRowCount,nEntryCount;char pad2[2];Ov002MarkerRow *pRows;} Ov002RecordList;
typedef struct Ov002MarkerOverride {u32 nId,nValue;} Ov002MarkerOverride;
typedef struct Ov002ObjectContext {void *pOwnedTable;Ov002RecordList *pEntryList;char pad8[0x14];void *aSources[8];short aMarkerIds[4];char pad44[0x58];Ov002MarkerOverride aMarkerOverrides[5];} Ov002ObjectContext;
extern Ov002ObjectContext *data_ov002_0207fa14;
extern VecFx32 data_02041dc8;
extern void Ov002_EmitEntriesForSetBits(void);
extern Actor *Ov107_SpawnEntityClass(int);
extern void Ov107_MoveNodeAndRelayout(Actor *,VecFx32 *);
extern void Ov107_InitObjectFromSource(void *,Actor *);
extern int Ov002_GetStateWord(void);
extern int Ov002_GetMarkerEnemyLevel(Ov002MarkerRow *);
extern void Ov107_AiState_LoadResistances(Actor *,u32);
extern void *Ov002_FindSiblingOfKindE(int);
extern void Ov015_StoreWordAt0x3c(void *,Actor *);
void Ov002_CreateActorFromMarker(int nSourceIndex,int nRowIndex)
{
    Ov002ObjectContext *pCtx=data_ov002_0207fa14;
    Ov002MarkerRow *pRow=&pCtx->pEntryList->pRows[nRowIndex];
    Actor *pActor;
    int i;
    for(i=0;i<4;i++){
        if(pRow->bId==pCtx->aMarkerIds[i])break;
        if(pCtx->aMarkerIds[i]==-1){
            pCtx->aMarkerIds[i]=pRow->bId;
            switch(pRow->bId){
            case 0x46:pCtx->aMarkerIds[i+1]=0;break;
            case 0x62:pCtx->aMarkerIds[i+1]=0x56;break;
            case 0x47:pCtx->aMarkerIds[i+1]=4;break;
            case 0x4d:pCtx->aMarkerIds[i+1]=0x69;pCtx->aMarkerIds[i+2]=0x6a;break;
            case 0x21:pCtx->aMarkerIds[i+1]=2;break;
            case 0x53:case 0x54:case 0x68:case 0x71:case 0x72:Ov002_EmitEntriesForSetBits();break;
            }
            break;
        }
    }
    pActor=Ov107_SpawnEntityClass(pRow->bId);
    pActor->wFlags1ae|=0x80;
    Ov107_MoveNodeAndRelayout(pActor,&data_02041dc8);
    Ov107_InitObjectFromSource(pCtx->aSources[nSourceIndex],pActor);
    if(Ov002_GetStateWord()!=2000){
        int nLevel=Ov002_GetMarkerEnemyLevel(pRow);
        if(pActor->pLoadStats)pActor->pLoadStats(pActor,nLevel);
        if(pRow->nParam>0 && pActor->pLoadMsUpRecord)pActor->pLoadMsUpRecord(pActor,pRow->nParam);
    }
    if(pRow->nBoost){
        int nBoost=pRow->nBoost+pActor->nMarkerBoost;
        pActor->nMarkerBoost=nBoost>255?255:nBoost<0?0:(u8)nBoost;
    }
    pActor->nMarkerValue=pRow->nActorValue;
    pActor->nMarkerParam=pRow->nActorParam;
    Ov107_AiState_LoadResistances(pActor,pRow->nProfile);
    for(i=0;i<5;i++){
        if(pRow->bId==pCtx->aMarkerOverrides[i].nId){pActor->nMarkerOverride=pCtx->aMarkerOverrides[i].nValue;break;}
    }
    if(pRow->bId==0x55){
        void *pSibling=Ov002_FindSiblingOfKindE(nSourceIndex);
        Ov015_StoreWordAt0x3c(pSibling,pActor);
        if(pActor->flags40.bActive && pActor->pfnHandler0c)pActor->pfnHandler0c(pActor,0);
    }
}
