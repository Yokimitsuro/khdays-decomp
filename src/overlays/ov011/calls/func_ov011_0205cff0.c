/* Ov011_ScrollTitleText -- draw the next line of a pane's scrolling title text once the
 * background has scrolled far enough: count the pane's distance down by the per-frame scroll,
 * and when it runs out clear the line band on the text surface (wrapping at the bottom of the
 * 256-line buffer), draw the script line (twice when it straddles the wrap), reload the distance
 * from the line height, and upload the surface.
 *
 * Structure follows the ROM's block order (the pText == NULL height and the in-range draw are the
 * fall-through cases); the declaration order below is what puts bTag/nColor in r6/r7 so both
 * stack arguments go out with one stm. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011TitleLine {
    u8         nFont;
    u8         nColor;
    u8         pad_02[2];
    const u16 *pText;
} Ov011TitleLine;

typedef struct Ov011TitleScript {
    int            nCount;
    Ov011TitleLine aLine[1];
} Ov011TitleScript;

typedef struct Ov011Pane {
    void *pBuffer;
    u8    pad_00004[0x10 - 4];
    u8    surface[0x88 - 0x10];
    u8    aText[0x800];
    u8    pad_00888[0x10938 - 0x888];
    int   nLineDistance;
    int   nLine;
} Ov011Pane;

typedef struct Ov011Scene {
    int               nA;
    int               nMode;
    u8                pad_00008[4];
    u32               nArchiveBase;
    u8                pad_00010[4];
    Ov011Pane         aPane[2];
    u8                pad_21294[0x23aac - 0x21294];
    int               nBgScroll;
    int               nPrevBgScroll;
    u8                pad_23ab4[0x2cf44 - 0x23ab4];
    Ov011TitleScript *pScript;
} Ov011Scene;

/* khdays: shared-bss */
u32 data_ov011_0205e960 = 0;
Ov011Scene *data_ov011_0205e964 = 0;

extern void func_0203011c(void *pSurface, int nX, int nY, int nWidth, int nHeight);
extern int  func_ov011_0205cfa8(const u16 *pText, int nFont);
extern void func_ov011_0205cda0(const u16 *pText, int nFont, int nY, int nPane, int bTag, int nColor);
extern void func_020300f8(void *pSurface);
extern void GFXi_EnqueueCommand(int nType, int nOffset, const void *pSrc, u32 nSize);

void func_ov011_0205cff0(int nPane)
{
    Ov011Pane *pPane = &data_ov011_0205e964->aPane[nPane];
    Ov011TitleScript *pScript = data_ov011_0205e964->pScript;
    Ov011TitleLine *aLine = pScript->aLine;
    int nBottom = data_ov011_0205e964->nBgScroll / 100 + 0xd0;
    const u16 *pText;
    int nFont;
    int bTag;
    int nColor;
    int nY;
    int nHeight;

    if (nBottom < 0) {
        return;
    }
    if (pPane->nLine == pScript->nCount) {
        return;
    }
    pPane->nLineDistance -= 0x94;
    nY = (u8)(nBottom - (data_ov011_0205e964->nBgScroll / 100 - data_ov011_0205e964->nPrevBgScroll / 100) - 1);
    if (pPane->nLineDistance > 0) {
        return;
    }
    nFont = aLine[pPane->nLine].nFont;
    pText = aLine[pPane->nLine].pText;
    nColor = aLine[pPane->nLine].nColor;
    if (nY <= 0xf1) {
        func_0203011c(pPane->surface, 0, nY, 0xb8, 0xf);
    } else {
        int nFirst = 0x100 - nY;

        func_0203011c(pPane->surface, 0, nY, 0xb8, nFirst);
        func_0203011c(pPane->surface, 0, 0, 0xb8, 0xf - nFirst);
    }
    bTag = func_ov011_0205cfa8(pText, nFont);
    if (pText != 0) {
        if (bTag) {
            nHeight = 0xb;
        } else {
            nHeight = 0xe;
        }
    } else {
        nHeight = 8;
    }
    if (nY <= 0x100 - nHeight) {
        if (pText != 0) {
            func_ov011_0205cda0(pText, nFont, nY, nPane, bTag, nColor);
        }
    } else {
        int nFirst = 0x100 - nY;

        if (pText != 0) {
            func_ov011_0205cda0(pText, nFont, nY, nPane, bTag, nColor);
            if (*pText != 0x3e) {
                func_ov011_0205cda0(pText, nFont, -nFirst, nPane, bTag, nColor);
            }
        }
    }
    pPane->nLineDistance += nHeight * 100;
    pPane->nLine++;
    func_020300f8(pPane->surface);
    GFXi_EnqueueCommand(nPane == 0 ? 9 : 0x19, 0, pPane->aText, 0x800);
}
