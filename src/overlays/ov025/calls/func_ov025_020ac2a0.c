/* func_ov025_020ac2a0 -- Ov008_ShowMissionInfoPanel: expand (bExpand) or
 * collapse the mission menu's info panel.  Expanding shows entries 0x34..0x36,
 * resets the two-slot entries 0x35 / 0x36 to frame 0, re-links 0x36, pushes
 * subitem pair 0 of 0x35, hides 0x37, shows 0x38, sets entries 0x16..0x20 to
 * frame 1 and darkens the sub screen's blend planes (0x04001050, planes
 * 0xf) by 8.  Collapsing hides 0x34..0x38, sets 0x16..0x20 back to frame 0
 * and restores the brightness.  The request is remembered at +0x180 and the
 * armed word (+0x184) cleared.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ENTRY_INFO_FIRST 0x16
#define ENTRY_INFO_LAST  0x20
#define BLEND_PLANES     0xf
#define REG_BLDCNT_SUB   ((void *)0x04001050)

typedef struct Ov008MissionMenu {
    u8  pad_000[0x180];
    int bSelectionPending;    /* 0x180 */
    int bSelectionArmed;      /* 0x184 */
} Ov008MissionMenu;

extern int   func_ov025_02084a8c(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nFrame);      /* Ov008_ReleaseTwoSlotsEx */
extern void  func_ov025_0208896c(int nCtx, void *pEntry);                  /* Ov008_SwapParamOverrides */
extern void  func_ov025_020889e4(int nCtx, void *pEntry, int nPair);       /* Ov008_PushSubitemPair */
extern void  G2x_SetBlendBrightness_(void *pReg, int nPlaneMask, int nBrightness);

void func_ov025_020ac2a0(Ov008MissionMenu *pMenu, int bExpand)
{
    int nCtx;
    u16 nId;

    nCtx = func_ov025_02084a8c();
    if (bExpand != 0) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x34), 1);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x35), 1);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x36), 1);
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
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x34), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x35), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x36), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x37), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x38), 0);
        for (nId = ENTRY_INFO_FIRST; nId <= ENTRY_INFO_LAST; nId++) {
            func_ov025_02088928(nCtx, func_ov025_0208843c(nCtx, nId), 0);
        }
        G2x_SetBlendBrightness_(REG_BLDCNT_SUB, BLEND_PLANES, 0);
    }
    pMenu->bSelectionPending = bExpand;
    pMenu->bSelectionArmed = 0;
}
