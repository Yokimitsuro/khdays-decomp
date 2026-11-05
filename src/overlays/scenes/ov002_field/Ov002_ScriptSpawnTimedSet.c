/* Ov002_ScriptSpawnTimedSet: load and instantiate the current state's timed records. */

#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct Ov002TimedClassDesc { const char *pName; int nOwnerArg; } Ov002TimedClassDesc;
typedef struct Ov002TimedSpawnRecord {
    signed char nSlot, nRoom;
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
extern int Ov002_GetStateWord(void);
extern void Ov002_LoadOffsetTableOnce(int bAlternate);
extern Ov002TimedSpawnSet *Ov002_FindHandlerByKey(int wKey);
extern void *Ov002_CreateTimedClass(int nCount, const Ov002TimedClassDesc *pDesc);
extern void Ov002_SetModuleSlot(int nModuleId, void *pClass);
extern int func_02020400(int nNumerator, int nDenominator);
extern void Ov002_SpawnTimedElementAt(void *pClass, int nSlot, int nRoom, VecFx32 *pPos,
                             short nAngle, unsigned short wField, unsigned char bWidth, short nKey);
extern void Ov002_AppendPendingId(int nKey);
extern void Ov002_FreeRootBuffer0x8d7c(void);

void Ov002_ScriptSpawnTimedSet(int nModuleId, const char *pName, int nOwnerArg)
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
    nState = Ov002_GetStateWord();
    if (data_0204c240 & 2)
        return;
    pSeats->cModuleId = -1;
    pSeats->nSkippedTimedCount = 0;
    pSeats->wSeatMask = 0;
    Ov002_LoadOffsetTableOnce(0);
    pSet = Ov002_FindHandlerByKey(nState);
    if (pSet) {
        pSeats->cModuleId = nModuleId;
        desc.pName = pName;
        desc.nOwnerArg = nOwnerArg;
        pClass = Ov002_CreateTimedClass(pSet->nCount, &desc);
        Ov002_SetModuleSlot(nModuleId, pClass);
        pRoot->nTimedSpawnCount = pSet->nCount;
        nIndex = 0;
        if (pSet->nCount > 0) {
            pCursor = pSet;
            pPos = &pCursor->aRecords[0].vPosition;
            do {
                if (pRoot->nState == 1 || !GameState_IsFlagSet(pCursor->aRecords[0].nFlagIndex + 9)) {
                    wStateField = pCursor->aRecords[0].nSlot * 2 + 0x20c0;
                    nKey = pCursor->aRecords[0].nKey;
                    if (pRoot->nState == 1 && GameState_IsFlagSet(pCursor->aRecords[0].nFlagIndex + 9))
                        nKey = 2;
                    Ov002_SpawnTimedElementAt(pClass, pCursor->aRecords[0].nSlot,
                        pCursor->aRecords[0].nRoom, pPos,
                        (short)func_02020400(pCursor->aRecords[0].nAngleDegrees << 16, 360),
                        wStateField, 2, (short)nKey);
                    GameState_SetField(wStateField, 2, 1);
                } else {
                    pSeats->nSkippedTimedCount++;
                }
                Ov002_AppendPendingId(pCursor->aRecords[0].nKey);
                nIndex++;
                pCursor = (Ov002TimedSpawnSet *)((char *)pCursor + 0x14);
                pPos = (VecFx32 *)((char *)pPos + 0x14);
            } while (nIndex < pSet->nCount);
        }
    }
    Ov002_FreeRootBuffer0x8d7c();
}
