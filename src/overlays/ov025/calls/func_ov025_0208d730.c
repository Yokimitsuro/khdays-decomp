/* func_ov025_0208d730 -- Ov008_MainMenu_StateTick: the two opening steps of the main menu,
 * one per call of its state (+0); returns 1 once state 1 has run.  State 0 notes whether the
 * 95c0 object (02084dd8) is 2 (+0x14e0), sets up the display (0208cde0) and builds the object
 * list from data_ov025_020b3934 with kind / selector 3 / 8 for that, else 4 / the current day
 * (game-state field 9) without the 9630 object (02084e08), 3 / 7 during a page transition
 * (02084e38) and 0 / 0 otherwise -- through the retrying builder 0208d69c when the 9630 object,
 * a page transition and a current mission (02084ff0) are all set, else straight into the
 * mission list +0x13fc (0208a13c); then 0208cdc4, the tag tracker (02084a64) loads member 0x13
 * (020891dc), the sub-object (+4) is reset (0208e5a4) and told the transition direction 4 (0
 * from day 357 on; 0208eaf8, kept at +0x14ec).  State 1 runs 0208d05c / 0208d2a4 / 0208d454
 * and stamps the opening tick (+0x14d4).  The sub-object ticks every call (0208ea58). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long u64;

typedef struct Ov008MissionResourceDescriptor {
    const char *pszPath;      /* 0x00 */
    int  nSelector;           /* 0x04 */
    int  nListKind;           /* 0x08 */
} Ov008MissionResourceDescriptor;

typedef struct Ov008MissionListState {
    u8   data[0x24];
} Ov008MissionListState;

typedef struct Ov008MainMenu {
    int  nState;              /* 0x0000 */
    u8   sub[0x13fc - 4];     /* 0x0004: the sub-object ticked by 0208ea58 */
    Ov008MissionListState missionList; /* 0x13fc */
    u8   pad_1420[0x14d4 - 0x1420];
    u64  nTick;               /* 0x14d4: the tick the menu opened at */
    int  bTimerFired;         /* 0x14dc */
    int  bWireless;           /* 0x14e0: the 95c0 object is 2 */
    int  nField14e4;          /* 0x14e4 */
    int  nField14e8;          /* 0x14e8 */
    int  nDir;                /* 0x14ec: the transition direction handed to 0208eaf8 */
} Ov008MainMenu;

extern int   func_ov025_02084dd8(void);                             /* Ov008_GetCtxObject95c0 */
extern void  func_ov025_0208cde0(void);                             /* Ov008_MainMenu_SetupDisplay */
extern int   func_ov025_02084e08(void);                             /* Ov008_GetCtxObject9630 */
extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern u32   func_ov025_02084ff0(void);                             /* Ov008_GetCtxField967c: current mission id */
extern void  func_ov025_0208d69c(Ov008MainMenu *pMenu, Ov008MissionResourceDescriptor *pDescriptor); /* Ov008_MainMenu_InitObjectListRetry */
extern void  func_ov025_0208a13c(Ov008MissionListState *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov025_InitMissionList */
extern void  func_ov025_0208cdc4(Ov008MainMenu *pMenu);
extern int   func_ov025_02084a64(void);                             /* Ov008_GetCtxBlock954c: the tag tracker */
extern u32   func_ov025_02084d18(int nMember);                      /* Ov008_PackSlotTag */
extern void  func_ov025_020891dc(int nTracker, u32 nTag);           /* Ov008_TagTracker_Load */
extern void  func_ov025_0208e5a4(void *pSub, int nArg);
extern void  func_ov025_0208eaf8(void *pSub, int nDir);
extern void  func_ov025_0208d05c(Ov008MainMenu *pMenu);
extern void  func_ov025_0208d2a4(Ov008MainMenu *pMenu);
extern void  func_ov025_0208d454(Ov008MainMenu *pMenu);
extern u64   func_020031d4(void);                                   /* GetTick64 */
extern void  func_ov025_0208ea58(void *pSub);
extern const Ov008MissionResourceDescriptor data_ov025_020b3934;

int func_ov025_0208d730(Ov008MainMenu *pMenu)
{
    Ov008MissionResourceDescriptor desc;
    int bDone;
    int nTracker;
    int nDir;

    desc = data_ov025_020b3934;
    bDone = 0;
    switch (pMenu->nState) {
    case 0:
        pMenu->bWireless = func_ov025_02084dd8() == 2;
        func_ov025_0208cde0();
        if (pMenu->bWireless != 0) {
            desc.nListKind = 3;
            desc.nSelector = 8;
        } else if (func_ov025_02084e08() != 0) {
            if (func_ov025_02084e38() != 0) {
                desc.nListKind = 3;
                desc.nSelector = 7;
            } else {
                desc.nListKind = 0;
                desc.nSelector = 0;
            }
        } else {
            desc.nListKind = 4;
            desc.nSelector = func_020235d0(0, 9);
        }
        if (func_ov025_02084e08() != 0 && func_ov025_02084e38() != 0 && func_ov025_02084ff0() != 0) {
            func_ov025_0208d69c(pMenu, &desc);
        } else {
            func_ov025_0208a13c(&pMenu->missionList, &desc);
        }
        func_ov025_0208cdc4(pMenu);
        nTracker = func_ov025_02084a64();
        func_ov025_020891dc(nTracker, func_ov025_02084d18(0x13));
        nDir = 4;
        if (func_020235d0(0, 9) >= 357) {
            nDir = 0;
        }
        func_ov025_0208e5a4(pMenu->sub, 0);
        func_ov025_0208eaf8(pMenu->sub, nDir);
        pMenu->nDir = nDir;
        pMenu->nState++;
        break;
    case 1:
        func_ov025_0208d05c(pMenu);
        func_ov025_0208d2a4(pMenu);
        func_ov025_0208d454(pMenu);
        pMenu->nState++;
        pMenu->nTick = func_020031d4();
        bDone = 1;
        break;
    }
    func_ov025_0208ea58(pMenu->sub);
    return bDone;
}
