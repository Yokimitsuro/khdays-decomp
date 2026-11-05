/* Ov008_Config_Setup -- open the camp's Preferences page (screen 5; Ov025_Config_Setup is ov025's).
 * Loads the layout resource of slot 5 into block 9500, retargets the page's tagged cell (the
 * current list's page table entry) to the origin, applies the layout template data_ov008_0208f5e8
 * with the slot-4 resource as its first word to the context, loads the slot-6 block (0x5d
 * entries), installs the menu's input dispatcher, walks the list nodes (mode 2), loads the
 * settings' values (Ov008_Config_LoadValues), hides widgets 4..8 and shows as many of them again
 * as the page has rows (table byte +2).  Setting 0 (Controls, gOv008ConfigSettings) is enabled
 * when flag 0x200b is set, or from day 12 on once flag 0x3c2b + 02079264(0x34) is set; then
 * Ov008_Config_EnableModeSettings enables Mission Mode's own settings.
 */

#include "nitro/types.h"
#include "game/engine.h"

#define FLAG_CONTROLS_SETTING 0x200b
#define FLAG_TIER_BASE      0x3c2b
#define DAY_TIER_UNLOCK     12
#define WIDGET_FIRST        4
#define WIDGET_COUNT        5

typedef struct Ov008LayoutTemplate {
    u32 words[4];
} Ov008LayoutTemplate;

typedef struct Ov008MenuContext {
    u8  pad_00[2];
    u16 nListId;              /* 0x02 */
} Ov008MenuContext;

typedef struct Ov008SlotTable {
    u16 nCellTag;             /* 0x00 */
    u8  nShown;               /* 0x02: widgets shown */
} Ov008SlotTable;

extern Ov008LayoutTemplate data_ov008_0208f5e8;
typedef struct Ov008ConfigValue {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
} Ov008ConfigValue;

typedef struct Ov008ConfigSetting {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
    u8  nAnchor;              /* 0x04 */
    u8  nState;               /* 0x05: lock state */
    u8  bEnabled;             /* 0x06: 0 shows it as "?" */
    u8  nSubCount;            /* 0x07: its values; 0 for a heading */
    Ov008ConfigValue aSub[3]; /* 0x08 */
} Ov008ConfigSetting;

extern Ov008ConfigSetting gOv008ConfigSettings[];
extern Ov008MenuContext *Ov008_GetMenuContext(void);                     /* Ov008_GetMenuContext */
extern Ov008SlotTable *Ov008_GetPageTableEntry(unsigned int nListId);
extern int   Ov008_GetCtxBlock9500(void);                                 /* Ov008_GetCtxBlock9500 */
extern u32   Ov008_PackSlotTag(int nSlot);                            /* Ov008_PackSlotTag */
extern void  Ov008_LoadLayoutResource(int nBlock, u32 nHandle);              /* Ov008_LoadLayoutResource */
extern void  Ov008_RetargetCellByTag(unsigned int nTag, int nX, int nY);             /* Ov008_RetargetCellByTag */
extern int   Ov008_GetContext(void);                                 /* Ov008_GetContext */
extern void  Ov008_InitFromDescAndMark(int nCtx, Ov008LayoutTemplate *pLayout);
extern void  Ov008_LoadBlockProcessAndFree(int nCtx, void *pResource, int nCount);/* Ov008_LoadBlockProcessAndFree */
extern void  Ov008_StoreWordAt0x4a50(int nCtx, void *pCallback);            /* ov008_StoreWordAt0x4a50 */
extern void  Ov008_ForEachListNode(int nCtx, int nMode);                  /* Ov008_ForEachListNode */
extern void  Ov008_Config_LoadValues(void);
extern void *Ov008_FindEntryById(int nCtx, int nId);                    /* FindEntryById */
extern void  Ov008_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern int   Ov008_GetSlideTableValue(int nId);
extern void  Ov008_Config_EnableModeSettings(void);                                 /* Ov008_Config_EnableModeSettings */
extern void  Ov008_DispatchMenuInput(void);                                 /* menu dispatcher */

void Ov008_Config_Setup(void)
{
    Ov008LayoutTemplate layout = data_ov008_0208f5e8;
    int nBlock;
    int i;
    int nCtx;
    Ov008SlotTable *pTable;
    int nDay;
    int nFlag;

    pTable = Ov008_GetPageTableEntry(Ov008_GetMenuContext()->nListId);
    nBlock = Ov008_GetCtxBlock9500();
    Ov008_LoadLayoutResource(nBlock, Ov008_PackSlotTag(5));
    Ov008_RetargetCellByTag(pTable->nCellTag, 0, 0);
    nCtx = Ov008_GetContext();
    layout.words[0] = Ov008_PackSlotTag(4);
    Ov008_InitFromDescAndMark(nCtx, &layout);
    Ov008_LoadBlockProcessAndFree(nCtx, (void *)Ov008_PackSlotTag(6), 0x5d);
    Ov008_StoreWordAt0x4a50(nCtx, (void *)Ov008_DispatchMenuInput);
    Ov008_ForEachListNode(nCtx, 2);
    Ov008_Config_LoadValues();
    for (i = 0; i < WIDGET_COUNT; i++) {
        Ov008_SetEntrySlotsVisible(nCtx, Ov008_FindEntryById(nCtx, i + WIDGET_FIRST), 0);
    }
    for (i = 0; i < pTable->nShown; i++) {
        if (i < WIDGET_COUNT) {
            Ov008_SetEntrySlotsVisible(nCtx, Ov008_FindEntryById(nCtx, i + WIDGET_FIRST), 1);
        }
    }
    if (GameState_IsFlagSet(FLAG_CONTROLS_SETTING) == 0) {
        nDay = GameState_GetField(0, 9);
        nFlag = Ov008_GetSlideTableValue(0x34);
        if (nDay >= DAY_TIER_UNLOCK && GameState_IsFlagSet(nFlag + FLAG_TIER_BASE) != 0) {
            gOv008ConfigSettings[0].bEnabled = 1;
        }
    } else {
        gOv008ConfigSettings[0].bEnabled = 1;
    }
    Ov008_Config_EnableModeSettings();
}
