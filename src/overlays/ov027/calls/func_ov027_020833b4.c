/* func_ov027_020833b4 -- Ov027_InitCharacterObject: set up the game-over screen's character
 * object (an ov002 display object).  It is started on the scene's character resource (+0x18 of
 * the scene work, packed into the ov002 descriptor word as ((p + 0x8000) & 0xfffffc) << 7 with
 * bit 31 and index 1; ov002 02050cd4), gets alpha 0x1f (bits 0-4 of +0x2a) and depth 0x3e (+0x24).
 * Its position comes from the scene data (data_ov027_02083ee0): the class descriptor's own
 * position (+8) in a session (bit 1 of data_0204c240) or when the room word (data_0204c240 + 2)
 * is 10000 or more, else the first placement (+0x44) -- and then the first placement is stored
 * anyway; the scale is the descriptor's (+0x10) and the angle (+0x30) and the two words at
 * +0x34 / +0x38 are cleared. */
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

typedef struct Ov027ClassDesc {
    int  nId;                 /* 0x00 */
    void *pfnInit;            /* 0x04: func_ov027_02082bec */
    void *pfnExit;            /* 0x08: func_ov027_02082cd8 */
    int  nWorkSize;           /* 0x0c: 0x630 */
    int  nField10;            /* 0x10 */
} Ov027ClassDesc;             /* 0x14 */

/* the scene's static data: the yes / no cursor, the scene handle, the character placement,
 * the class descriptor, the hint strings and the placements share one base
 * (data_ov027_02083ee0) */
typedef struct Ov027Data {
    int  nChoice;             /* 0x00: the yes / no cursor, 1 = no */
    int  nHandle;             /* 0x04: the scene object handle */
    Fx32Pair vCharacterPos;   /* 0x08 */
    Fx32Pair vCharacterScale; /* 0x10 */
    Ov027ClassDesc classDesc; /* 0x18 */
    const char *apHint[6];    /* 0x2c: data_ov027_02083f0c, per language */
    Fx32Pair aPlacement[2][3]; /* 0x44: the character placements, plain / highlighted rows */
} Ov027Data;

typedef struct Ov027SessionInfo {
    u8   nBits;               /* 0x00: bit 1 = client, bit 2 = wireless session */
    u8   pad_01;
    u16  nRoom;               /* 0x02: the room number */
} Ov027SessionInfo;

extern int   func_ov002_02050cd4(Ov027Object *pObject, u32 nDescriptor); /* start an object on a resource */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern Ov027SessionInfo data_0204c240;                                 /* session bits */
extern const Ov027Data data_ov027_02083ee0;

void func_ov027_020833b4(Ov027Object *pObject)
{
    func_ov002_02050cd4(pObject, ((((u32)data_ov027_02084364->pArchive + 0x8000) & 0xfffffc) << 7) | 0x80000001);
    pObject->nAlpha = (pObject->nAlpha & ~0x1f) | 0x1f;
    pObject->nDepth = 0x3e;
    if ((data_0204c240.nBits & 2) || data_0204c240.nRoom >= 10000) {
        pObject->vPos = data_ov027_02083ee0.vCharacterPos;
    } else {
        pObject->vPos = data_ov027_02083ee0.aPlacement[0][0];
    }
    pObject->vPos = data_ov027_02083ee0.aPlacement[0][0];
    pObject->vScale = data_ov027_02083ee0.vCharacterScale;
    pObject->wFlags = 0;
    pObject->nSlot = 0;
    pObject->nPhase = 0;
}
