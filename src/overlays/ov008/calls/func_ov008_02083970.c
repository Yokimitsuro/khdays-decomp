/* func_ov008_02083970 -- Ov008_ShowThreeDigitCells: show a number (clamped to
 * 999) on three digit cells.  Shows widgets 0x1e and 0x1f of the widget group
 * (ctx+0x7530), then from the units cell (index 2) up: a digit cell is shown
 * with its digit frame (value % 10) while the value is non-zero, the units cell
 * always; leading cells with nothing left are hidden.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define VALUE_MAX 999
#define DIGIT_CELLS 3
#define WIDGET_DIGITS_A 0x1e
#define WIDGET_DIGITS_B 0x1f

extern char *data_ov008_02090fac;
extern void *func_ov008_02054788(void *pGroup, int nId);                 /* FindEntryById */
extern void func_ov008_02054ba4(void *pGroup, void *pWidget, int bVisible); /* SetEntrySlotsVisible */
extern void func_02032710(int hSlots, int nCell, int bVisible);           /* Slot_SetVisible */
extern void func_020325ec(int hSlots, int nCell, int nFrame);             /* Slot_ForwardToEntry */

void func_ov008_02083970(int hSlots, u32 nValue, int *aCell)
{
    char *pGroup = data_ov008_02090fac + 0x7530;
    int i;

    if (nValue > VALUE_MAX) {
        nValue = VALUE_MAX;
    }
    func_ov008_02054ba4(pGroup, func_ov008_02054788(pGroup, WIDGET_DIGITS_A), 1);
    func_ov008_02054ba4(pGroup, func_ov008_02054788(pGroup, WIDGET_DIGITS_B), 1);
    for (i = DIGIT_CELLS - 1; i >= 0; i--) {
        if (i != DIGIT_CELLS - 1 && nValue == 0) {
            func_02032710(hSlots, aCell[i], 0);
        } else {
            func_02032710(hSlots, aCell[i], 1);
            func_020325ec(hSlots, aCell[i], (u16)(nValue % 10));
        }
        nValue /= 10;
    }
}
