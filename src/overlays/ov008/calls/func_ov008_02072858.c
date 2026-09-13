/* func_ov008_02072858 -- Ov008_ShowMissionListWidgets: bring the mission
 * list's widgets in context block 4a80 up (the counterpart of
 * Ov008_HideMissionMenuWidgets): widget 1 is hidden while the list animates
 * (+0x68) and shown otherwise (both tests kept, as the ROM re-reads the flag),
 * the scroll bar widgets 2..0x13 are shown, the row widgets 0x16..0x20 hidden,
 * widget 2's sub-item set pushed off and 0x16's on, and the extras 0x33 and
 * 0x35..0x38 hidden.
 */
typedef unsigned char u8;

#define WIDGET_LIST      2
#define WIDGET_ROWS      0x16
#define WIDGET_BAR_LAST  0x13
#define WIDGET_ROW_LAST  0x20

typedef struct Ov008MissionList {
    u8  pad_00[0x68];
    int bAnimating;           /* 0x68 */
} Ov008MissionList;

extern int  func_ov008_02050c64(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *func_ov008_02054788(int nCtx, int nId);                     /* FindEntryById */
extern void func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */
extern void func_ov008_02054b18(int nCtx, void *pEntry, int nValue);     /* Ov008_PushSubitemSet */

void func_ov008_02072858(Ov008MissionList *pList)
{
    int nCtx;
    int i;

    nCtx = func_ov008_02050c64();
    if (pList->bAnimating != 0) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 1), 0);
    }
    if (pList->bAnimating == 0) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 1), 1);
    }
    for (i = WIDGET_LIST; i <= WIDGET_BAR_LAST; i++) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i), 1);
    }
    for (i = WIDGET_ROWS; i <= WIDGET_ROW_LAST; i++) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i), 0);
    }
    func_ov008_02054b18(nCtx, func_ov008_02054788(nCtx, WIDGET_LIST), 0);
    func_ov008_02054b18(nCtx, func_ov008_02054788(nCtx, WIDGET_ROWS), 1);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x33), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x35), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x36), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x37), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x38), 0);
}
