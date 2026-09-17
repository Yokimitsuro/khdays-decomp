/* func_ov027_0208360c -- Ov027_MoveCursor: move the game-over panel's cursor with the pad.
 * Outside a client session (bit 1 of data_0204c240) and below room 10000 (data_0204c240 + 2),
 * up (bit 7 of the pressed keys data_0204c190) or down (bit 6) plays sound 0 / 0, clears the
 * old slot's blink phase (+0x574 of the scene work, 8 bytes a slot), steps the cursor and skips
 * the hidden middle slot of a three-slot panel (+0x5d4) without the prompt (+0x5e0), wrapping
 * at both ends.  Then bit 1 of the panel word (+0x5b8) is set, the selection (+0x5c0) becomes
 * the cursor -- 1 for the hidden middle case -- the new slot's blink phase is 1 with its timer
 * (+0x570) reset, and every slot is redrawn shifted by its phase (Ov027_DrawPanelSlotShifted
 * 02083c78). */
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

extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern void  func_ov027_02083c78(Ov027Panel *pPanel, int nSlot, int nShift); /* Ov027_DrawPanelSlotShifted */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern Ov027SessionInfo data_0204c240;                                 /* session bits */
extern u16   data_0204c190;                                         /* the keys pressed this frame */

void func_ov027_0208360c(int *pCursor)
{
    Ov027Scene *pScene;
    int nStep;
    int i;
    int nSlots;

    if (!(data_0204c240.nBits & 2)) {
        if (data_0204c240.nRoom < 10000) {
            if ((data_0204c190 & 0x80) || (data_0204c190 & 0x40)) {
                func_02033b78(0, 0);
                data_ov027_02084364->aBlink[*pCursor].nPhase = 0;
                if (data_0204c190 & 0x80) {
                    nStep = 1;
                } else {
                    nStep = -1;
                }
                *pCursor += nStep;
                pScene = data_ov027_02084364;
                nSlots = pScene->nSlots;
                if (nSlots == 3 && *pCursor == 1 && pScene->bPrompt == 0) {
                    *pCursor += nStep;
                } else if (*pCursor >= nSlots) {
                    *pCursor = 0;
                } else if (*pCursor < 0) {
                    *pCursor = nSlots - 1;
                }
                data_ov027_02084364->character.wFlags |= 2;
                pScene = data_ov027_02084364;
                if (pScene->nSlots == 3 && pScene->nCursor == 2 && pScene->bPrompt == 0) {
                    pScene->character.nSlot = 1;
                } else {
                    pScene->character.nSlot = *pCursor;
                }
                data_ov027_02084364->aBlink[*pCursor].nPhase = 1;
                data_ov027_02084364->aBlink[*pCursor].nTimer = 0;
                for (i = 0; i < data_ov027_02084364->nSlots; i++) {
                    func_ov027_02083c78(&data_ov027_02084364->panel, i, data_ov027_02084364->aBlink[i].nPhase);
                }
            }
        }
    }
}
