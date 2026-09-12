/* Ov022_DrawStateMarker -- draw an actor's shown state marker over a world
 * point and age it.
 *
 * Nothing is drawn under the pause lock. The slot must be shown; without a
 * current view target it is hidden. Otherwise the point, lifted by the
 * panel's y offset, is projected: behind the camera hides the slot, else the
 * sprite of the slot's state lands at the projection shifted by the panel's x
 * offset, the view is reset, the sprite drawn and the target's view
 * restored. The slot's timer then advances by the frame delta and hides it
 * once it reaches three units.
 */

typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022ScreenPos: an fx32 screen position */
struct ScreenPos {
    int x;
    int y;
};

/* Ov022MarkerSprite: one of the panel's 0x30-byte sprites */
struct MarkerSprite {
    u8 pad00[0x10];
    struct ScreenPos pos;        /* 0x10 */
    u8 pad18[0x18];
};

/* Ov022MarkerSlot: one actor's marker */
struct MarkerSlot {
    struct MarkerSprite *pSprites; /* 0x00 one per state */
    u8 bShown;                   /* 0x04 */
    u8 nState;                   /* 0x05 */
    u8 pad06[2];
    int nTimer;                  /* 0x08 */
};

/* Ov022MarkerPanel */
struct MarkerPanel {
    u8 nKind;                    /* 0x00 */
    u8 nCount;                   /* 0x01 sprites per slot */
    u8 pad02[2];
    int nYLift;                  /* 0x04 added to the world y */
    int nXShift;                 /* 0x08 added to the screen x */
    struct MarkerSlot aSlots[4]; /* 0x0c one per actor id */
};

#define MARKER_KIND_STATE 0
#define MARKER_KIND_MENU 1
#define MARKER_LIFE 0x3000
#define VIEW_NONE (-1)

extern u8 data_0204be04;                             /* pause lock */
extern struct MarkerPanel *data_ov022_020b2ec0[2];   /* the two marker panels by kind */

extern int func_ov022_02083f0c(void);                /* current view target, -1 when none */
extern int func_ov022_020b1d90(VecFx32 *pWorld, struct ScreenPos *pScreen);
extern void func_ov002_02050e64(void);               /* reset the view to default */
extern void func_ov002_0205126c(struct MarkerSprite *pSprite);
extern void func_ov000_0204cac0(int nTarget, int nMode);

void func_ov022_020b2118(int nKind, int nId, VecFx32 *pPos, int nDelta)
{
    VecFx32 vecWorld;
    struct ScreenPos posScreen;
    struct MarkerPanel *pPanel;
    struct MarkerSlot *pSlot;
    struct MarkerSprite *pSprite;
    int nTarget;

    if (data_0204be04 != 0) {
        return;
    }
    switch (nKind) {
    case MARKER_KIND_STATE:
        pPanel = data_ov022_020b2ec0[0];
        break;
    case MARKER_KIND_MENU:
        pPanel = data_ov022_020b2ec0[1];
        break;
    }
    pSlot = &pPanel->aSlots[nId];
    if (pSlot->bShown == 0) {
        return;
    }
    nTarget = func_ov022_02083f0c();
    if (nTarget == VIEW_NONE) {
        pSlot->bShown = 0;
        return;
    }
    vecWorld = *pPos;
    vecWorld.y += pPanel->nYLift;
    pSprite = &pSlot->pSprites[pSlot->nState - 1];
    if (func_ov022_020b1d90(&vecWorld, &posScreen) < 0) {
        pSlot->bShown = 0;
    } else {
        posScreen.x += pPanel->nXShift;
        pSprite->pos = posScreen;
        func_ov002_02050e64();
        func_ov002_0205126c(pSprite);
        func_ov000_0204cac0(nTarget, 0);
    }
    pSlot->nTimer += nDelta;
    if (pSlot->nTimer >= MARKER_LIFE) {
        pSlot->bShown = 0;
    }
}
