/* Ov008_DrawNumber3Shadowed -- Ov008_DrawNumber3Shadowed: draw nValue as a right-aligned
 * three-digit number ("%3d") with a 1 px drop shadow.  Blank digits (space or the
 * terminator) just advance the pen 5 px; a "1" is nudged 1 px right and advances
 * 4 px, any other digit 5 px.  Each glyph is drawn once offset by (+1, +1) in
 * colour 1 and once at the pen position in nColour.
 */

#include "nitro/types.h"

#define DIGIT_COUNT   3
#define DIGIT_ADVANCE 5
#define ONE_ADVANCE   4

extern u16 data_ov008_02090ea8[];                                       /* L"%3d" */
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...); /* Text_FormatUtf16 */
extern int Obj_ForwardInnerPayload(void *pSurface, int nX, int nY, int nColour, int nGlyph); /* Obj_ForwardInnerPayload */

void Ov008_DrawNumber3Shadowed(void *pSurface, int nValue, int nX, int nY, int nColour)
{
    u16 aDigit[4] = { 0, 0, 0, 0 };
    int i;

    Text_FormatUtf16(aDigit, 4, data_ov008_02090ea8, nValue);
    for (i = 0; i < DIGIT_COUNT; i++) {
        u16 nGlyph = aDigit[i];
        if (nGlyph != 0 && nGlyph != ' ') {
            if (nGlyph == '1') {
                nX++;
            }
            Obj_ForwardInnerPayload(pSurface, nX + 1, nY + 1, 1, nGlyph);
            Obj_ForwardInnerPayload(pSurface, nX, nY, nColour, aDigit[i]);
            nX += aDigit[i] == '1' ? ONE_ADVANCE : DIGIT_ADVANCE;
        } else {
            nX += DIGIT_ADVANCE;
        }
    }
}
