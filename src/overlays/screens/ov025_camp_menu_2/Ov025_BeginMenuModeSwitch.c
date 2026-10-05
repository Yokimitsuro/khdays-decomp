/* Ov025_BeginMenuModeSwitch -- Ov008_BeginMenuModeSwitch: start switching the grid
 * menu to mode nMode.  Unless the menu state (+0x10) is already 2 the grid is
 * reset and state 2 entered.  Mode 0 requests cursor mode 0x14 with 0; mode 1
 * hides widgets 400..407, 500..507, 1, 2 and 0x4a, disables the row block,
 * refreshes the equip panel from the summary (+0x1f78) and requests cursor
 * mode 0x14 with 4.  Then the grid is refreshed, widget 3 hidden, context
 * field 95fc cleared, the slide tween (+0x368) configured from 0 to -10.0
 * (fx32) over 100 frames and started, context field 9628 set, the transition
 * flag (+0x4) raised, the save-page group shown or hidden for the mode, and
 * the mode recorded (+0x8, previous one kept at +0xc).
 */

#include "nitro/types.h"

#define STATE_IDLE     2
#define CURSOR_MODE_DRAG 0x14
#define WIDGET_DRAG    3
#define WIDGET_ICON    0x4a
#define ROW_WIDGET_A   400
#define ROW_WIDGET_B   500
#define ROW_WIDGET_COUNT 8
#define SLIDE_TARGET   (-0xa0000)
#define SLIDE_FRAMES   100

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    long long startTick;
    u32 flags;
} Tween;

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008MenuContext {
    u8  pad_0000[4];
    int bTransition;          /* 0x0004 */
    int menuMode;             /* 0x0008 */
    int prevMenuMode;         /* 0x000c */
    int menuState;            /* 0x0010 */
    u8  pad_0014[0x368 - 0x14];
    Tween slideTween;         /* 0x0368 */
    u8  pad_0384[0x1f78 - 0x384];
    Ov008GridSummary summary; /* 0x1f78 */
} Ov008MenuContext;

extern int  Ov025_GetContext(void);                                    /* Ov008_GetContext */
extern void Ov025_ResetGridDrag(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void Ov025_EnterMenuState(Ov008MenuContext *pCtx, int nState);      /* enter a menu state */
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...); /* cursor mode request */
extern void *Ov025_FindEntryById(int nCtx, int nId);                      /* FindEntryById */
extern void Ov025_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void Ov025_ClearTagRange(void);                                    /* Ov008_DisableRowBlock */
extern void Ov025_RefreshStatusPage(Ov008GridSummary *pSummary);              /* Ov008_RefreshEquipPanel */
extern void Ov025_PageB_UploadSurface154(void);                                    /* grid refresh */
extern void Ov025_SetCtxField95fc(int nValue);                              /* Ov008_SetCtxField95fc */
extern void Tween_Configure(Tween *pTween, int nMode, int nFrom, int nTo, int nFrames); /* Tween_Configure */
extern void Tween_Start(Tween *pTween);                                 /* Tween_Start */
extern void Ov025_SetCtxField9628(int nValue);                              /* Ov008_SetCtxField9628 */
extern void Ov025_SetSavePageGroupVisible(Ov008MenuContext *pCtx, int nMode);       /* Ov008_SetSavePageGroupVisible */

void Ov025_BeginMenuModeSwitch(Ov008MenuContext *pCtx, int nMode)
{
    int nCtx;
    int i;

    nCtx = Ov025_GetContext();
    if (pCtx->menuState != STATE_IDLE) {
        Ov025_ResetGridDrag(pCtx, 0);
        Ov025_EnterMenuState(pCtx, STATE_IDLE);
    }
    switch (nMode) {
    case 0:
        Ov025_DrawPageBElement(CURSOR_MODE_DRAG, 0, 0);
        break;
    case 1:
        for (i = ROW_WIDGET_A; i <= ROW_WIDGET_A + ROW_WIDGET_COUNT - 1; i++) {
            Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, i), 0);
        }
        for (i = ROW_WIDGET_B; i <= ROW_WIDGET_B + ROW_WIDGET_COUNT - 1; i++) {
            Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, i), 0);
        }
        Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, 1), 0);
        Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, 2), 0);
        Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, WIDGET_ICON), 0);
        Ov025_ClearTagRange();
        Ov025_RefreshStatusPage(&pCtx->summary);
        Ov025_DrawPageBElement(CURSOR_MODE_DRAG, 0, 4);
        break;
    }
    Ov025_PageB_UploadSurface154();
    Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, WIDGET_DRAG), 0);
    Ov025_SetCtxField95fc(0);
    Tween_Configure(&pCtx->slideTween, 1, 0, SLIDE_TARGET, SLIDE_FRAMES);
    Tween_Start(&pCtx->slideTween);
    Ov025_SetCtxField9628(1);
    pCtx->bTransition = 1;
    Ov025_SetSavePageGroupVisible(pCtx, nMode);
    pCtx->prevMenuMode = pCtx->menuMode;
    pCtx->menuMode = nMode;
}
