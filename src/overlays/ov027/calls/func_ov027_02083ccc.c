/* func_ov027_02083ccc -- Ov027_InitHintText: set the game-over hint text up.  The 10-pixel EU
 * font (data_ov027_02084344, "/text/font_eu_10all.nftr") is loaded into the font slot at +0x624
 * of the scene work (0202f7fc), its palette sent to the sub palette RAM at 0x1a0 (GFXi_EnqueueCommand
 * 0xf from data_02042958, 0x20 bytes), and the tile text renderer at +0x5e4 is set up on layer 2
 * with a 0x20 x 3 cell box at (0, 0x14), palette 1, spacing 0xd, kind 1 (0202f834), cleared
 * (0202fa20) and flushed (0202f9f8). */
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

typedef struct Ov027TextBox {
    u16  nX;                  /* 0x00 */
    u16  nY;                  /* 0x02 */
    u16  nWidth;              /* 0x04 */
    u16  nHeight;             /* 0x06 */
    u16  nPalette;            /* 0x08 */
    u16  nSpacing;            /* 0x0a */
    u16  nField0c;            /* 0x0c */
    u16  nKind;               /* 0x0e */
} Ov027TextBox;

extern void  func_0202f7fc(void *pFont, const char *pszPath);       /* FontResource_Load */
extern void  GFXi_EnqueueCommand(int nCmd, int nDest, const void *pSrc, int nSize);
extern void  func_0202f834(void *pText, int nLayer, void *pFont, Ov027TextBox *pBox); /* TileTextRenderer_Init */
extern void  func_0202fa20(void *pText, int nArg);                  /* TileTextRenderer_Clear */
extern void  func_0202f9f8(void *pText);                            /* TileTextRenderer_Flush */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern char  data_ov027_02084344[];                                 /* "/text/font_eu_10all.nftr" */
extern u8    data_02042958[];                                       /* the text palette */

void func_ov027_02083ccc(void)
{
    Ov027TextBox box;

    func_0202f7fc(data_ov027_02084364->font, data_ov027_02084344);
    GFXi_EnqueueCommand(0xf, 0x1a0, data_02042958, 0x20);
    box.nX = 0;
    box.nY = 0x14;
    box.nWidth = 0x20;
    box.nHeight = 3;
    box.nPalette = 1;
    box.nSpacing = 0xd;
    box.nField0c = 0;
    box.nKind = 1;
    func_0202f834(data_ov027_02084364->text, 2, data_ov027_02084364->font, &box);
    func_0202fa20(data_ov027_02084364->text, 0);
    func_0202f9f8(data_ov027_02084364->text);
}
