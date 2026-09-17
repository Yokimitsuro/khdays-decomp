/* func_ov027_02083168 -- Ov027_LoadCharacterModels: load the fallen characters shown on the
 * game-over screen.  In a wireless session (bit 2 of data_0204c240) every occupied slot
 * (Session_GetSlotIfOccupied 020315c0) gets a model: the definition named by its member kind
 * (data_ov027_02084190, "ba/ch/<kind>/def*.p.z") is registered (0202a634, heap 6), its idle
 * animation is loaded from the game-over archive (+0x18 of the scene work; the packed source id
 * carries the archive pointer above the kind's entry from data_ov027_020840f0) into the matching
 * slot (+0x448, 0202a388) and started on track 0 (0202accc); the loaded models are then placed
 * on the row of data_ov027_02083e10 for that many characters.  In single player only the
 * player is loaded (Roxas, or Xion after byte 3 of data_0204c678 is set: entry 19), with
 * animation entry 2 and the position data_ov027_02083e04. */
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

typedef struct Ov027SessionSlot {
    int  nField00;            /* 0x00 */
    int  nMemberKind;         /* 0x04 */
} Ov027SessionSlot;

typedef struct Ov027PlayerRecord {
    u8   pad_00[3];
    u8   bXion;               /* 0x03 */
} Ov027PlayerRecord;

extern Ov027SessionSlot *func_020315c0(int nSlot);                  /* Session_GetSlotIfOccupied */
extern void  func_0202a634(Ov027Model *pModel, const char *pszDef, int nA, int nHeap); /* Model_Register */
extern void  func_0202a388(Ov027AnimSlot *pSlot, Ov027Model *pModel, u32 nSource, int nHeap); /* AnimSlot_Load */
extern void  func_0202accc(Ov027Model *pModel, int nTrack, Ov027AnimSlot *pSlot, int nFrame); /* Anim_PlayTrack */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern Ov027SessionInfo data_0204c240;
extern Ov027PlayerRecord data_0204c678;
extern const char *data_ov027_02084190[];                           /* model definition per member kind */
extern s8    data_ov027_020840f0[];                                 /* animation entry per member kind */
extern VecFx32 data_ov027_02083e10[4][4];                           /* positions by character count */
extern VecFx32 data_ov027_02083e04;                                 /* the single-player position */

void func_ov027_02083168(void)
{
    int nLoaded;
    int i;
    int nKind;
    Ov027SessionSlot *pSlot;

    if (data_0204c240.nBits & 4) {
        nLoaded = 0;
        for (i = 0; i < 4; i++) {
            pSlot = func_020315c0(i);
            if (pSlot != 0) {
                nKind = pSlot->nMemberKind;
                func_0202a634(&data_ov027_02084364->aModel[nLoaded], data_ov027_02084190[nKind], 0, 6);
                func_0202a388(&data_ov027_02084364->aAnimSlot[nLoaded], &data_ov027_02084364->aModel[nLoaded],
                              (((((u32)data_ov027_02084364->pArchive + 0x8000) & 0xfffffc) << 7) | 0x80000000)
                                  | (data_ov027_020840f0[nKind] & 0x1ff),
                              6);
                func_0202accc(&data_ov027_02084364->aModel[nLoaded], 0, &data_ov027_02084364->aAnimSlot[nLoaded], 0);
                nLoaded++;
            }
        }
        data_ov027_02084364->nModels = nLoaded;
        for (i = 0; i < data_ov027_02084364->nModels; i++) {
            data_ov027_02084364->aModel[i].vPos = data_ov027_02083e10[data_ov027_02084364->nModels - 1][i];
        }
    } else {
        data_ov027_02084364->nModels = 1;
        if (data_0204c678.bXion == 0) {
            func_0202a634(&data_ov027_02084364->aModel[0], data_ov027_02084190[0], 0, 6);
        } else {
            func_0202a634(&data_ov027_02084364->aModel[0], data_ov027_02084190[19], 0, 6);
        }
        func_0202a388(&data_ov027_02084364->aAnimSlot[0], &data_ov027_02084364->aModel[0],
                      ((((u32)data_ov027_02084364->pArchive + 0x8000) & 0xfffffc) << 7) | 0x80000002, 6);
        func_0202accc(&data_ov027_02084364->aModel[0], 0, &data_ov027_02084364->aAnimSlot[0], 0);
        data_ov027_02084364->aModel[0].vPos = data_ov027_02083e04;
    }
}
