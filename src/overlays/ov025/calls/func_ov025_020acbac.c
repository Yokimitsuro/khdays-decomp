/* func_ov025_020acbac -- Ov008_HideMissionMenuWidgets: hide the mission
 * menu's widgets in context block 4a80: pushes widget 2's sub-item set on and
 * 0x16's off, hides widget 1 (twice, as the ROM does), the scroll bar widgets
 * 2..0x13, the row widgets 0x16..0x20 and the five extras 0x34..0x38.
 */
#define WIDGET_LIST      2
#define WIDGET_ROWS      0x16
#define WIDGET_BAR_LAST  0x13
#define WIDGET_ROW_LAST  0x20

extern int  func_ov025_02084a8c(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                     /* FindEntryById */
extern void func_ov025_020887c0(int nCtx, void *pEntry, int nValue);     /* Ov008_PushSubitemSet */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */

void func_ov025_020acbac(void)
{
    int nCtx;
    int i;

    nCtx = func_ov025_02084a8c();
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, WIDGET_LIST), 1);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, WIDGET_ROWS), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 1), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 1), 0);
    for (i = WIDGET_LIST; i <= WIDGET_BAR_LAST; i++) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), 0);
    }
    for (i = WIDGET_ROWS; i <= WIDGET_ROW_LAST; i++) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), 0);
    }
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x34), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x35), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x36), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x37), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x38), 0);
}
