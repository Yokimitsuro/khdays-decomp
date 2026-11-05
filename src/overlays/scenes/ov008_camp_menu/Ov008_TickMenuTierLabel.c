/* Ov008_TickMenuTierLabel -- Ov008_TickMenuTierLabel: once a second (60 frames) pick
 * the tier label for the current menu entry (Ov008_Config_GetTabTitleRecord on the list id,
 * selection and previous label index), then redraw the label field: clear the
 * text surface, fit the glyph set to the label text (max width 0xa0), draw it
 * with a shadow at (0xfa, 2) and queue the surface upload.
 */

#include "nitro/types.h"

#define LABEL_CYCLE_FRAMES 60
#define LABEL_MAX_WIDTH    0xa0
#define LABEL_X            0xfa
#define LABEL_Y            2
#define LABEL_STYLE        2

typedef struct Ov008MenuContext {
    s16 nSelection;           /* 0x000 */
    u16 nListId;              /* 0x002 */
    u8  varRecords[0xc];      /* 0x004 */
    u8  labelField[0xa4];     /* 0x010: Ov008TextField / draw surface */
    int nLabelIndex;          /* 0x0b4 */
    int nLabelTimer;          /* 0x0b8 */
} Ov008MenuContext;

#define LABEL_COLOUR       0x821

extern Ov008MenuContext *Ov008_GetMenuContext(void);               /* Ov008_GetMenuContext */
extern int Ov008_Config_GetTabTitleRecord(int nListId, unsigned int nSelection, int nPrev);
extern void Obj_InvokeInnerVtable8(void *pSurface, int a, int b, int c, int d);  /* Obj_InvokeInnerVtable8 */
extern char *Ov008_GetVarRecordByIndex(void *pRecords, int nIndex);     /* GetVarRecordByIndex */
extern int Ov008_FitTextFieldFont(void *pField, char *pText, int nMaxWidth); /* Ov008_FitTextFieldFont */
extern void Ov008_DrawPageAElementWithShadow(char *pText, int nX, int nY, int nStyle, unsigned int nColour, int bShadow); /* Ov008_DrawPageAElementWithShadow */
extern void EnqueueObjGfxCommand(void *pSurface);                        /* EnqueueObjGfxCommand */

void Ov008_TickMenuTierLabel(void)
{
    Ov008MenuContext *pCtx;
    char *pText;

    pCtx = Ov008_GetMenuContext();
    pCtx->nLabelTimer++;
    if (pCtx->nLabelTimer > LABEL_CYCLE_FRAMES) {
        pCtx->nLabelTimer = 0;
        pCtx->nLabelIndex = Ov008_Config_GetTabTitleRecord(pCtx->nListId, (u16)pCtx->nSelection, pCtx->nLabelIndex);
    }
    Obj_InvokeInnerVtable8(pCtx->labelField, 0, 2, 0x100, 0x10);
    pText = Ov008_GetVarRecordByIndex(pCtx->varRecords, pCtx->nLabelIndex);
    Ov008_FitTextFieldFont(pCtx->labelField, pText, LABEL_MAX_WIDTH);
    Ov008_DrawPageAElementWithShadow(pText, LABEL_X, LABEL_Y, LABEL_STYLE, LABEL_COLOUR, 1);
    EnqueueObjGfxCommand(pCtx->labelField);
}
