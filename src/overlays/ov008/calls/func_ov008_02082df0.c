/* func_ov008_02082df0 -- Ov008_DrawNumber3Shadowed: draw nValue as a right-aligned
 * three-digit number ("%3d") with a 1 px drop shadow.  Blank digits (space or the
 * terminator) just advance the pen 5 px; a "1" is nudged 1 px right and advances
 * 4 px, any other digit 5 px.  Each glyph is drawn once offset by (+1, +1) in
 * colour 1 and once at the pen position in nColour.
 */
typedef unsigned short u16;

#define DIGIT_COUNT   3
#define DIGIT_ADVANCE 5
#define ONE_ADVANCE   4

extern u16 data_ov008_02090ea8[];                                       /* L"%3d" */
extern void func_020262a0(u16 *pDst, int nCount, const void *pFmt, ...); /* Text_FormatUtf16 */
extern int func_02030194(void *pSurface, int nX, int nY, int nColour, int nGlyph); /* Obj_ForwardInnerPayload */

void func_ov008_02082df0(void *pSurface, int nValue, int nX, int nY, int nColour)
{
    u16 aDigit[4] = { 0, 0, 0, 0 };
    int i;

    func_020262a0(aDigit, 4, data_ov008_02090ea8, nValue);
    for (i = 0; i < DIGIT_COUNT; i++) {
        u16 nGlyph = aDigit[i];
        if (nGlyph != 0 && nGlyph != ' ') {
            if (nGlyph == '1') {
                nX++;
            }
            func_02030194(pSurface, nX + 1, nY + 1, 1, nGlyph);
            func_02030194(pSurface, nX, nY, nColour, aDigit[i]);
            nX += aDigit[i] == '1' ? ONE_ADVANCE : DIGIT_ADVANCE;
        } else {
            nX += DIGIT_ADVANCE;
        }
    }
}
