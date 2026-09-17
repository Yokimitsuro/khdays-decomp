/* func_ov025_020b02b8 -- Ov025_ReportDetail_DrawWrappedText: draw a report's text on the detail
 * view of page B (Ov025_GetPageB 02084b14) line by line.  The characters are gathered into a
 * 256-character line until a line feed (code 10) or the line is full; each finished line is drawn
 * shaded at (nX, nY) in nColour with shade nColour + 2 (020302ec) and nY steps 16 pixels.  The
 * style codes 2 (open) and 1 (close) are tracked so that a line broken inside a styled run is
 * closed with a 1 and the next one reopened with a 2.  The fourth argument is not used.
 * Codegen: the text pointer is copied to a local AFTER the page call (the ROM loads the stack
 * argument late, into r7) and declared before the style flag (r8); the line-full test is the
 * `if` with the plain store as its else; the reopened line starts with `*pDst++ = 2` (the
 * hoisted `aLine + 1` spilled at sp+0xc). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov025ReportDetailPage {
    int  nField00;            /* 0x00 */
    u8   surface[0x3c];       /* 0x04: the text surface (TileSurface) */
} Ov025ReportDetailPage;

extern Ov025ReportDetailPage *func_ov025_02084b14(void);            /* Ov025_GetPageB */
extern void  func_020302ec(void *pSurface, int nX, int nY, int nColour, int nShade, const u16 *pText); /* Text_DrawShaded */
void func_ov025_020b02b8(int nX, int nY, int nColour, int nUnused, const u16 *pText)
{
    Ov025ReportDetailPage *pPage;
    u16 *pDst;
    const u16 *pSrc;
    int bStyleOpen;
    u16 aLine[0x100];

    pPage = func_ov025_02084b14();
    pDst = aLine;
    bStyleOpen = 0;
    pSrc = pText;
    if (*pSrc != 0) {
        do {
            u16 c = *pSrc;
            if (c == 1) {
                bStyleOpen = 0;
            } else if (c == 2) {
                bStyleOpen = 1;
            }
            if (c == 10 || pDst == &aLine[0xff]) {
                if (bStyleOpen) {
                    *pDst++ = 1;
                }
                *pDst = 0;
                if (aLine[0] != 0) {
                    func_020302ec(pPage->surface, nX, nY, nColour, nColour + 2, aLine);
                }
                pDst = aLine;
                if (bStyleOpen) {
                    *pDst++ = 2;
                }
                nY += 0x10;
            } else {
                *pDst++ = c;
            }
            pSrc++;
        } while (*pSrc != 0);
    }
    *pDst = 0;
    if (aLine[0] != 0) {
        func_020302ec(pPage->surface, nX, nY, nColour, nColour + 2, aLine);
    }
}
