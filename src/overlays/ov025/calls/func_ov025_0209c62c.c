/* func_ov025_0209c62c -- Ov025_Config_Setup: open the config page.  The tag tracker of the 9500
 * block (02084a50) loads archive member 5 (Ov008_PackSlotTag 02084d18; 020891dc) and the tier
 * record of the page's tier (+2; 0209bf40) places its tagged cell at (0, 0) (0209cc88).  The
 * entry context (02084a7c) takes the layout template data_ov025_020b4148 with member 4 as its
 * resource (020883f8), loads the 0x5d entries of member 6 (Ov008_LoadBlockProcessAndFree
 * 0208832c), the input dispatcher 0209d4c8 (02088430) and releases the list slots in mode 2
 * (02088a7c); the option values are loaded (Ov025_Config_LoadValues 0209c084) and entries 4..8
 * hidden, then as many shown as the tier has rows.  The first menu entry (data_ov025_020b4f64)
 * is enabled when flag 0x200b is set, or from day 12 on once flag 0x3c2b + the 0x34 tier base
 * (020afda0) is set.  Codegen: declaration order nTracker, i, nCtx, pTier, bVisible (the
 * visibility flag reuses the tracker's r5). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov008LayoutTemplate {
    u32  words[4];
} Ov008LayoutTemplate;

typedef struct Ov025ConfigTier {
    u16  nTag;                /* 0x00: the tracker cell tag */
    u8   nRows;               /* 0x02: the rows shown (entries 4..) */
    u8   aRow[15];            /* 0x03 */
} Ov025ConfigTier;            /* 0x12: data_ov025_020b4ee8[3] */

typedef struct Ov008MenuEntryDef {
    s16  nId;                 /* 0x00 */
    u8   nText;               /* 0x02 */
    u8   nHelpText;           /* 0x03 */
    u8   nAnchor;             /* 0x04 */
    u8   nState;              /* 0x05: lock state */
    u8   bEnabled;            /* 0x06 */
    u8   nSubCount;           /* 0x07 */
    u8   aSub[0x18];          /* 0x08 */
} Ov008MenuEntryDef;

typedef struct Ov025ConfigPage {
    s16  nField00;            /* 0x00 */
    u16  nTier;               /* 0x02 */
} Ov025ConfigPage;

extern Ov025ConfigPage *func_ov025_02084afc(void);                  /* Ov008_GetPageA */
extern Ov025ConfigTier *func_ov025_0209bf40(u32 nTier);             /* Ov025_Config_GetTier */
extern int   func_ov025_02084a50(void);                             /* Ov025_GetCtxBlock9500 */
extern u32   func_ov025_02084d18(int nMember);                      /* Ov008_PackSlotTag */
extern void  func_ov025_020891dc(int nTracker, u32 nTag);           /* Ov008_TagTracker_Load */
extern void  func_ov025_0209cc88(u32 nTag, int nX, int nY);         /* Ov025_PlaceTaggedCell */
extern int   func_ov025_02084a7c(void);                             /* Ov008_GetCtxBlock4a7c */
extern void  func_ov025_020883f8(int nCtx, Ov008LayoutTemplate *pLayout); /* Ov008_SetLayout */
extern void  func_ov025_0208832c(int nCtx, u32 nTag, int nCount);   /* Ov008_LoadBlockProcessAndFree */
extern void  func_ov025_02088430(int nCtx, void *pCallback);        /* Ov008_SetInputDispatcher */
extern void  func_ov025_0209d4c8(void);                             /* Ov008_DispatchMenuInput */
extern void  func_ov025_02088a7c(int nCtx, int nMode);              /* Ov025_ReleaseAllListSlots */
extern void  func_ov025_0209c084(void);                             /* Ov025_Config_LoadValues */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern int   func_02023588(int nFlag);                              /* GameState_IsFlagSet */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern int   func_ov025_020afda0(int nIndex);                       /* Ov025_GetTierBase */
extern Ov008LayoutTemplate data_ov025_020b4148;
extern Ov008MenuEntryDef data_ov025_020b4f64[];                     /* the menu entry table */

void func_ov025_0209c62c(void)
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
    pTier = func_ov025_0209bf40(func_ov025_02084afc()->nTier);
    nTracker = func_ov025_02084a50();
    func_ov025_020891dc(nTracker, func_ov025_02084d18(5));
    func_ov025_0209cc88(pTier->nTag, 0, 0);
    nCtx = func_ov025_02084a7c();
    layout.words[0] = func_ov025_02084d18(4);
    func_ov025_020883f8(nCtx, &layout);
    func_ov025_0208832c(nCtx, func_ov025_02084d18(6), 0x5d);
    func_ov025_02088430(nCtx, func_ov025_0209d4c8);
    func_ov025_02088a7c(nCtx, 2);
    func_ov025_0209c084();
    bVisible = 0;
    for (i = 0; i < 5; i++) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i + 4), bVisible);
    }
    bVisible = 1;
    for (i = 0; i < pTier->nRows; i++) {
        if (i < 5) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i + 4), bVisible);
        }
    }
    if (func_02023588(0x200b) == 0) {
        nDay = func_020235d0(0, 9);
        nBase = func_ov025_020afda0(0x34);
        if (nDay < 12) {
            return;
        }
        if (func_02023588(nBase + 0x3c2b) == 0) {
            return;
        }
        data_ov025_020b4f64[0].bEnabled = 1;
        return;
    }
    data_ov025_020b4f64[0].bEnabled = 1;
}
