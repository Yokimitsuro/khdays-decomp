/* func_ov008_0206a564 -- Ov008_SetupItemMenu: bring the item menu screen up.
 * Loads the layout resource of slot 5 into block 9500, retargets the current
 * list's slot table cell (02069b60 on the menu context's list id) to the
 * origin, applies the layout template data_ov008_0208f5e8 with the slot-4
 * resource as its first word to the context, loads the slot-6 block (0x5d
 * entries), installs the dispatcher 0206b3f8, walks the list nodes (mode 2),
 * refreshes the pick set (02069ca4), hides widgets 4..8 and shows the first
 * (table byte +2) of them again.  The "unseen" marker (data_ov008_02090598
 * byte 6) is set when flag 0x200b is set, or once day 12 is reached and the
 * flag 0x3c2b + 02079264(0x34) is set; then the markers are armed.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define FLAG_ITEM_MENU_SEEN 0x200b
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
typedef short s16;
typedef struct Ov008MenuSubEntry {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02 */
    u8  nHelpText;            /* 0x03 */
} Ov008MenuSubEntry;

typedef struct Ov008MenuEntryDef {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02 */
    u8  nHelpText;            /* 0x03 */
    u8  nAnchor;              /* 0x04 */
    u8  nState;               /* 0x05: lock state */
    u8  bEnabled;             /* 0x06 */
    u8  nSubCount;            /* 0x07 */
    Ov008MenuSubEntry aSub[3]; /* 0x08 */
} Ov008MenuEntryDef;

extern Ov008MenuEntryDef data_ov008_02090598[];
extern Ov008MenuContext *func_ov008_02050cd4(void);                     /* Ov008_GetMenuContext */
extern Ov008SlotTable *func_ov008_02069b60(u16 nListId);
extern int   func_ov008_02050c28(void);                                 /* Ov008_GetCtxBlock9500 */
extern u32   func_ov008_02050f08(int nSlot);                            /* Ov008_PackSlotTag */
extern void  func_ov008_02055534(int nBlock, u32 nHandle);              /* Ov008_LoadLayoutResource */
extern void  func_ov008_0206abb8(u16 nTag, int nX, int nY);             /* Ov008_RetargetCellByTag */
extern int   func_ov008_02050c54(void);                                 /* Ov008_GetContext */
extern void  func_ov008_02054744(int nCtx, Ov008LayoutTemplate *pLayout);
extern void  func_ov008_02054678(int nCtx, void *pResource, int nCount);/* Ov008_LoadBlockProcessAndFree */
extern void  func_ov008_0205477c(int nCtx, void *pCallback);            /* ov008_StoreWordAt0x4a50 */
extern void  func_ov008_02054dd4(int nCtx, int nMode);                  /* Ov008_ForEachListNode */
extern void  func_ov008_02069ca4(void);
extern void *func_ov008_02054788(int nCtx, int nId);                    /* FindEntryById */
extern void  func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern int   func_02023588(int nFlag);                                  /* GameState_IsFlagSet */
extern u32   func_020235d0(int nField, int nBits);                      /* GameState_GetField */
extern int   func_ov008_02079264(int nId);
extern void  func_ov008_0206a138(void);                                 /* Ov008_ArmUnseenMarkers */
extern void  func_ov008_0206b3f8(void);                                 /* menu dispatcher */

void func_ov008_0206a564(void)
{
    Ov008LayoutTemplate layout = data_ov008_0208f5e8;
    int nBlock;
    int i;
    int nCtx;
    Ov008SlotTable *pTable;
    int nDay;
    int nFlag;

    pTable = func_ov008_02069b60(func_ov008_02050cd4()->nListId);
    nBlock = func_ov008_02050c28();
    func_ov008_02055534(nBlock, func_ov008_02050f08(5));
    func_ov008_0206abb8(pTable->nCellTag, 0, 0);
    nCtx = func_ov008_02050c54();
    layout.words[0] = func_ov008_02050f08(4);
    func_ov008_02054744(nCtx, &layout);
    func_ov008_02054678(nCtx, (void *)func_ov008_02050f08(6), 0x5d);
    func_ov008_0205477c(nCtx, (void *)func_ov008_0206b3f8);
    func_ov008_02054dd4(nCtx, 2);
    func_ov008_02069ca4();
    for (i = 0; i < WIDGET_COUNT; i++) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + WIDGET_FIRST), 0);
    }
    for (i = 0; i < pTable->nShown; i++) {
        if (i < WIDGET_COUNT) {
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + WIDGET_FIRST), 1);
        }
    }
    if (func_02023588(FLAG_ITEM_MENU_SEEN) == 0) {
        nDay = func_020235d0(0, 9);
        nFlag = func_ov008_02079264(0x34);
        if (nDay >= DAY_TIER_UNLOCK && func_02023588(nFlag + FLAG_TIER_BASE) != 0) {
            data_ov008_02090598[0].bEnabled = 1;
        }
    } else {
        data_ov008_02090598[0].bEnabled = 1;
    }
    func_ov008_0206a138();
}
