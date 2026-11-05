/* Ov002_CreateSpawner: make a field spawner for group nGroup of the enemy table in region nRegion
 * (Ov002_CreateObjectSlot), stamp its place, spread (+0x110), keep-near distance (+0x114), scale
 * (+0x118) and tag into its object, start its trigger sphere (Ov002_StartSpawnerTrigger) and add
 * a slot for each enemy its group's rows allow (Ov107_Spawner_AddSlot). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov107Object Ov107Object;
struct Ov107Object {
    char pad0[0x14];void (*pStateCallback)(Ov107Object *,int);char pad18[0x28];
    u32 dwStateFlags;void *pCallback;u16 wFlags;short nTag;char pad4c[0xb8];
    VecFx32 vSpawnAt;int fxSpread,fxKeepNear,fxScale;
};
typedef struct Ov002ObjectSlot {Ov107Object *pObject;VecFx32 vAt;int nMode;s8 bEntryIndex;u8 nActiveEvent;char pad16[2];} Ov002ObjectSlot;
typedef struct Ov002MarkerLookup {s8 nRowIndex;u8 nHandle;} Ov002MarkerLookup;
typedef struct Ov002RecordGroup {s8 nRowIndex;u8 nLimit,nCount;s8 nLastPlayer;} Ov002RecordGroup;
typedef struct Ov002RecordEntryFlags {s8 nState:4,nValue:4;} Ov002RecordEntryFlags;
typedef struct Ov002RecordEntry {s8 nGroupCount;Ov002RecordEntryFlags bStateAndValue;char pad2[2];Ov002RecordGroup aGroups[1];} Ov002RecordEntry;
typedef struct Ov002MarkerRow {u8 bId;char pad1[15];} Ov002MarkerRow;
typedef struct Ov002RecordList {u8 nRowCount,nEntryCount;char pad2[2];Ov002MarkerRow *pRows;Ov002RecordEntry *apEntries[1];} Ov002RecordList;
typedef struct Ov002ObjectContext {void *pOwnedTable;Ov002RecordList *pEntryList;char pad8[0x3c];Ov002ObjectSlot *pSlots;char pad48[4];Ov002MarkerLookup *pSlotLookup;u8 nLookupCount,nLookupInUse;} Ov002ObjectContext;
extern Ov002ObjectContext *data_ov002_0207fa14;
extern int Ov002_CreateObjectSlot(int);
extern void Ov002_StartSpawnerTrigger(int,int,int,VecFx32 *,int);
extern int Ov107_Spawner_AddSlot(Ov107Object *,u8,u8,int,s8,u32);
extern void *Ov002_FindSiblingOfKindE(int);
extern int Ov002_GetSlotTableByte(int);
extern void Ov015_SpotInstallTable(void *,Ov107Object *,int,u32);
void Ov002_CreateSpawner(int nGroup,int nRegion,u32 nMask,int nMode,VecFx32 *pAt,int fxSpread,int nTag,int fxScale,int fxKeepNear,VecFx32 *pTriggerAt,int fxTriggerRadius,int bShown)
{
    Ov002ObjectContext *pCtx;
    int i;
    Ov002RecordList *pList;
    Ov002RecordEntry *pRecord;
    int nIndex,j,k,nLookup;
    pCtx=data_ov002_0207fa14;
    pList=pCtx->pEntryList;
    pRecord=pList->apEntries[nGroup];
    if(!(pRecord->bStateAndValue.nState&1)){
        nIndex=Ov002_CreateObjectSlot(nRegion);
        pCtx->pSlots[nIndex].pObject->nTag=nTag;
        pCtx->pSlots[nIndex].pObject->fxScale=fxScale;
        pCtx->pSlots[nIndex].pObject->vSpawnAt=*pAt;
        pCtx->pSlots[nIndex].pObject->fxSpread=fxSpread;
        pCtx->pSlots[nIndex].pObject->fxKeepNear=fxKeepNear;
        if(nMode==4){pCtx->pSlots[nIndex].pObject->wFlags|=2;nMode=-1;}
        Ov002_StartSpawnerTrigger(nIndex,nGroup,fxTriggerRadius,pTriggerAt,bShown);
        pCtx->pSlots[nIndex].bEntryIndex=nGroup;
        pCtx->pSlots[nIndex].nActiveEvent=-1;
        for(i=0;i<pRecord->nGroupCount;i++){
            Ov002RecordGroup *pGroup=&pRecord->aGroups[i];
            nLookup=-1;
            for(j=0;j<pCtx->nLookupInUse;j++){
                if(pGroup->nRowIndex==pCtx->pSlotLookup[j].nRowIndex){nLookup=j;break;}
            }
            for(k=0;k<pGroup->nCount;k++){
                if(pGroup->nLimit==0xff || pGroup->nLimit>k){
                    Ov002MarkerRow *pRow=&pList->pRows[pRecord->aGroups[i].nRowIndex];
                    Ov107_Spawner_AddSlot(pCtx->pSlots[nIndex].pObject,pCtx->pSlotLookup[nLookup].nHandle,(u8)nMask,-1,(s8)nMode,((u16)(nIndex<<8))|(u8)i);
                    if(pRow->bId==0x55){
                        void *pSibling=Ov002_FindSiblingOfKindE(nRegion);
                        int nSlot=Ov002_GetSlotTableByte(nRegion);
                        Ov015_SpotInstallTable(pSibling,pCtx->pSlots[nIndex].pObject,nSlot,nMask);
                        if(pCtx->pSlots[nIndex].pObject->pStateCallback)pCtx->pSlots[nIndex].pObject->pStateCallback(pCtx->pSlots[nIndex].pObject,0);
                        pCtx->pSlots[nIndex].pObject->dwStateFlags&=~4;
                    }
                }
            }
        }
    }
}
