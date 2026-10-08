#include "nitro/types.h"

#include "game/class_descriptor.h"
#include "game/engine.h"

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
extern Ov002RootContext *data_ov002_0207fa00;
extern Ov002MissionMember gPartyMembers[];
extern const s8 data_ov002_0207ef68[];
extern const GameClassDescriptor data_ov002_0207e8c8;
extern Ov002DayClock data_0204c240;
extern Ov002PanelThresholds data_0204c254;
extern u8 func_ov022_020882f8(void);
extern int Ov022_GetEntryField12(int);
extern SessionSlotInfo *Slot4_GetIfOccupied(int);
extern void *Ov002_Event_GetBlock3C(void);
extern int InstantiateClass(const GameClassDescriptor *, void *);
extern u16 *Slot_GetEntryIfBothSet(int, int);
extern u16 *Slot_GetEntryIfCounted(int, int);
extern void Ov002_PanelSetEntryTag(int, u16);
extern void Ov002_PanelAddSubEntryAndRepaint(int, int);
extern void Ov002_HudSetSlotValue(int, int);
extern void Ov002_Panel_RestoreRowsIfAny(void);
extern void Ov002_RepublishHud(void);
extern int Ov002_IsPanelModeSet(void);
extern void Ov002_AddToPanelTotal(int, int, int);
extern s16 Ov002_GetRootField8bc8(void);
extern void Ov002_StartHudTimer(int, int);
extern void Ov002_SetPanelField01b8(int);
extern void Ov002_Field_RequestTransfer(int, int);
extern void Ov002_ForwardWithOptionalPublish(int, int);
extern void MI_CpuFill8(void *, int, u32);
extern void Ov002_Hud_RefreshUnless8(int);

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
void Ov002_CreateAndRestoreHud(void)
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
    pSession = (SessionSlotTable *)Session_GetSetup();
    params.wInitialValue = 100;
    for (nIndex = 0; nIndex < 4; nIndex++) {
        params.aSlots[nIndex].nId = -1;
        params.aSlots[nIndex].nIcon = -1;
    }
    if (!Session_IsActive()) {
        nIndex = 0;
        if (nIndex < func_ov022_020882f8()) {
            pHeader = gPartyMembers;
            pRecord = gPartyMembers;
            pSlot = params.aSlots;
            do {
                memberHeader = pHeader->header;
                pSlot->nId = memberHeader.nMemberId;
                pSlot->nIcon = data_ov002_0207ef68[memberHeader.bMemberKind];
                pSlot->wRecordedValue = pRecord->body.wRecordedValue;
                pSlot->wState = 0;
                pSlot->wCurrentValue = Ov022_GetEntryField12(nIndex);

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
            pOnline = gPartyMembers;
            do {
                pPeer = Slot4_GetIfOccupied(nPeer);
                if (pPeer != 0) {
                    pMemberBody = &pOnline->body;
                    if ((u32)nPeer == Session_GetLocalPlayerIndex()) {
                        params.aSlots[0].nId = nMember;
                        params.aSlots[0].nIcon = data_ov002_0207ef68[pPeer->nMemberKind];
                        params.aSlots[0].wRecordedValue = pMemberBody->wRecordedValue;
                        params.aSlots[0].wCurrentValue = Ov022_GetEntryField12(nMember);
                        params.aSlots[0].wState = 0;
                    } else {
                        params.aSlots[nOther].nId = nMember;
                        params.aSlots[nOther].nIcon = data_ov002_0207ef68[pPeer->nMemberKind];
                        params.aSlots[nOther].wRecordedValue = pMemberBody->wRecordedValue;
                        params.aSlots[nOther].wCurrentValue = Ov022_GetEntryField12(nMember);
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
    params.pSharedState = Ov002_Event_GetBlock3C();
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
        if (Slot_EvalPackedParam(Session_GetLocalPlayerIndex(), nIndex + 1)) params.nEnabledMask |= 1u << nIndex;
    }
    params.nInitOptionA = pPause->nInitOptionA;
    params.nInitOptionB = pPause->nInitOptionB;
    pPause->nObject = InstantiateClass(&data_ov002_0207e8c8, &params);
    for (nIndex = 0; nIndex < 24; nIndex++) {
        pEntry = Slot_GetEntryIfBothSet(Session_GetLocalPlayerIndex(), nIndex);
        if (pEntry != 0 && !IsExcludedSlot(pEntry[0])) Ov002_PanelSetEntryTag(pEntry[0], pEntry[1]);
    }
    for (nIndex = 0; nIndex < 18; nIndex++) {
        pEntry = Slot_GetEntryIfCounted(Session_GetLocalPlayerIndex(), nIndex);
        if (pEntry != 0) Ov002_PanelAddSubEntryAndRepaint(pEntry[0], pEntry[1]);
    }
    for (nIndex = 0; nIndex < 15; nIndex++) {
        if ((params.nEnabledMask & (1u << nIndex)) &&
            (!(data_0204c240.nModeFlags & 2) ||
            ((!(data_0204c254.wHiddenGroups & 1) || nIndex >= 12) &&
            (!(data_0204c254.wHiddenGroups & 2) || nIndex < 12)))) {
            nValue = Load2DArrayU8(Session_GetLocalPlayerIndex(), nIndex);
            Ov002_HudSetSlotValue((u8)nIndex, nValue);
        }
    }
    Ov002_Panel_RestoreRowsIfAny();
    Ov002_RepublishHud();
    /* Ov002_IsPanelModeSet takes the value it returns when no panel is installed; the ROM hands it
     * whatever Ov002_RepublishHud left in r0 (9 when the member is 9, otherwise what
     * Ov002_PanelSetSecondaryFlag left). There may be no panel (mission 61 has none), but then
     * the value does not matter: the branch only sums the tally rows and calls
     * Ov002_AddToPanelTotal, which returns at once without a panel. */
    if (Ov002_IsPanelModeSet()) {
        nTotal = 0;
        for (nIndex = 0; nIndex < func_ov022_020882f8(); nIndex++) {
            nTotal += pRoot->session.aTallyRows[nIndex].aCounters[2];
        }
        Ov002_AddToPanelTotal(nTotal, 0, 0);
    }
    if (pRoot->nField8bc4 > 0) Ov002_StartHudTimer(0, Ov002_GetRootField8bc8());
    if (pPause->nRequestId >= 0 && LoadGlobalU16At0() != 0x2a) {
        Ov002_SetPanelField01b8(pPause->nRequestId);
        Ov002_Field_RequestTransfer(pPause->nRequestParam, pPause->nRequestDuration);
        if (pPause->nPendingTotal >= 0) {
            pPause->nRunningTotal = pPause->nPendingTotal;
            pPause->nPendingTotal = -1;
        }
        Ov002_ForwardWithOptionalPublish(pPause->nRunningTotal, 0);
    }
    MI_CpuFill8(pPause->aCrawlSlotIndex, 0xff, 4);
    if ((data_0204c240.nModeFlags & 2) && !(data_0204c240.nModeFlags & 4)) Ov002_Hud_RefreshUnless8(data_0204c254.nMetric);
}
