/* func_ov008_02083248 -- Ov008_ShowEightDigitCells: show a number (clamped to
 * 999999) on eight digit cells, most significant first, with a divisor that
 * starts at 10,000,000 and drops by ten per cell.  With bShow clear every cell
 * is hidden.  Leading zeros are hidden until the first non-zero digit (the last
 * cell is always shown); each shown cell gets its digit frame.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define VALUE_MAX   999999
#define CELL_COUNT  8
#define FIRST_DIVISOR 10000000

extern char *data_ov008_02090fac;
extern u32  func_0202060c(u32 nNum, u32 nDen);                          /* Math_DivMod (quotient) */
extern void func_02032710(int hSlots, int nCell, int bVisible);          /* Slot_SetVisible */
extern void func_020325ec(int hSlots, int nCell, int nFrame);            /* Slot_ForwardToEntry */

void func_ov008_02083248(u32 nValue, int *aCell, int bShow)
{
    int hSlots;
    int i;
    u32 nDigit;
    u32 nDivisor;
    int bLeading;

    hSlots = *(int *)(data_ov008_02090fac + 0xbfb4);
    bLeading = 1;
    nDivisor = FIRST_DIVISOR;
    if (nValue > VALUE_MAX) {
        nValue = VALUE_MAX;
    }
    for (i = 0; i < CELL_COUNT; i++) {
        if (bShow == 0) {
            func_02032710(hSlots, aCell[i], 0);
        } else {
            nDigit = func_0202060c(nValue, nDivisor);
            if (bLeading) {
                if (i < CELL_COUNT - 1 && nDigit == 0) {
                    func_02032710(hSlots, aCell[i], 0);
                } else {
                    bLeading = 0;
                    func_02032710(hSlots, aCell[i], 1);
                    func_020325ec(hSlots, aCell[i], (u16)nDigit);
                }
            } else {
                func_02032710(hSlots, aCell[i], 1);
                func_020325ec(hSlots, aCell[i], (u16)nDigit);
            }
            nValue -= nDigit * nDivisor;
            nDivisor /= 10;
        }
    }
}
