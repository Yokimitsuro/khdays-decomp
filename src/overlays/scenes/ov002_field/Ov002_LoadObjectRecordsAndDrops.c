/* Ov002_LoadObjectRecordsAndDrops: relocate the loaded em0 table and fill
 * marker drop defaults from the selected eid variant. */

#include "nitro/types.h"

typedef struct Ov002MarkerRow {
    u8 bId;u8 nKind:4,nHigh:4;char pad2[3];s8 nParam;char pad6[4];
    s16 nDropKey,nDropChance;s8 nDropEntry;char padf;
} Ov002MarkerRow;
typedef struct Ov002RecordEntry Ov002RecordEntry;
typedef struct Ov002RecordList {u8 nRowCount,nEntryCount;char pad2[2];Ov002MarkerRow *pRows;Ov002RecordEntry *apEntries[1];} Ov002RecordList;
typedef struct Ov002ObjectContext {Ov002RecordList *pOwnedTable,*pEntryList;char pad8[9];s8 nDropVariant;} Ov002ObjectContext;
typedef struct Ov002DropChoice {s16 nKey,nChance;} Ov002DropChoice;
typedef struct Ov002DropTableRow {Ov002DropChoice aVariants[6];} Ov002DropTableRow;
typedef struct Ov002DropTable {u32 header;Ov002DropTableRow aRows[1];} Ov002DropTable;
extern Ov002ObjectContext *data_ov002_0207fa14;
extern u8 data_0204c240;
extern char data_ov002_0207f114[],data_ov002_0207f118[],gOv0020Fmt[],gOv002EmName[],gOv002MiMiEidPath[];
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int Ov002_GetRootSub04(void);
extern u32 MsgArchive_FindEntryByName(int,const char *);
extern void *Archive_LoadFile(u32,int);
extern s16 Session_GetLocalPlayerIndex(void);
extern int Ov002_TakeEntryOfKind1(void);
extern void Ov002_AppendPendingId(int);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void Ov002_LoadObjectRecordsAndDrops(void)
{
    char szMemberName[16];
    Ov002ObjectContext *pCtx;
    Ov002RecordList *pRecords;
    Ov002DropTable *pDrops;
    Ov002MarkerRow *pRow;
    Ov002DropChoice *pChoice;
    int nArchive,nVariant,i;
    u32 nFile;
    pCtx=data_ov002_0207fa14;
    OS_SPrintf(szMemberName,gOv0020Fmt,gOv002EmName,(data_0204c240&4)?data_ov002_0207f114:data_ov002_0207f118);
    nArchive=Ov002_GetRootSub04();
    nFile=MsgArchive_FindEntryByName(Ov002_GetRootSub04(),szMemberName);
    pRecords=Archive_LoadFile((((nArchive+0x8000)&0xfffffc)<<7)|0x80000000|(nFile&(0xfffffc>>15)),2);
    pCtx->pOwnedTable=pRecords;
    pCtx->pEntryList=pRecords;
    pRecords->pRows=(Ov002MarkerRow *)((u32)pRecords->pRows+(u32)pRecords);
    for(i=0;i<pRecords->nEntryCount;i++)pRecords->apEntries[i]=(Ov002RecordEntry *)((u32)pRecords+(u32)pRecords->apEntries[i]);
    nVariant=pCtx->nDropVariant;
    pDrops=Archive_LoadFile((u32)gOv002MiMiEidPath,2);
    for(i=0;i<pCtx->pEntryList->nRowCount;i++){
        pRow=&pCtx->pEntryList->pRows[i];
        if(pRow->nDropKey<0){
            pChoice=&pDrops->aRows[pRow->bId].aVariants[nVariant];
            pRow->nDropKey=pRow->nDropChance<0?-1:pChoice->nKey;
            pRow->nDropChance=pRow->nDropChance<0?0:pChoice->nChance;
            pRow->nDropEntry=-1;
        }else if(Session_GetLocalPlayerIndex()==0)pRow->nDropEntry=Ov002_TakeEntryOfKind1();
        if(pRow->nDropKey>=0 && pRow->nDropChance>0)Ov002_AppendPendingId(pRow->nDropKey);
        if((pRow->bId==7 || pRow->bId==8) && Session_GetLocalPlayerIndex()==0)pRow->nDropEntry=Ov002_TakeEntryOfKind1();
    }
    NNSi_FndFreeFromDefaultHeap(pDrops);
}
