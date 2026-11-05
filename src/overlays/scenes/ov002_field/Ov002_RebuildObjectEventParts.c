/* Ov002_RebuildObjectEventParts: preserve selected parts of an object across
 * its event reset, then restart its animation or clear it when none remain. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct Ov002PartOwnerTagFields {
    u8 nGroupIndex,nSlotIndex; unsigned short wReserved;
} Ov002PartOwnerTagFields;
typedef union Ov002PartOwnerTag {
    u32 raw; Ov002PartOwnerTagFields fields;
} Ov002PartOwnerTag;
typedef struct Ov107ObjectPart {
    u8 nId; u8 bFlags:2; s8 nBinding:4; u8 bHighFlags:2;
    u8 nMask; s8 nMode; Ov002PartOwnerTag ownerTag; int reserved;
} Ov107ObjectPart;
typedef struct Ov107Object Ov107Object;
struct Ov107Object {
    char pad0[0x14]; void (*pStateCallback)(Ov107Object *,int);
    char pad18[0x34]; short nPartCount; char pad4e[2]; Ov107ObjectPart aParts[8];
};
typedef struct Ov002ObjectSlot {
    Ov107Object *pObject; VecFx32 vAt; int nMode; s8 bEntryIndex; u8 nActiveEvent; char pad16[2];
} Ov002ObjectSlot;
typedef struct Ov002RecordGroup { u8 reserved,nLimit,nCount,pad; } Ov002RecordGroup;
typedef struct Ov002RecordEntryFlags { s8 nState:4,nValue:4; } Ov002RecordEntryFlags;
typedef struct Ov002RecordEntry {
    s8 nGroupCount; Ov002RecordEntryFlags bStateAndValue; char pad2[2]; Ov002RecordGroup aGroups[1];
} Ov002RecordEntry;
typedef struct Ov002RecordList { char pad0[8]; Ov002RecordEntry *apEntries[1]; } Ov002RecordList;
typedef struct Ov002ObjectContext {
    void *pOwned; Ov002RecordList *pEntryList; char pad8[0x3c]; Ov002ObjectSlot *pSlots;
    char pad48[0xb]; u8 nSeqAck;
} Ov002ObjectContext;
extern Ov002ObjectContext *data_ov002_0207fa14;
extern void Ov107_StartObject(Ov107Object *);
extern int Ov107_Spawner_AddSlot(Ov107Object *,u8,u8,int,s8,u32);
extern void Ov107_SetPartBinding(Ov107Object *,int,int);
extern void Ov107_Spawner_FreeDataBlocks(Ov107Object *);
extern void Ov002_StartSpawnerTrigger(int,int,int,VecFx32 *,int);

void Ov002_RebuildObjectEventParts(u8 nSlotIndex)
{
    u32 aOwnerTags[8];
    u8 aIds[8];
    s8 aBindings[8];
    Ov002RecordEntry *pRecord;
    u8 nMask;
    Ov002ObjectContext *pCtx;
    int i,j;
    Ov002ObjectSlot *pSlot;
    int k,nRestored;
    Ov002RecordGroup *pGroup;
    u8 nModeBits;
    pCtx=data_ov002_0207fa14;
    pSlot=&pCtx->pSlots[nSlotIndex];
    pRecord=pCtx->pEntryList->apEntries[pSlot->bEntryIndex];
    if(!(pRecord->bStateAndValue.nState&1)) {
        nRestored=0;
        k=0;
        if(pSlot->pObject->nPartCount>0) {
            nMask=pSlot->pObject->aParts[0].nMask;
            nModeBits=pSlot->pObject->aParts[0].nMode;
            for(i=0;i<pSlot->pObject->nPartCount;i++) {
                aIds[i]=pSlot->pObject->aParts[i].nId;
                aOwnerTags[i]=pSlot->pObject->aParts[i].ownerTag.raw;
                aBindings[i]=pSlot->pObject->aParts[i].nBinding;
            }
        }
        Ov107_StartObject(pSlot->pObject);
        pCtx->pSlots[nSlotIndex].nActiveEvent=-1;
        for(i=0;i<pRecord->nGroupCount;i++) {
            pGroup=&pRecord->aGroups[i];
            for(j=0;j<pGroup->nCount;j++,k++) {
                if(pGroup->nLimit==0xff || j<pGroup->nLimit) {
                    Ov107_Spawner_AddSlot(pSlot->pObject,aIds[k],nMask,0,(s8)(nModeBits==2?1:nModeBits),aOwnerTags[k]);
                    if(aBindings[k]>=0) Ov107_SetPartBinding(pSlot->pObject,k,aBindings[k]);
                    nRestored++;
                }
            }
        }
        if(nRestored==0) {
            pRecord->bStateAndValue.nState|=1;
            Ov107_Spawner_FreeDataBlocks(pSlot->pObject);
        } else {
            Ov002_StartSpawnerTrigger(nSlotIndex,pSlot->bEntryIndex,pSlot->nMode,&pSlot->vAt,1);
            if(pSlot->pObject->pStateCallback) pSlot->pObject->pStateCallback(pSlot->pObject,1);
        }
    }
    if(Session_IsActive()) pCtx->nSeqAck++;
}
