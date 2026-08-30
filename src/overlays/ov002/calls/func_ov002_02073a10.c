/* Ov002_CreateSlotObjectAndStart: create a slot, initialize its object and
 * install the record's permitted marker parts before activating special links. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Ov002Vec3 {int x,y,z;} Ov002Vec3;
typedef struct Ov107Object Ov107Object;
struct Ov107Object {
    char pad0[0x14];void (*pStateCallback)(Ov107Object *,int);char pad18[0x28];
    u32 dwStateFlags;void *pCallback;u16 wFlags;short nObjTag;char pad4c[0xb8];
    Ov002Vec3 vObjectPos;int nObjA,nObjC,nObjB;
};
typedef struct Ov002ObjectSlot {Ov107Object *pObject;Ov002Vec3 vAt;int nMode;s8 bEntryIndex;u8 nActiveEvent;char pad16[2];} Ov002ObjectSlot;
typedef struct Ov002MarkerLookup {s8 nRowIndex;u8 nHandle;} Ov002MarkerLookup;
typedef struct Ov002RecordGroup {s8 nRowIndex;u8 nLimit,nCount;s8 nLastPlayer;} Ov002RecordGroup;
typedef struct Ov002RecordEntryFlags {s8 nState:4,nValue:4;} Ov002RecordEntryFlags;
typedef struct Ov002RecordEntry {s8 nGroupCount;Ov002RecordEntryFlags bStateAndValue;char pad2[2];Ov002RecordGroup aGroups[1];} Ov002RecordEntry;
typedef struct Ov002MarkerRow {u8 bId;char pad1[15];} Ov002MarkerRow;
typedef struct Ov002RecordList {u8 nRowCount,nEntryCount;char pad2[2];Ov002MarkerRow *pRows;Ov002RecordEntry *apEntries[1];} Ov002RecordList;
typedef struct Ov002ObjectContext {void *pOwnedTable;Ov002RecordList *pEntryList;char pad8[0x3c];Ov002ObjectSlot *pSlots;char pad48[4];Ov002MarkerLookup *pSlotLookup;u8 nLookupCount,nLookupInUse;} Ov002ObjectContext;
extern Ov002ObjectContext *data_ov002_0207fa14;
extern int func_ov002_02073bdc(int);
extern void func_ov002_02073c34(int,int,int,Ov002Vec3 *,int);
extern int func_ov107_020c1d3c(Ov107Object *,u8,u8,int,s8,u32);
extern void *func_ov002_02072ba8(int);
extern int func_ov002_02072754(int);
extern void func_ov015_020810c0(void *,Ov107Object *,int,u32);
void func_ov002_02073a10(int nEntry,int nKind,u32 nMask,int nMode,Ov002Vec3 *pObjectPos,int nObjA,int nObjTag,int nObjB,int nObjC,Ov002Vec3 *pAnimAt,int nAnimMode,int nAnimParam)
{
    Ov002ObjectContext *pCtx;
    int i;
    Ov002RecordList *pList;
    Ov002RecordEntry *pRecord;
    int nIndex,j,k,nLookup;
    pCtx=data_ov002_0207fa14;
    pList=pCtx->pEntryList;
    pRecord=pList->apEntries[nEntry];
    if(!(pRecord->bStateAndValue.nState&1)){
        nIndex=func_ov002_02073bdc(nKind);
        pCtx->pSlots[nIndex].pObject->nObjTag=nObjTag;
        pCtx->pSlots[nIndex].pObject->nObjB=nObjB;
        pCtx->pSlots[nIndex].pObject->vObjectPos=*pObjectPos;
        pCtx->pSlots[nIndex].pObject->nObjA=nObjA;
        pCtx->pSlots[nIndex].pObject->nObjC=nObjC;
        if(nMode==4){pCtx->pSlots[nIndex].pObject->wFlags|=2;nMode=-1;}
        func_ov002_02073c34(nIndex,nEntry,nAnimMode,pAnimAt,nAnimParam);
        pCtx->pSlots[nIndex].bEntryIndex=nEntry;
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
                    func_ov107_020c1d3c(pCtx->pSlots[nIndex].pObject,pCtx->pSlotLookup[nLookup].nHandle,(u8)nMask,-1,(s8)nMode,((u16)(nIndex<<8))|(u8)i);
                    if(pRow->bId==0x55){
                        void *pSibling=func_ov002_02072ba8(nKind);
                        int nSlot=func_ov002_02072754(nKind);
                        func_ov015_020810c0(pSibling,pCtx->pSlots[nIndex].pObject,nSlot,nMask);
                        if(pCtx->pSlots[nIndex].pObject->pStateCallback)pCtx->pSlots[nIndex].pObject->pStateCallback(pCtx->pSlots[nIndex].pObject,0);
                        pCtx->pSlots[nIndex].pObject->dwStateFlags&=~4;
                    }
                }
            }
        }
    }
}
