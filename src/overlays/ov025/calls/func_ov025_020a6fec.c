/* func_ov025_020a6fec -- Ov008_ShowMissionListInfoPanel: expand (bExpand)
 * or collapse the mission list's info panel (twin of Ov008_ShowMissionInfoPanel).
 * Expanding shows entries 0x33, 0x35, 0x36, hides the cursor entry 1, resets
 * the two-slot entries 0x35 / 0x36 to frame 0, re-links 0x36, pushes subitem
 * pair 0 of 0x35, hides 0x37, shows 0x38, sets entries 2..0x13 to frame 1
 * and darkens the sub screen's blend planes (0x04001050, planes 0xf) by 8.
 * Collapsing hides 0x33, 0x35..0x38, shows entry 1, sets 2..0x13 back to
 * frame 0, restores the brightness and locks the list (+0x500).  The request is
 * remembered at +0x4f8 and the armed word (+0x4fc) cleared.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ENTRY_INFO_FIRST 2
#define ENTRY_INFO_LAST  0x13
#define ENTRY_CURSOR     1
#define BLEND_PLANES     0xf
#define REG_BLDCNT_SUB   ((void *)0x04001050)

typedef struct Ov008MissionList {
    u8  pad_000[0x4f8];
    int bSelectionPending;    /* 0x4f8 */
    int bSelectionArmed;      /* 0x4fc */
    int bLocked;           /* 0x500 */
} Ov008MissionList;

extern int   func_ov025_02084a8c(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nFrame);      /* Ov008_ReleaseTwoSlotsEx */
extern void  func_ov025_0208896c(int nCtx, void *pEntry);                  /* Ov008_SwapParamOverrides */
extern void  func_ov025_020889e4(int nCtx, void *pEntry, int nPair);       /* Ov008_PushSubitemPair */
extern void  G2x_SetBlendBrightness_(void *pReg, int nPlaneMask, int nBrightness);

void func_ov025_020a6fec(Ov008MissionList *pList, int bExpand)
{
    int nCtx;
    u16 nId;

    nCtx = func_ov025_02084a8c();
    if (bExpand != 0) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x33), 1);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x35), 1);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x36), 1);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, ENTRY_CURSOR), 0);
        func_ov025_02088928(nCtx, func_ov025_0208843c(nCtx, 0x35), 0);
        func_ov025_02088928(nCtx, func_ov025_0208843c(nCtx, 0x36), 0);
        func_ov025_0208896c(nCtx, func_ov025_0208843c(nCtx, 0x36));
        func_ov025_020889e4(nCtx, func_ov025_0208843c(nCtx, 0x35), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x37), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x38), 1);
        for (nId = ENTRY_INFO_FIRST; nId <= ENTRY_INFO_LAST; nId++) {
            func_ov025_02088928(nCtx, func_ov025_0208843c(nCtx, nId), 1);
        }
        G2x_SetBlendBrightness_(REG_BLDCNT_SUB, BLEND_PLANES, -8);
    } else {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x33), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x35), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x36), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, ENTRY_CURSOR), 1);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x37), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x38), 0);
        for (nId = ENTRY_INFO_FIRST; nId <= ENTRY_INFO_LAST; nId++) {
            func_ov025_02088928(nCtx, func_ov025_0208843c(nCtx, nId), 0);
        }
        G2x_SetBlendBrightness_(REG_BLDCNT_SUB, BLEND_PLANES, 0);
        pList->bLocked = 1;
    }
    pList->bSelectionPending = bExpand;
    pList->bSelectionArmed = 0;
}
