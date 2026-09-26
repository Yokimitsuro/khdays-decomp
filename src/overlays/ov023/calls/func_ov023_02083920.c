/* func_ov023_02083920 -- Ov023_CreateHintSprites: create the event scene's three hint sprites.
 * The sprite manager at +0x144 is initialised with the "ev/hint_&.z" resource
 * (data_ov023_0208a098, enabled, 02032388); then three sprites are created (02032444) and kept
 * at +0x4b7c, each placed at its position from data_ov023_02089cfc (0203257c), sent to its
 * first animation entry (020325ec 0), shown (02032710 1) and left in the plain mode
 * (0203281c 0).
 * Codegen: the manager pointer is a local initialised once; mwcc propagates it into every use (base
 * + 0x144 re-added per call) and strength-reduces the slot array off it. */
typedef unsigned char  u8;

typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct SpriteManagerInit {
    void *pResource;          /* 0x00 */
    int  bEnabled;            /* 0x04 */
    int  nReserved0;          /* 0x08 */
    int  nReserved1;          /* 0x0c */
} SpriteManagerInit;

typedef struct Ov023SceneBlock {
    u8   a[0x144];
} Ov023SceneBlock;

typedef struct Ov023SpriteManager {
    u8   core[0x4a38];        /* 0x0000: shared sprite manager */
    void *apHintSprite[3];    /* 0x4a38 */
} Ov023SpriteManager;

typedef struct Ov023Scene {
    Ov023SceneBlock head;      /* 0x00000 */
    Ov023SpriteManager display; /* 0x00144 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

typedef struct Ov023HintPositions {
    Fx32Pair aPos[3];         /* 0x00 */
} Ov023HintPositions;

extern void  func_02032388(void *pManager, SpriteManagerInit *pInit);  /* SpriteManager_Init */
extern void *WM_EndKeySharing_0x02032444(void *pManager, int nIndex, int nArg); /* SpriteManager_Create */
extern void  func_0203257c(void *pManager, void *pSprite, Fx32Pair *pPos); /* Sprite_SetPosition */
extern void  func_020325ec(void *pManager, void *pSprite, int nEntry); /* Sprite_SetEntry */
extern void  func_02032710(void *pManager, void *pSprite, int bVisible); /* Sprite_SetVisible */
extern void  func_0203281c(void *pManager, void *pSprite, int nMode);  /* Sprite_SetMode */
extern Ov023SceneRoot data_ov023_0208a784;
extern const Ov023HintPositions data_ov023_02089cfc;                /* the hint positions */
extern char  data_ov023_0208a098[];                                 /* "ev/hint_&.z" */

void func_ov023_02083920(void)
{
    SpriteManagerInit init;
    Ov023HintPositions positions;
    int i;
    Ov023SpriteManager *pManager;

    pManager = &data_ov023_0208a784.pScene->display;
    positions = data_ov023_02089cfc;
    init.pResource = data_ov023_0208a098;
    init.bEnabled = 1;
    init.nReserved0 = 0;
    init.nReserved1 = 0;
    func_02032388(pManager, &init);
    for (i = 0; i < 3; i++) {
        pManager->apHintSprite[i] = WM_EndKeySharing_0x02032444(pManager, i, 0);
        func_0203257c(pManager, pManager->apHintSprite[i], &positions.aPos[i]);
        func_020325ec(pManager, pManager->apHintSprite[i], 0);
        func_02032710(pManager, pManager->apHintSprite[i], 1);
        func_0203281c(pManager, pManager->apHintSprite[i], 0);
    }
}
