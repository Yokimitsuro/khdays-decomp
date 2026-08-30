/* Ov002_ScriptSpawnTimedSet: load and instantiate the current state's timed records. */
typedef struct VecFx32 { int x, y, z; } VecFx32;
typedef struct Ov002TimedClassDesc { const char *pName; int nOwnerArg; } Ov002TimedClassDesc;
typedef struct Ov002TimedSpawnRecord {
    signed char nSlot, nBucket;
    short nKey, nFlagIndex, nAngleDegrees;
    VecFx32 vPosition;
} Ov002TimedSpawnRecord;
typedef struct Ov002TimedSpawnSet {
    unsigned short wStateKey;
    signed char nCount;
    char bReserved;
    Ov002TimedSpawnRecord aRecords[1];
} Ov002TimedSpawnSet;
typedef struct Ov002SeatBlock {
    void *pOffsetTable;
    unsigned short wSeatMask;
    signed char cModuleId, nSkippedTimedCount;
} Ov002SeatBlock;
typedef struct Ov002RootContext {
    char pad0000[0x8ba8];
    short nState;
    char pad8baa[0x16e];
    signed char nTimedSpawnCount;
    char pad8d19[0x63];
    Ov002SeatBlock seats;
} Ov002RootContext;
extern Ov002RootContext *data_ov002_0207fa00;
extern unsigned char data_0204c240;
extern int func_ov002_0206b84c(void);
extern void func_ov002_0206e0f0(int bAlternate);
extern Ov002TimedSpawnSet *func_ov002_0206e144(int wKey);
extern void *func_ov002_0207a29c(void *pCount, const Ov002TimedClassDesc *pDesc);
extern void func_ov002_0207643c(int nModuleId, void *pClass);
extern int func_02023588(int nFlag);
extern int func_02020400(int nNumerator, int nDenominator);
extern void func_ov002_0207a32c(void *pClass, int nSlot, int nBucket, VecFx32 *pPos,
                             short nAngle, unsigned short wField, unsigned char bWidth, short nKey);
extern void func_020235e8(unsigned int wField, int nWidth, int nValue);
extern void func_ov002_0206cf4c(int nKey);
extern void func_ov002_0206e184(void);

void func_ov002_0206e1a4(int nModuleId, const char *pName, int nOwnerArg)
{
    Ov002RootContext *pRoot;
    Ov002SeatBlock *pSeats;
    int nState;
    Ov002TimedClassDesc desc;
    Ov002TimedSpawnSet *pSet;
    int nIndex;
    void *pClass;
    Ov002TimedSpawnSet *pCursor;
    VecFx32 *pPos;
    unsigned short wStateField;
    int nKey;
    pRoot = data_ov002_0207fa00;
    pSeats = &pRoot->seats;
    nState = func_ov002_0206b84c();
    if (data_0204c240 & 2)
        return;
    pSeats->cModuleId = -1;
    pSeats->nSkippedTimedCount = 0;
    pSeats->wSeatMask = 0;
    func_ov002_0206e0f0(0);
    pSet = func_ov002_0206e144(nState);
    if (pSet) {
        pSeats->cModuleId = nModuleId;
        desc.pName = pName;
        desc.nOwnerArg = nOwnerArg;
        pClass = func_ov002_0207a29c((void *)(int)pSet->nCount, &desc);
        func_ov002_0207643c(nModuleId, pClass);
        pRoot->nTimedSpawnCount = pSet->nCount;
        nIndex = 0;
        if (pSet->nCount > 0) {
            pCursor = pSet;
            pPos = &pCursor->aRecords[0].vPosition;
            do {
                if (pRoot->nState == 1 || !func_02023588(pCursor->aRecords[0].nFlagIndex + 9)) {
                    wStateField = pCursor->aRecords[0].nSlot * 2 + 0x20c0;
                    nKey = pCursor->aRecords[0].nKey;
                    if (pRoot->nState == 1 && func_02023588(pCursor->aRecords[0].nFlagIndex + 9))
                        nKey = 2;
                    func_ov002_0207a32c(pClass, pCursor->aRecords[0].nSlot,
                        pCursor->aRecords[0].nBucket, pPos,
                        (short)func_02020400(pCursor->aRecords[0].nAngleDegrees << 16, 360),
                        wStateField, 2, (short)nKey);
                    func_020235e8(wStateField, 2, 1);
                } else {
                    pSeats->nSkippedTimedCount++;
                }
                func_ov002_0206cf4c(pCursor->aRecords[0].nKey);
                nIndex++;
                pCursor = (Ov002TimedSpawnSet *)((char *)pCursor + 0x14);
                pPos = (VecFx32 *)((char *)pPos + 0x14);
            } while (nIndex < pSet->nCount);
        }
    }
    func_ov002_0206e184();
}
