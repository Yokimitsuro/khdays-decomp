/* func_ov027_02083834 -- Ov027_PollChoice: read the yes / no prompt of the game-over panel.  The
 * choice cursor (the scene's static word data_ov027_02083ee0) moves with the pad
 * (Ov027_MoveCursor 0208360c); A (bit 0 of data_0204c190) confirms it and B (bit 1) forces "no"
 * (1) first.  "Yes" (0) plays sound 0 / 1, resets the choice to 1 and drops bit 4 of the mode
 * word (+0x24 of the scene work).  "No" plays sound 0 / 3 and sets mode 1; with the panel
 * cursor (+0x5d8) on the hidden middle slot of a promptless panel (+0x5e0) the highlight
 * (+0x5c0) becomes 1, otherwise the cursor.  Every frame the choice slot is either queued
 * (Ov027_EnqueuePanel 02083cb8) while its blink phase (+0x574) is 0 or blinked
 * (Ov027_BlinkPanelSlot 02083918). */
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

extern void  func_ov027_0208360c(int *pCursor);                     /* Ov027_MoveCursor */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern void  func_ov027_02083cb8(Ov027Panel *pPanel);              /* Ov027_EnqueuePanel */
extern void  func_ov027_02083918(int nSlot);                        /* Ov027_BlinkPanelSlot */
/* khdays: shared-data */
int data_ov027_02083ee0 = 1;                                        /* the choice cursor: 1 = no */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern u16   data_0204c190;                                         /* the keys pressed this frame */

void func_ov027_02083834(void)
{
    int nCursor;
    Ov027Scene *pScene;

    func_ov027_0208360c(&data_ov027_02083ee0);
    if ((data_0204c190 & 1) || (data_0204c190 & 2)) {
        if (data_0204c190 & 2) {
            data_ov027_02083ee0 = 1;
        }
        switch (data_ov027_02083ee0) {
        case 0:
            func_02033b78(0, 1);
            data_ov027_02083ee0 = 1;
            data_ov027_02084364->nMode &= ~0x10;
            break;
        case 1:
            func_02033b78(0, 3);
            data_ov027_02084364->nMode = 1;
            pScene = data_ov027_02084364;
            nCursor = pScene->nCursor;
            if (nCursor == 2 && pScene->bPrompt == 0) {
                pScene->character.nSlot = 1;
            } else {
                pScene->character.nSlot = nCursor;
            }
            break;
        }
    }
    if (data_ov027_02084364->aBlink[data_ov027_02083ee0].nPhase != 0) {
        func_ov027_02083918(data_ov027_02083ee0);
    } else {
        func_ov027_02083cb8(&data_ov027_02084364->panel);
    }
}
