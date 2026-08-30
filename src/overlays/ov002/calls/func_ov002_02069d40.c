typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Ov002PanelSlot {
    int nId, nIcon;
    u16 wRecordedValue, wCurrentValue, wState, wReserved;
} Ov002PanelSlot;
typedef struct Ov002PanelParams {
    Ov002PanelSlot aSlots[4];
    u16 wInitialValue, pad42;
    u32 nEnabledMask;
    s16 *pKeys;
    s16 nKeyCount, pad4e;
    void *pSharedState;
    int nInitOptionA, nInitOptionB;
} Ov002PanelParams;
typedef struct Ov002MissionMemberHeader {
    u8 nMemberId, nHeaderByte1;
    u8 nTally, bMemberKind;
    u16 wHead4, wHead6;
} Ov002MissionMemberHeader;
typedef struct Ov002MissionMemberBody {
    char pad000[6];
    u16 wRecordedValue;
} Ov002MissionMemberBody;
typedef struct Ov002MissionMember {
    Ov002MissionMemberHeader header;
    Ov002MissionMemberBody body;
    char pad010[0xf4];
} Ov002MissionMember;
typedef struct SessionSlotTable { int pad0, nSlotCount; } SessionSlotTable;
typedef struct SessionSlotInfo { int bOccupied, nMemberKind; } SessionSlotInfo;
typedef struct Ov002PauseSlot {
    int nObject;
    u8 bSeatFlags, pad5, nInitOptionA, nInitOptionB;
    s8 nRequestLevel;
    char pad009[3];
    int nRequestParam;
    s16 nRequestDuration, pad12;
    int nRunningTotal;
    s16 nPendingTotal;
    s8 nRequestId;
    s8 aCrawlSlotIndex[4];
    char pad01f[0x59];
} Ov002PauseSlot;
typedef struct Ov002TallyRow { int aCounters[11]; } Ov002TallyRow;
typedef struct Ov002SessionBlock {
    int nSessionToken;
    void *pMarkers;
    Ov002TallyRow aTallyRows[4];
    char pad0b8[16];
} Ov002SessionBlock;
typedef struct Ov002KeyEntry { char pad000[0x40]; s16 nKey, nValue; } Ov002KeyEntry;
typedef struct Ov002KeyEntryTable {
    Ov002KeyEntry *pKeyEntries;
    u8 bFlags, nKeyEntryCount, nSeedKeyCount, pad7;
    s16 anSeedKeys[24];
} Ov002KeyEntryTable;
typedef struct Ov002RootContext {
    char pad0000[0x8bc4];
    int nField8bc4;
    s16 nField8bc8, pad8bca;
    Ov002SessionBlock session;
    Ov002PauseSlot pause;
    char pad8d0c[8];
    Ov002KeyEntryTable keyTable;
} Ov002RootContext;
typedef struct Ov002DayClock { u8 nModeFlags; } Ov002DayClock;
typedef struct Ov002PanelThresholds { char pad000[4]; u16 wHiddenGroups; char pad006[8]; u16 nMetric; } Ov002PanelThresholds;
typedef struct GameClassDescriptor {
    u16 nClassId, nGroupId;
    int (*pfnOpen)(void *);
    void (*pfnClose)(void);
    int nAuxSize;
    int *pArena;
} GameClassDescriptor;

extern Ov002RootContext *data_ov002_0207fa00;
extern Ov002MissionMember data_0204c678[];
extern const s8 data_ov002_0207ef68[];
extern const GameClassDescriptor data_ov002_0207e8c8;
extern Ov002DayClock data_0204c240;
extern Ov002PanelThresholds data_0204c254;
extern SessionSlotTable *CARDi_GetRomAccessor_0x020315f4(void);
extern int func_02030670(void);
extern u8 func_ov022_020882f8(void);
extern int func_ov022_020882e0(int);
extern SessionSlotInfo *func_020315c0(int);
extern u32 func_02030788(void);
extern void *func_ov002_02073898(void);
extern u8 func_020358f4(int, int);
extern int func_02023930(const GameClassDescriptor *, void *);
extern u16 *func_02035874(int, int);
extern u16 *func_02035978(int, int);
extern void func_ov002_0205de68(int, u16);
extern void func_ov002_0205e358(int, int);
extern int func_020357f4(int, int);
extern void func_ov002_0205dcd4(int, int);
extern void func_ov002_0205e4dc(void);
extern void func_ov002_02056e80(void);
extern int func_ov002_02061b80(void);
extern void func_ov002_02061978(int, int, int);
extern s16 func_ov002_0206dbe0(void);
extern void func_ov002_02061d64(int, int);
extern u16 func_02020a9c(void);
extern void func_ov002_020574e4(int);
extern void func_ov002_02063638(int, int);
extern void func_ov002_020574a4(int, int);
extern void MI_CpuFill8(void *, int, u32);
extern void func_ov002_0205759c(u16);

static inline int IsExcludedSlot(u16 nId)
{
    int bExcluded = 0;
    switch (nId) {
    case 12:
        bExcluded = 1;
        break;
    }
    return bExcluded;
}

/* Creates the gameplay HUD, ordering the local player first, then restores
 * participant values, enabled channels, entries, totals and pending requests.
 * Member header and recorded-value cursors are deliberately separate. */
void func_ov002_02069d40(void)
{
    Ov002PanelParams params;
    s16 aKeys[120];
    Ov002MissionMemberHeader memberHeader;
    Ov002RootContext *pRoot;
    Ov002PauseSlot *pPause;
    SessionSlotTable *pSession;
    Ov002MissionMember *pHeader;
    Ov002MissionMember *pOnline;
    const Ov002MissionMember *pRecord;
    Ov002PanelSlot *pSlot;
    SessionSlotInfo *pPeer;
    Ov002KeyEntryTable *pKeyTable;
    Ov002MissionMemberBody *pMemberBody;
    u8 nValue;
    u16 *pEntry;
    int nIndex, nMember, nPeer, nTotal, nOther;
    int nKeyCount;

    pRoot = data_ov002_0207fa00;
    pPause = &pRoot->pause;
    pSession = CARDi_GetRomAccessor_0x020315f4();
    params.wInitialValue = 100;
    for (nIndex = 0; nIndex < 4; nIndex++) {
        params.aSlots[nIndex].nId = -1;
        params.aSlots[nIndex].nIcon = -1;
    }
    if (!func_02030670()) {
        nIndex = 0;
        if (nIndex < func_ov022_020882f8()) {
            pHeader = data_0204c678;
            pRecord = data_0204c678;
            pSlot = params.aSlots;
            do {
                memberHeader = pHeader->header;
                pSlot->nId = memberHeader.nMemberId;
                pSlot->nIcon = data_ov002_0207ef68[memberHeader.bMemberKind];
                pSlot->wRecordedValue = pRecord->body.wRecordedValue;
                pSlot->wState = 0;
                pSlot->wCurrentValue = func_ov022_020882e0(nIndex);

                pHeader++;
                pRecord++;
                pSlot++;
                nIndex++;
            } while (nIndex < func_ov022_020882f8());
        }
    } else {
        nPeer = 0;
        nMember = nPeer;
        nOther = 1;
        if (nPeer < pSession->nSlotCount) {
            pOnline = data_0204c678;
            do {
                pPeer = func_020315c0(nPeer);
                if (pPeer != 0) {
                    pMemberBody = &pOnline->body;
                    if ((u32)nPeer == func_02030788()) {
                        params.aSlots[0].nId = nMember;
                        params.aSlots[0].nIcon = data_ov002_0207ef68[pPeer->nMemberKind];
                        params.aSlots[0].wRecordedValue = pMemberBody->wRecordedValue;
                        params.aSlots[0].wCurrentValue = func_ov022_020882e0(nMember);
                        params.aSlots[0].wState = 0;
                    } else {
                        params.aSlots[nOther].nId = nMember;
                        params.aSlots[nOther].nIcon = data_ov002_0207ef68[pPeer->nMemberKind];
                        params.aSlots[nOther].wRecordedValue = pMemberBody->wRecordedValue;
                        params.aSlots[nOther].wCurrentValue = func_ov022_020882e0(nMember);
                        params.aSlots[nOther].wState = 0;
                        nOther++;
                    }
                    pOnline++;
                    nMember++;
                }
                nPeer++;
            } while (nPeer < pSession->nSlotCount);
        }
    }
    params.pSharedState = func_ov002_02073898();
    pKeyTable = &pRoot->keyTable;
    nKeyCount = 0;
    for (nIndex = 0; nIndex < pKeyTable->nKeyEntryCount; nIndex++) {
        aKeys[nIndex] = pKeyTable->pKeyEntries[nIndex].nKey;
        nKeyCount++;
    }
    params.pKeys = aKeys;
    params.nKeyCount = nKeyCount;
    params.nEnabledMask = 0;
    for (nIndex = 0; nIndex < 15; nIndex++) {
        if (func_020358f4(func_02030788(), nIndex + 1)) params.nEnabledMask |= 1u << nIndex;
    }
    params.nInitOptionA = pPause->nInitOptionA;
    params.nInitOptionB = pPause->nInitOptionB;
    pPause->nObject = func_02023930(&data_ov002_0207e8c8, &params);
    for (nIndex = 0; nIndex < 24; nIndex++) {
        pEntry = func_02035874(func_02030788(), nIndex);
        if (pEntry != 0 && !IsExcludedSlot(pEntry[0])) func_ov002_0205de68(pEntry[0], pEntry[1]);
    }
    for (nIndex = 0; nIndex < 18; nIndex++) {
        pEntry = func_02035978(func_02030788(), nIndex);
        if (pEntry != 0) func_ov002_0205e358(pEntry[0], pEntry[1]);
    }
    for (nIndex = 0; nIndex < 15; nIndex++) {
        if ((params.nEnabledMask & (1u << nIndex)) &&
            (!(data_0204c240.nModeFlags & 2) ||
            ((!(data_0204c254.wHiddenGroups & 1) || nIndex >= 12) &&
            (!(data_0204c254.wHiddenGroups & 2) || nIndex < 12)))) {
            nValue = func_020357f4(func_02030788(), nIndex);
            func_ov002_0205dcd4((u8)nIndex, nValue);
        }
    }
    func_ov002_0205e4dc();
    func_ov002_02056e80();
    if (func_ov002_02061b80()) {
        nTotal = 0;
        for (nIndex = 0; nIndex < func_ov022_020882f8(); nIndex++) {
            nTotal += pRoot->session.aTallyRows[nIndex].aCounters[2];
        }
        func_ov002_02061978(nTotal, 0, 0);
    }
    if (pRoot->nField8bc4 > 0) func_ov002_02061d64(0, func_ov002_0206dbe0());
    if (pPause->nRequestId >= 0 && func_02020a9c() != 0x2a) {
        func_ov002_020574e4(pPause->nRequestId);
        func_ov002_02063638(pPause->nRequestParam, pPause->nRequestDuration);
        if (pPause->nPendingTotal >= 0) {
            pPause->nRunningTotal = pPause->nPendingTotal;
            pPause->nPendingTotal = -1;
        }
        func_ov002_020574a4(pPause->nRunningTotal, 0);
    }
    MI_CpuFill8(pPause->aCrawlSlotIndex, 0xff, 4);
    if ((data_0204c240.nModeFlags & 2) && !(data_0204c240.nModeFlags & 4)) func_ov002_0205759c(data_0204c254.nMetric);
}
