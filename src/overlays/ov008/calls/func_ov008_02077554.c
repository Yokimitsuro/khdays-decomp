/* func_ov008_02077554 -- Ov008_HideMissionMenuWidgets: hide the mission
 * menu's widgets in context block 4a80: pushes widget 2's sub-item set on and
 * 0x16's off, hides widget 1 (twice, as the ROM does), the scroll bar widgets
 * 2..0x13, the row widgets 0x16..0x20 and the five extras 0x34..0x38.
 */
#define WIDGET_LIST      2
#define WIDGET_ROWS      0x16
#define WIDGET_BAR_LAST  0x13
#define WIDGET_ROW_LAST  0x20

extern int  func_ov008_02050c64(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *func_ov008_02054788(int nCtx, int nId);                     /* FindEntryById */
extern void func_ov008_02054b18(int nCtx, void *pEntry, int nValue);     /* Ov008_PushSubitemSet */
extern void func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */

void func_ov008_02077554(void)
{
    int nCtx;
    int i;

    nCtx = func_ov008_02050c64();
    func_ov008_02054b18(nCtx, func_ov008_02054788(nCtx, WIDGET_LIST), 1);
    func_ov008_02054b18(nCtx, func_ov008_02054788(nCtx, WIDGET_ROWS), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 1), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 1), 0);
    for (i = WIDGET_LIST; i <= WIDGET_BAR_LAST; i++) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i), 0);
    }
    for (i = WIDGET_ROWS; i <= WIDGET_ROW_LAST; i++) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i), 0);
    }
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x34), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x35), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x36), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x37), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x38), 0);
}
