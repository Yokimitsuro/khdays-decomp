/* Ov025_Config_Setup -- Ov025_Config_Setup: open the config page.  The tag tracker of the 9500
 * block (02084a50) loads archive member 5 (Ov008_PackSlotTag 02084d18; 020891dc) and the tier
 * record of the page's tier (+2; 0209bf40) places its tagged cell at (0, 0) (0209cc88).  The
 * entry context (02084a7c) takes the layout template data_ov025_020b4148 with member 4 as its
 * resource (020883f8), loads the 0x5d entries of member 6 (Ov008_LoadBlockProcessAndFree
 * 0208832c), the input dispatcher 0209d4c8 (02088430) and releases the list slots in mode 2
 * (02088a7c); the option values are loaded (Ov025_Config_LoadValues 0209c084) and entries 4..8
 * hidden, then as many shown as the tier has rows.  The first menu entry (gOv025ConfigSettings)
 * is enabled when flag 0x200b is set, or from day 12 on once flag 0x3c2b + the 0x34 tier base
 * (020afda0) is set.  Codegen: declaration order nTracker, i, nCtx, pTier, bVisible (the
 * visibility flag reuses the tracker's r5). */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov008LayoutTemplate {
    u32  words[4];
} Ov008LayoutTemplate;

typedef struct Ov025ConfigTier {
    u16  nTag;                /* 0x00: the tracker cell tag */
    u8   nRows;               /* 0x02: the rows shown (entries 4..) */
    u8   aRow[15];            /* 0x03 */
} Ov025ConfigTier;            /* 0x12: gOv025ConfigLists[3] */

typedef struct Ov008ConfigSetting {
    s16  nId;                 /* 0x00 */
    u8   nText;               /* 0x02: its name, a cfg_&.s record */
    u8   nHelpText;           /* 0x03: its help, a cfg_&.s record */
    u8   nAnchor;             /* 0x04 */
    u8   nState;              /* 0x05: lock state */
    u8   bEnabled;            /* 0x06: 0 shows it as "?" */
    u8   nSubCount;           /* 0x07: its values; 0 for a heading */
    u8   aSub[0x18];          /* 0x08 */
} Ov008ConfigSetting;

typedef struct Ov025ConfigPage {
    s16  nField00;            /* 0x00 */
    u16  nTier;               /* 0x02 */
} Ov025ConfigPage;

extern Ov025ConfigPage *Ov025_GetPageA(void);                  /* Ov008_GetPageA */
extern Ov025ConfigTier *Ov025_GetPageTableEntry(u32 nTier);             /* Ov025_Config_GetTier */
extern int   Ov025_GetCtxBlock9500(void);                             /* Ov025_GetCtxBlock9500 */
extern u32   Ov025_PackSlotTag(int nMember);                      /* Ov008_PackSlotTag */
extern void  Ov025_LoadBlockDispatchThreeThenFree(int nTracker, u32 nTag);           /* Ov008_TagTracker_Load */
extern void  Ov025_RetargetCellByTag(u32 nTag, int nX, int nY);         /* Ov025_PlaceTaggedCell */
extern int   Ov025_GetContext(void);                             /* Ov008_GetCtxBlock4a7c */
extern void  Ov025_InitFromDescAndMark(int nCtx, Ov008LayoutTemplate *pLayout); /* Ov008_SetLayout */
extern void  Ov025_LoadBlockProcessAndFree(int nCtx, u32 nTag, int nCount);   /* Ov008_LoadBlockProcessAndFree */
extern void  Ov025_StoreWordAt0x4a50(int nCtx, void *pCallback);        /* Ov008_SetInputDispatcher */
extern void  Ov025_DispatchMenuInput(void);                             /* Ov008_DispatchMenuInput */
extern void  Ov025_ReleaseAllListSlots(int nCtx, int nMode);              /* Ov025_ReleaseAllListSlots */
extern void  Ov025_Config_LoadValues(void);                             /* Ov025_Config_LoadValues */
extern void *Ov025_FindEntryById(int nCtx, int nId);                /* FindEntryById */
extern void  Ov025_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern int   Ov025_GetSlideTableValue(int nIndex);                       /* Ov025_GetTierBase */
extern Ov008LayoutTemplate data_ov025_020b4148;
extern Ov008ConfigSetting gOv025ConfigSettings[];                     /* the Preferences page's settings */

void Ov025_Config_Setup(void)
{
    Ov008LayoutTemplate layout;
    int nTracker;
    int i;
    int nCtx;
    Ov025ConfigTier *pTier;
    int bVisible;
    int nDay;
    int nBase;

    layout = data_ov025_020b4148;
    pTier = Ov025_GetPageTableEntry(Ov025_GetPageA()->nTier);
    nTracker = Ov025_GetCtxBlock9500();
    Ov025_LoadBlockDispatchThreeThenFree(nTracker, Ov025_PackSlotTag(5));
    Ov025_RetargetCellByTag(pTier->nTag, 0, 0);
    nCtx = Ov025_GetContext();
    layout.words[0] = Ov025_PackSlotTag(4);
    Ov025_InitFromDescAndMark(nCtx, &layout);
    Ov025_LoadBlockProcessAndFree(nCtx, Ov025_PackSlotTag(6), 0x5d);
    Ov025_StoreWordAt0x4a50(nCtx, Ov025_DispatchMenuInput);
    Ov025_ReleaseAllListSlots(nCtx, 2);
    Ov025_Config_LoadValues();
    bVisible = 0;
    for (i = 0; i < 5; i++) {
        Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, i + 4), bVisible);
    }
    bVisible = 1;
    for (i = 0; i < pTier->nRows; i++) {
        if (i < 5) {
            Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, i + 4), bVisible);
        }
    }
    if (GameState_IsFlagSet(0x200b) == 0) {
        nDay = GameState_GetField(0, 9);
        nBase = Ov025_GetSlideTableValue(0x34);
        if (nDay < 12) {
            return;
        }
        if (GameState_IsFlagSet(nBase + 0x3c2b) == 0) {
            return;
        }
        gOv025ConfigSettings[0].bEnabled = 1;
        return;
    }
    gOv025ConfigSettings[0].bEnabled = 1;
}
