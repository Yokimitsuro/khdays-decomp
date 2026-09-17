/* func_ov025_0208b7d0 -- Ov025_Hub_InitEntries: settle the records hub's menu.  A mission list
 * (0208a13c) built from data_ov025_020b3870 with selector 7 tells whether any of the twelve slots
 * has entries (0208a304 with (slot << 8) | 7, 0208a2fc): +0x90; the day list of
 * data_ov025_020b387c with the current day (game-state field 9) as selector is built and freed
 * (0208a19c), and +0x8c is set from day 14 on.  The default entry (0208b0a4) becomes the hovered
 * one (+0x88), its parameter overrides swapped (0208896c), and the cursor entry 0x15 of the 4a7c
 * block (02084a7c) moves to its row (Ov008_GetEntryPos 020884c8 / Ov008_SetEntryPos 02088500).
 * Codegen: the slot tag's high part is the just-stored +0x90 word read back (a copy the compiler
 * keeps in r7 rather than a folded zero), declared before the u32 slot counter; the stack order
 * list, day descriptor, slot descriptor, position; both entry positions fetched before the reads. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct UiLayoutPos {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} UiLayoutPos;

typedef struct Ov008MissionResourceDescriptor {
    const char *pszPath;      /* 0x00: "UI/cm/msl_&.msi.z" */
    int  nSelector;           /* 0x04 */
    int  nListKind;           /* 0x08 */
} Ov008MissionResourceDescriptor;

typedef struct Ov008MissionListState {
    u8   data[0x24];
} Ov008MissionListState;

typedef struct Ov008MenuEntry {
    u8   pad_00[0xc];
    int  nId;                 /* 0x0c */
} Ov008MenuEntry;

typedef struct Ov025HubScene {
    int  nField00;            /* 0x00 */
    u8   strings[0xc];        /* 0x04: the hub string set */
    u8   surfaceTitle[0x3c];  /* 0x10: the title surface */
    u8   surfaceBody[0x28];   /* 0x4c: the second surface */
    int  bTextReady;          /* 0x74 */
    u8   pad_78[0x10];
    int  nHoverId;            /* 0x88: the hovered entry id, -1 for none */
    int  bDay14;              /* 0x8c: day 14 reached */
    int  bSlotMissions;       /* 0x90: a mission slot has entries */
} Ov025HubScene;

extern int   func_ov025_02084a7c(void);                             /* Ov008_GetCtxBlock4a7c */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern void  func_ov025_0208a13c(Ov008MissionListState *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov025_InitMissionList */
extern void  func_ov025_0208a304(Ov008MissionListState *pList, u32 nTag); /* Ov025_MissionList_SelectTag */
extern u16   func_ov025_0208a2fc(Ov008MissionListState *pList);     /* Ov025_MissionList_EntryCount */
extern void  func_ov025_0208a19c(Ov008MissionListState *pList);     /* Ov025_ReleaseMissionList */
extern int   func_ov025_0208b0a4(Ov025HubScene *pScene);            /* Ov025_Hub_PickDefaultEntry */
extern Ov008MenuEntry *func_ov025_0208843c(int nCtx, int nId);      /* FindEntryById */
extern void  func_ov025_0208896c(int nCtx, Ov008MenuEntry *pEntry); /* Ov008_SwapParamOverrides */
extern UiLayoutPos *func_ov025_020884c8(int nCtx, Ov008MenuEntry *pEntry); /* Ov008_GetEntryPos */
extern void  func_ov025_02088500(int nCtx, Ov008MenuEntry *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern const Ov008MissionResourceDescriptor data_ov025_020b3870;    /* the slot list (kind 3) */
extern const Ov008MissionResourceDescriptor data_ov025_020b387c;    /* the day list (kind 2) */

void func_ov025_0208b7d0(Ov025HubScene *pScene)
{
    int nCtx;
    u32 nBase;
    u32 nSlot;
    Ov008MissionListState list;
    Ov008MissionResourceDescriptor descDay;
    Ov008MissionResourceDescriptor descSlots;
    UiLayoutPos pos;
    Ov008MenuEntry *pEntry;
    Ov008MenuEntry *pCursor;
    UiLayoutPos *pCursorPos;
    UiLayoutPos *pEntryPos;

    nCtx = func_ov025_02084a7c();
    descDay = data_ov025_020b387c;
    descDay.nSelector = func_020235d0(0, 9);
    descSlots = data_ov025_020b3870;
    descSlots.nSelector = 7;
    func_ov025_0208a13c(&list, &descSlots);
    pScene->bSlotMissions = 0;
    nBase = pScene->bSlotMissions;
    for (nSlot = 0; nSlot < 12; nSlot++) {
        func_ov025_0208a304(&list, ((nBase | nSlot) << 8) | 7);
        if (func_ov025_0208a2fc(&list) != 0) {
            pScene->bSlotMissions = 1;
            break;
        }
    }
    func_ov025_0208a19c(&list);
    func_ov025_0208a13c(&list, &descDay);
    if (func_020235d0(0, 9) >= 14) {
        pScene->bDay14 = 1;
    }
    func_ov025_0208a19c(&list);
    pScene->nHoverId = func_ov025_0208b0a4(pScene);
    pEntry = func_ov025_0208843c(nCtx, pScene->nHoverId);
    func_ov025_0208896c(nCtx, pEntry);
    pCursor = func_ov025_0208843c(nCtx, 0x15);
    pCursorPos = func_ov025_020884c8(nCtx, pCursor);
    pEntryPos = func_ov025_020884c8(nCtx, pEntry);
    pos.x = pCursorPos->x;
    pos.y = pEntryPos->y;
    func_ov025_02088500(nCtx, pCursor, &pos);
}
