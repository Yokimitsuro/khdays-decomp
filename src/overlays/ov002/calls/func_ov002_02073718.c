/* Ov002_LoadObjectRecordsAndDrops: relocate the loaded em0 table and fill
 * marker drop defaults from the selected eid variant. */
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;
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
extern char data_ov002_0207f114[],data_ov002_0207f118[],data_ov002_0207f11c[],data_ov002_0207f124[],data_ov002_0207f128[];
extern int OS_SPrintf(char *,const char *,...);
extern int func_ov002_0206d86c(void);
extern u32 func_02024fe8(int,const char *);
extern void *func_0201ef9c(u32,int);
extern s16 func_02030788(void);
extern int func_ov002_02077b30(void);
extern void func_ov002_0206cf4c(int);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void func_ov002_02073718(void)
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
    OS_SPrintf(szMemberName,data_ov002_0207f11c,data_ov002_0207f124,(data_0204c240&4)?data_ov002_0207f114:data_ov002_0207f118);
    nArchive=func_ov002_0206d86c();
    nFile=func_02024fe8(func_ov002_0206d86c(),szMemberName);
    pRecords=func_0201ef9c((((nArchive+0x8000)&0xfffffc)<<7)|0x80000000|(nFile&(0xfffffc>>15)),2);
    pCtx->pOwnedTable=pRecords;
    pCtx->pEntryList=pRecords;
    pRecords->pRows=(Ov002MarkerRow *)((u32)pRecords->pRows+(u32)pRecords);
    for(i=0;i<pRecords->nEntryCount;i++)pRecords->apEntries[i]=(Ov002RecordEntry *)((u32)pRecords+(u32)pRecords->apEntries[i]);
    nVariant=pCtx->nDropVariant;
    pDrops=func_0201ef9c((u32)data_ov002_0207f128,2);
    for(i=0;i<pCtx->pEntryList->nRowCount;i++){
        pRow=&pCtx->pEntryList->pRows[i];
        if(pRow->nDropKey<0){
            pChoice=&pDrops->aRows[pRow->bId].aVariants[nVariant];
            pRow->nDropKey=pRow->nDropChance<0?-1:pChoice->nKey;
            pRow->nDropChance=pRow->nDropChance<0?0:pChoice->nChance;
            pRow->nDropEntry=-1;
        }else if(func_02030788()==0)pRow->nDropEntry=func_ov002_02077b30();
        if(pRow->nDropKey>=0 && pRow->nDropChance>0)func_ov002_0206cf4c(pRow->nDropKey);
        if((pRow->bId==7 || pRow->bId==8) && func_02030788()==0)pRow->nDropEntry=func_ov002_02077b30();
    }
    NNSi_FndFreeFromDefaultHeap(pDrops);
}
