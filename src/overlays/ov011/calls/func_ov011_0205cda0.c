/* Ov011_DrawTitleLine -- draw one line of the scrolling title text on a pane. A line starting
 * with '>' names a logo sprite (">SQEX", ">DSN1", ">DSN2", ">HAND"): the matching sprite slot is
 * placed at (8.0, 12.0) and shown, and DSN1 also arms the pane's pending sprite drop. Any other
 * line is drawn in style 7 when coloured, 1 for plain/credit lines and 4 for headings; a line at
 * a negative y (wrapped above the buffer) goes through the second surface and its glyphs are
 * copied into the first.
 *
 * The sprite manager is bound to a local at the top of the tag branch: mwcc then computes its
 * base and index parts before the search loop, as the ROM does. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct UiLayoutPos {
    int x;
    int y;
} UiLayoutPos;

typedef struct Ov011TextCanvas {
    u8  pad_00[8];
    u8 *pChars;
} Ov011TextCanvas;

typedef struct Ov011TextSurface {
    u8               pad_00[0x18];
    Ov011TextCanvas *pCanvas;
    u8               pad_1c[4];
    const void      *pColor;
    u8               pad_24[0x3c - 0x24];
} Ov011TextSurface;

typedef struct Ov011Pane {
    void            *pBuffer;
    u8               pad_00004[0x10 - 4];
    Ov011TextSurface aSurface[2];
    u8               pad_00088[0x10908 - 0x88];
    int              aSlot[4];
    u8               pad_10918[0x1091a - 0x10918];
    u16              wPendingDrop;
    u8               pad_1091c[0x10940 - 0x1091c];
} Ov011Pane;

typedef struct Ov011SpriteManager {
    u8 data[0x4a38];
} Ov011SpriteManager;

typedef struct Ov011TextColor {
    u8 data[0xc];
} Ov011TextColor;

typedef struct Ov011Scene {
    int                nA;
    int                nMode;
    u8                 pad_00008[4];
    u32                nArchiveBase;
    u8                 pad_00010[4];
    Ov011Pane          aPane[2];
    u8                 pad_21294[0x23a94 - 0x21294];
    Ov011TextColor     aTextColor[2];
    u8                 pad_23aac[0x23ad0 - 0x23aac];
    Ov011SpriteManager aManager[2];
} Ov011Scene;

typedef struct Ov011TitleTag {
    int nSlot;
    u16 aName[4];
} Ov011TitleTag;

/* khdays: shared-bss */
u32 data_ov011_0205e960 = 0;
Ov011Scene *data_ov011_0205e964 = 0;

extern const Ov011TitleTag data_ov011_0205dca0[4];
extern const u16 data_ov011_0205dc82[];

extern void func_0203257c(Ov011SpriteManager *pManager, int nSlot, UiLayoutPos *pPos);
extern void func_02032710(Ov011SpriteManager *pManager, int nSlot, int bVisible);
extern void func_02030158(Ov011TextSurface *pSurface);
extern void func_02030278(Ov011TextSurface *pSurface, int nX, int nY, int nStyle, const u16 *pText, int nFlags);
extern void MIi_CpuCopy32(const void *pSrc, void *pDst, u32 nSize);

void func_ov011_0205cda0(const u16 *pText, int nFont, int nY, int nPane, int bTag, int nColor)
{
    Ov011Pane *pPane = &data_ov011_0205e964->aPane[nPane];
    int nStyle;

    if (*pText == 0x3e) {
        Ov011SpriteManager *pManager = &data_ov011_0205e964->aManager[nPane];
        const Ov011TitleTag *pTag = data_ov011_0205dca0;
        int i;

        for (i = 0; i < 4; i++, pTag++) {
            if (pText[1] == pTag->aName[0] && pText[2] == pTag->aName[1]
                && pText[3] == pTag->aName[2] && pText[4] == pTag->aName[3]) {
                int nSlot = data_ov011_0205dca0[i].nSlot;
                UiLayoutPos pos;

                pos.x = 0x80000;
                pos.y = 0xc0000;
                func_0203257c(pManager, pPane->aSlot[nSlot], &pos);
                func_02032710(pManager, pPane->aSlot[nSlot], 1);
                if (i == 1 && pPane->wPendingDrop == 0) {
                    pPane->wPendingDrop = 1;
                }
                return;
            }
        }
        return;
    }

    if (nColor != 0) {
        nStyle = 7;
    } else if (bTag == 0 || nFont == 2) {
        nStyle = 1;
    } else {
        nStyle = 4;
    }
    if (nY < 0) {
        func_02030158(&pPane->aSurface[1]);
        pPane->aSurface[1].pColor = &data_ov011_0205e964->aTextColor[bTag];
        func_02030278(&pPane->aSurface[1], data_ov011_0205dc82[nFont], nY + 8, nStyle, pText, 0);
        MIi_CpuCopy32(pPane->aSurface[1].pCanvas->pChars + 0x2e0, pPane->aSurface[0].pCanvas->pChars, 0x5c0);
    } else {
        pPane->aSurface[0].pColor = &data_ov011_0205e964->aTextColor[bTag];
        func_02030278(&pPane->aSurface[0], data_ov011_0205dc82[nFont], nY, nStyle, pText, 0);
    }
}
