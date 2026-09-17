/* func_ov027_02082bec -- Ov027_InitScene: the class init of the game-over scene.  The scene
 * work (NNSi_FndGetCurrentRootHeap) is published in data_ov027_02084360, the game-over
 * counter (byte +0x11 of data_0204c4d8) ticks up to 5, the retry prompt flag is read
 * (Ov027_HasRetryPrompt 020838f0), the "/gameover/data" archive is opened (02024ee8, heap 0xf)
 * and the fade starts from -16 in a wireless session (bit 2 of data_0204c240) or +16 otherwise
 * in mode 1.  The panel begins with three slots, the cursor on "quit" (slot 2) for a client
 * (bit 1) or on slot 0, no highlight and cleared blink timers, and the resource kind is 9.
 * Then the fallen characters (Ov027_LoadCharacterModels 02083168), the camera
 * (Ov027_InitCamera 0208334c), the panel (Ov027_LoadPanel 02083980) and the hint text
 * (Ov027_InitHintText 02083ccc) are set up; single player also builds the character object at
 * +0x588 (Ov027_InitCharacterObject 020833b4), a session host loads the sign-in panel
 * (Ov027_LoadSignInPanel 02082b54).  Returns the first state, Ov027_WaitSceneReady 02082d8c. */
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

typedef struct Ov027SessionTable {
    int  nState;              /* 0x00 */
    int  nCount;              /* 0x04 */
} Ov027SessionTable;

typedef struct Ov027GameInfo {
    u8   pad_00[0x11];
    s8   nGameOvers;          /* 0x11: capped at 5, when the hint text appears */
} Ov027GameInfo;

typedef void *(*Ov027StateFn)(void);

extern Ov027Scene *NNSi_FndGetCurrentRootHeap(void);                /* the current scene work */
extern Ov027SessionTable *CARDi_GetRomAccessor_0x020315f4(void);   /* Session_GetSlotTable */
extern int   func_ov027_020838f0(void);                             /* Ov027_HasRetryPrompt */
extern void *func_02024ee8(const char *pszName, int nHeap);         /* open an archive */
extern void  func_ov027_02083168(void);                             /* Ov027_LoadCharacterModels */
extern void  func_ov027_0208334c(void);                             /* Ov027_InitCamera */
extern void  func_ov027_02083980(void);                             /* Ov027_LoadPanel */
extern void  func_ov027_02083ccc(void);                             /* Ov027_InitHintText */
extern void  func_ov027_020833b4(Ov027Object *pObject);             /* Ov027_InitCharacterObject */
extern void  func_ov027_02082b54(Ov027Scene *pScene);               /* Ov027_LoadSignInPanel */
extern void *func_ov027_02082d8c(void);                             /* Ov027_WaitSceneReady */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern Ov027GameInfo  data_0204c4d8;
extern Ov027SessionInfo data_0204c240;
extern char  data_ov027_02084318[];                                 /* "/gameover/data" */

Ov027StateFn func_ov027_02082bec(void)
{
    Ov027Scene *pScene;
    int i;

    pScene = NNSi_FndGetCurrentRootHeap();
    CARDi_GetRomAccessor_0x020315f4();
    data_ov027_02084364 = pScene;
    if (data_0204c4d8.nGameOvers < 5) {
        data_0204c4d8.nGameOvers++;
    }
    pScene->bPrompt = func_ov027_020838f0();
    pScene->pArchive = func_02024ee8(data_ov027_02084318, 0xf);
    pScene->nBrightness = (data_0204c240.nBits & 4) ? -16 : 16;
    pScene->nMode = 1;
    pScene->nSwapTimer = 0;
    pScene->nSlots = 3;
    if (data_0204c240.nBits & 2) {
        pScene->nCursor = 2;
    } else {
        pScene->nCursor = 0;
    }
    for (i = 0; i < pScene->nSlots; i++) {
        pScene->aBlink[i].nTimer = 0;
    }
    pScene->nFlags = 9;
    func_ov027_02083168();
    func_ov027_0208334c();
    func_ov027_02083980();
    func_ov027_02083ccc();
    if (!(data_0204c240.nBits & 4)) {
        func_ov027_020833b4(&pScene->character);
    } else if (CARDi_GetRomAccessor_0x020315f4()->nState != 1) {
        func_ov027_02082b54(data_ov027_02084364);
    }
    return func_ov027_02082d8c;
}
