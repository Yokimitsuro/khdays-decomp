/* func_ov027_02083a80 -- Ov027_LayoutChoicePanel: lay out the game-over menu with its yes / no
 * prompt.  The panel's background screen (+0x564 of the scene work: cells at +0xc, size at +8) is
 * cleared (MIi_CpuClearFast), the blink phase of every slot is lit only under the cursor
 * (+0x5d8), and the strips are placed at column 8 (Ov027_SetPanelSlot 02083c1c): line 0 from
 * source row 0 at row 15 (row 14 for a client, bit 1 of data_0204c240, or below room 10000);
 * the prompt line (slot 1, source column 15) at row 16 when the retry prompt (+0x5e0) is on,
 * which pushes the quit line down to row 18 -- a client without the prompt lifts it to row 15;
 * the quit line (slot 2, source row 3) only below room 10000. */
typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov027ScreenBlock {
    u16  nWidth;              /* 0x00: in cells */
    u16  nHeight;             /* 0x02 */
    u8   pad_04[4];
    u32  nSize;               /* 0x08: bytes of cells */
    u8   aData[4];            /* 0x0c: the cells */
} Ov027ScreenBlock;

typedef struct Ov027BgSet {
    Ov027ScreenBlock *pScreen; /* 0x00 */
    void *pChar;              /* 0x04 */
    void *pPalette;           /* 0x08 */
} Ov027BgSet;

typedef struct Ov027PanelSlot {
    int  nSrcX;               /* 0x00: in cells of the strip block */
    int  nSrcY;               /* 0x04 */
    int  nDstX;               /* 0x08: in cells of the screen */
    int  nDstY;               /* 0x0c */
    int  nWidth;              /* 0x10 */
    int  nHeight;             /* 0x14 */
} Ov027PanelSlot;

typedef struct Ov027Panel {
    void *pBlock;             /* 0x00: the unpacked menu strips */
    void *pData;              /* 0x04: their cells */
    Ov027PanelSlot aSlot[3];  /* 0x08: line 0, the prompt line, line 1 */
    void *pFile;              /* 0x50: the background file */
    Ov027BgSet set;           /* 0x54: its screen / character / palette */
} Ov027Panel;                 /* 0x60 */

typedef struct Ov027SignInPanel {
    void *pIconBlock;         /* 0x00 */
    void *pBgFile;            /* 0x04 */
    void *pIconData;          /* 0x08 */
    Ov027BgSet set;           /* 0x0c */
} Ov027SignInPanel;           /* 0x18 */

typedef struct Ov027Blink {
    int  nTimer;              /* 0x00 */
    int  nPhase;              /* 0x04: 0 dark, 1 / 2 the two lit strips */
} Ov027Blink;

typedef struct Ov027Model {
    u8   pad_000[0xa4];
    VecFx32 vPos;             /* 0x0a4 */
    u8   pad_0b0[0x108 - 0xb0];
} Ov027Model;                 /* 0x108 */

typedef struct Ov027AnimSlot {
    int  aField[3];           /* 0x00 */
    int  nHandle;             /* 0x0c */
    int  aField10[5];         /* 0x10 */
} Ov027AnimSlot;              /* 0x24 */

typedef struct Ov027Camera {
    int  nNear;               /* 0x00 */
    int  nFar;                /* 0x04 */
    u8   pad_08[0x18 - 0x8];
    int  nAngle;              /* 0x18 */
    u8   pad_1c[0x24 - 0x1c];
    int  nAngleTarget;        /* 0x24 */
    int  nDistance;           /* 0x28 */
    u8   pad_2c[0x38 - 0x2c];
} Ov027Camera;                /* 0x38 */

typedef struct Ov027Object {
    u8   pad_00[0x10];
    Fx32Pair vPos;            /* 0x10 */
    Fx32Pair vScale;          /* 0x18 */
    u8   pad_20[4];
    u8   nDepth;              /* 0x24 */
    u8   pad_25[5];
    u8   nAlpha;              /* 0x2a: bits 0-4 */
    u8   pad_2b[5];
    u16  wFlags;              /* 0x30: bit 1 = steer toward the target */
    u8   pad_32[2];
    int  nPhase;              /* 0x34: the float orbit phase */
    int  nSlot;               /* 0x38: the placement slot */
    Fx32Pair vStep;           /* 0x3c */
    u8   pad_44[4];
} Ov027Object;                /* 0x48: an ov002 display object */

typedef struct Ov027Scene {
    Ov027SignInPanel signIn;  /* 0x000: the session sign-in panel */
    void *pArchive;           /* 0x018: the "/gameover/data" archive */
    int  nFlags;              /* 0x01c: bit 0 = still loading, bit 3 = busy */
    int  nBrightness;         /* 0x020 */
    int  nMode;               /* 0x024: 1 menu, 2 retry, 4 quit; bit 4 = choice prompt up */
    Ov027Model aModel[4];     /* 0x028: the fallen characters */
    Ov027AnimSlot aAnimSlot[4]; /* 0x448 */
    Ov027Camera camera;       /* 0x4d8 */
    Ov027Panel panel;         /* 0x510: the menu panel */
    Ov027Blink aBlink[3];     /* 0x570: per panel slot */
    Ov027Object character;    /* 0x588: the floating character sprite */
    int  nModels;             /* 0x5d0 */
    int  nSlots;              /* 0x5d4: 2 without the prompt line, 3 with it */
    int  nCursor;             /* 0x5d8 */
    int  nSwapTimer;          /* 0x5dc */
    int  bPrompt;             /* 0x5e0: the retry prompt line is shown */
    u8   text[0x40];          /* 0x5e4: the tile text renderer */
    u8   font[0xc];           /* 0x624 */
} Ov027Scene;                 /* 0x630 */

typedef struct Ov027SessionInfo {
    u8   nBits;               /* 0x00: bit 1 = client, bit 2 = wireless session */
    u8   pad_01;
    u16  nRoom;               /* 0x02: the room number */
} Ov027SessionInfo;

extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void  func_ov027_02083c1c(Ov027Panel *pPanel, int nSlot, int nSrcX, int nSrcRow,
                                 int nDstX, int nDstY, int nWidth, int nHeight); /* Ov027_SetPanelSlot */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern Ov027SessionInfo data_0204c240;                              /* session bits */

void func_ov027_02083a80(void)
{
    int nQuitRow = 0x10;
    Ov027ScreenBlock *pScreen;
    int i;
    int nFirstRow;

    pScreen = data_ov027_02084364->panel.set.pScreen;
    MIi_CpuClearFast(0, pScreen->aData, pScreen->nSize);
    for (i = 0; i < data_ov027_02084364->nSlots; i++) {
        if (i == data_ov027_02084364->nCursor) {
            data_ov027_02084364->aBlink[i].nPhase = 1;
        } else {
            data_ov027_02084364->aBlink[i].nPhase = 0;
        }
    }
    if (!(data_0204c240.nBits & 2)) {
        if (data_0204c240.nRoom >= 10000) {
            nFirstRow = 0xf;
        } else {
            nFirstRow = 0xe;
        }
        func_ov027_02083c1c(&data_ov027_02084364->panel, 0, 0, 0, 8, nFirstRow, 0xf, 2);
    }
    if (data_ov027_02084364->bPrompt != 0) {
        func_ov027_02083c1c(&data_ov027_02084364->panel, 1, 0xf, 0, 8, 0x10, 0xf, 2);
        nQuitRow = 0x12;
    } else if (data_0204c240.nBits & 2) {
        nQuitRow = 0xf;
    }
    if (data_0204c240.nRoom < 10000) {
        func_ov027_02083c1c(&data_ov027_02084364->panel, 2, 0, 3, 8, nQuitRow, 0xf, 2);
    }
}
