/* func_ov027_02083068 -- Ov027_GameOverIdle: the game-over state that fades the screens to the
 * session's end brightness.  In a mission session (bit 2 of data_0204c240) the brightness (+0x20
 * of the scene work) steps by -6 toward -16, otherwise by +6 toward +16, clamped to [-16, 16];
 * once it is there the scene leaves -- in a session the flag word is updated (Ov027_SetLeaving
 * 02082b24 with 0) and the terminal state (func_ov027_02083164) returned, otherwise
 * Ov027_GameOverFadeOut (02083114).  Every frame both screens get the brightness, the sign-in
 * panel is drawn unless the slot table's word is 1 (020315f4; Ov027_DrawSignInPanel 02082ba4),
 * the models animate (Ov027_UpdateModels 02083308), the camera (+0x4d8) is committed (02023cc0)
 * and, outside a session, the hint text drawn (Ov027_DrawHintText 02083d50). */
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

typedef struct Ov027SessionTable {
    int  nState;              /* 0x00 */
    int  nCount;              /* 0x04 */
} Ov027SessionTable;

extern Ov027Scene *NNSi_FndGetCurrentRootHeap(void);                /* the current scene work */
extern void  func_0201e374(int nBrightness);                        /* SetMasterBrightnessMain */
extern void  func_0201e3cc(int nBrightness);                        /* SetMasterBrightnessSub */
extern void  func_ov027_02082b24(int nArg);                         /* Ov027_SetLeaving */
extern void *func_ov027_02083164(void);                             /* the terminal state */
extern void *func_ov027_02083114(void);                             /* Ov027_GameOverFadeOut */
extern Ov027SessionTable *CARDi_GetRomAccessor_0x020315f4(void);        /* Session_GetSlotTable */
extern void  func_ov027_02082ba4(Ov027Scene *pScene);               /* Ov027_DrawSignInPanel */
extern void  func_ov027_02083308(void);                             /* Ov027_UpdateModels */
extern void  func_02023cc0(Ov027Camera *pCamera);                  /* Camera_Commit */
extern void  func_ov027_02083d50(void);                             /* Ov027_DrawHintText */
/* khdays: shared-bss */
int data_ov027_02084360 = 0;                                        /* the fade-out frame counter */
Ov027Scene *data_ov027_02084364 = 0;                                /* the scene work */
extern u8    data_0204c240;                                         /* session bits */

void *func_ov027_02083068(void)
{
    Ov027Scene *pScene;
    void *pNext;
    int bSession;
    int nTarget;

    pScene = NNSi_FndGetCurrentRootHeap();
    pNext = 0;
    bSession = data_0204c240 & 4;
    if (bSession) {
        nTarget = -16;
    } else {
        nTarget = 16;
    }
    if (pScene->nBrightness == nTarget) {
        if (bSession) {
            func_ov027_02082b24(0);
            pNext = func_ov027_02083164;
        } else {
            pNext = func_ov027_02083114;
        }
    } else {
        pScene->nBrightness += bSession ? -6 : 6;
        if (pScene->nBrightness < -16) {
            pScene->nBrightness = -16;
        }
        if (pScene->nBrightness > 16) {
            pScene->nBrightness = 16;
        }
    }
    func_0201e374(pScene->nBrightness);
    func_0201e3cc(pScene->nBrightness);
    if (CARDi_GetRomAccessor_0x020315f4()->nState != 1) {
        func_ov027_02082ba4(data_ov027_02084364);
    }
    func_ov027_02083308();
    func_02023cc0(&pScene->camera);
    if (!(data_0204c240 & 4)) {
        func_ov027_02083d50();
    }
    return pNext;
}
