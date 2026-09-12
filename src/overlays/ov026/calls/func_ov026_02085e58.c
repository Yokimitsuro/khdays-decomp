/* func_ov026_02085e58 -- Ov008_DrawDescriptionText: draw a description string on
 * the panel's text surface (+0xc160, region (0, 0xa0, 0x100 x 0x20) cleared
 * first) from (8, 0xa4).  Code unit 1 selects colour 4, 2 colour 2; any other
 * glyph is drawn once with a (+1, +1) colour-1 shadow and once in the current
 * colour, advancing the pen by the returned width.  A newline (10) is skipped
 * and returns the pen to x 8 on the next 15-px line.  Widget 0x3f of the
 * widget group is shown with frame nIcon when nIcon is below 0x3f, hidden
 * otherwise.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TEXT_X0   8
#define TEXT_Y0   0xa4
#define LINE_STEP 15
#define WIDGET_ICON 0x3f
#define ICON_NONE   0x3f

extern char *data_ov026_02091368;
extern void func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8 */
extern int  func_02030194(void *pSurface, int nX, int nY, int nColour, int nGlyph); /* Obj_ForwardInnerPayload */
extern void *func_ov026_0208427c(void *pGroup, int nId);              /* FindEntryById */
extern void func_ov026_020843e8(void *pGroup, void *pWidget, int bVisible); /* SetEntrySlotsVisible */
extern void func_ov026_02084488(void *pGroup, void *pWidget, int nFrame);   /* Ov008_ReleaseTwoSlotsEx */

void func_ov026_02085e58(u16 *pText, u32 nIcon)
{
    char *ctx = data_ov026_02091368;
    u8 (*pSurface)[0xc000];
    u8 (*pGroup)[0x2000];
    int nY;
    int nX;
    int nColour;
    void *pWidget;

    pSurface = (u8 (*)[0xc000])(ctx + 0x160);
    pGroup = (u8 (*)[0x2000])(ctx + 0xab0);
    nColour = 4;
    func_0203011c(pSurface + 1, 0, 0xa0, 0x100, 0x20);
    nY = TEXT_Y0;
    nX = TEXT_X0;
    while (*pText != 0) {
        u16 c = *(volatile u16 *)pText;   /* the ROM re-reads the code unit (precedent 020681b0) */
        switch (c) {
        case 1:
            nColour = 4;
            break;
        case 2:
            nColour = 2;
            break;
        default:
            func_02030194(pSurface + 1, nX + 1, nY + 1, 1, c);
            nX += func_02030194(pSurface + 1, nX, nY, nColour, *pText);
            break;
        }
        pText++;
        if (*pText == 10) {
            pText++;
            nX = TEXT_X0;
            nY += LINE_STEP;
        }
    }
    pWidget = func_ov026_0208427c(pGroup + 1, WIDGET_ICON);
    func_ov026_020843e8(pGroup + 1, pWidget, nIcon < ICON_NONE);
    if (nIcon < ICON_NONE) {
        func_ov026_02084488(pGroup + 1, pWidget, (u16)nIcon);
    }
}
