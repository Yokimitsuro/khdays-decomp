/* func_ov008_02075f70 -- Ov008_DrawMissionInfoText: draw the mission menu's
 * info panel text.  Binds the panel surface (+0xc) to its target (+0x140),
 * sets mode 6 (+0x34) and refreshes the surface.  During a page transition
 * (02051028) it draws a single message from the menu's variable records
 * (+0x530): with the transfer flag (+0x150) clear, record 0x20 with the shadow
 * drawer; otherwise record 0x24 for mission 10, 0x25 for mission 0x6c, 0x21 for
 * any other, through the sub-1c drawer with colour 0xfb.  Either way the
 * measured text width goes to +0x14c.  Outside a transition it redraws the
 * mission rows (020759c4) and the 13 row captions (02075f00) after clearing
 * the width.  The text pick is a switch with case 0x6c written before case 10
 * so its body falls straight out of the compare chain, as in the ROM.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define ROW_COUNT       13
#define MODE_INFO       6
#define TEXT_TRANSFER   0x20
#define TEXT_MISSION_10 0x24
#define TEXT_MISSION_6C 0x25
#define TEXT_OTHER      0x21
#define MISSION_10      10
#define MISSION_6C      0x6c

typedef struct Ov008MissionMenu {
    u8  pad_000[0xc];
    u8  surface[0x34 - 0xc];  /* 0x00c */
    int nMode;                /* 0x034 */
    u8  pad_038[0x140 - 0x38];
    int nTarget;              /* 0x140 */
    u8  pad_144[8];
    int nTextWidth;           /* 0x14c */
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x530 - 0x154];
    u8  records[4];           /* 0x530: variable text records */
} Ov008MissionMenu;

extern void  func_02030094(void *pSurface, int nTarget, int nUpdate);        /* TileSurface_SetCurrentItem */
extern void  func_02030158(void *pSurface);                                  /* Obj_InvokeInnerVtable4 */
extern int   func_ov008_02051028(void);                                      /* page transition active */
extern void *func_ov008_02055c84(void *pRecords, int nIndex);                /* GetVarRecordByIndex */
extern void  func_02030278(void *pSurface, int nX, int nY, int nColour, void *pText, int nFlag); /* Text_DrawWithShadow */
extern void  func_020302ec(void *pSurface, int nX, int nY, int nColour, int nShade, void *pText); /* Obj_ForwardToSub1c */
extern int   func_ov008_02074b10(void *pText);                               /* text width */
extern void  func_ov008_020759c4(Ov008MissionMenu *pMenu, u16 *pMissionId);  /* draw the mission rows */
extern void  func_ov008_02075f00(Ov008MissionMenu *pMenu, int nRow);         /* draw one row caption */

void func_ov008_02075f70(Ov008MissionMenu *pMenu, u16 *pMissionId)
{
    void *pText;
    int nText;
    u16 i;

    func_02030094(pMenu->surface, pMenu->nTarget, 0);
    pMenu->nMode = MODE_INFO;
    func_02030158(pMenu->surface);
    if (func_ov008_02051028() != 0) {
        if (pMenu->bTransfer == 0) {
            pText = func_ov008_02055c84(pMenu->records, TEXT_TRANSFER);
            func_02030278(pMenu->surface, 3, 3, 0xf5, pText, 1);
            pMenu->nTextWidth = func_ov008_02074b10(pText);
        } else {
            switch (*pMissionId) {
            case MISSION_6C:
                nText = TEXT_MISSION_6C;
                break;
            case MISSION_10:
                nText = TEXT_MISSION_10;
                break;
            default:
                nText = TEXT_OTHER;
                break;
            }
            pText = func_ov008_02055c84(pMenu->records, nText);
            func_020302ec(pMenu->surface, 3, 3, 0xf5, 0xfb, pText);
            pMenu->nTextWidth = func_ov008_02074b10(pText);
        }
    } else {
        func_ov008_020759c4(pMenu, pMissionId);
        pMenu->nTextWidth = 0;
        for (i = 0; i < ROW_COUNT; i++) {
            func_ov008_02075f00(pMenu, i);
        }
    }
}
