/* func_ov008_0206a1a8 -- Ov008_FitTextFieldFont: pick the glyph set for a text field
 * from the widest of its lines.  Resets the field to the narrow set, measures every
 * line (func_02013768 hands back the rest of the text after each line), and picks
 * the wide set when the widest line exceeds nMaxWidth; a changed set is written to
 * the field's head and cursor.  Returns 1 when the wide set was chosen.  Nothing
 * (and no return value) for a null field or text.
 */
typedef struct Ov008TextField {
    int nGlyphSet;        /* 0x00: head */
    int pad_04[7];
    int nCursorSet;       /* 0x20: cursor */
    int nLength;          /* 0x24 */
} Ov008TextField;

extern void func_ov008_0206a190(Ov008TextField *pField);            /* reset to the narrow set */
extern int func_02013768(int nSet, int nLength, char *pText, char **ppRest); /* Text_MeasureLineWidth */
extern int func_ov008_02050ea4(void);                                /* wide glyph set */
extern int func_ov008_02050e74(void);                                /* narrow glyph set */

int func_ov008_0206a1a8(Ov008TextField *pField, char *pText, int nMaxWidth)
{
    char *pRest = 0;
    int nWidest;
    int nWidth;
    int nSet;
    int bWide;

    if (pField != 0 && pText != 0) {
        func_ov008_0206a190(pField);
        nWidest = 0;
        do {
            nWidth = func_02013768(pField->nCursorSet, pField->nLength, pText, &pRest);
            if (nWidth > nWidest) {
                nWidest = nWidth;
            }
            pText = pRest;
        } while (pRest != 0);
        if (nWidest > nMaxWidth) {
            nSet = func_ov008_02050ea4();
            bWide = 1;
        } else {
            nSet = func_ov008_02050e74();
            bWide = 0;
        }
        if (nSet != pField->nGlyphSet) {
            pField->nGlyphSet = nSet;
            pField->nCursorSet = nSet;
        }
        return bWide;
    }
}
