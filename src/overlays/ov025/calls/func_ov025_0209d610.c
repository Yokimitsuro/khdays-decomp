/* func_ov025_0209d610 -- Ov008_TickMenuTierLabel: once a second (60 frames) pick
 * the tier label for the current menu entry (func_ov025_0209bf18 on the list id,
 * selection and previous label index), then redraw the label field: clear the
 * text surface, fit the glyph set to the label text (max width 0xa0), draw it
 * with a shadow at (0xfa, 2) and queue the surface upload.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

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

extern Ov008MenuContext *func_ov025_02084afc(void);               /* Ov008_GetMenuContext */
extern int func_ov025_0209bf18(int nListId, unsigned int nSelection, int nPrev); /* SelectTierIfActive */
extern void func_0203011c(void *pSurface, int a, int b, int c, int d);  /* Obj_InvokeInnerVtable8 */
extern char *func_ov025_02089894(void *pRecords, int nIndex);     /* GetVarRecordByIndex */
extern int func_ov025_0209c2a0(void *pField, char *pText, int nMaxWidth); /* Ov008_FitTextFieldFont */
extern void func_ov025_0209cce8(char *pText, int nX, int nY, int nStyle, unsigned int nColour, int bShadow); /* Ov008_DrawPageAElementWithShadow */
extern void func_020300f8(void *pSurface);                        /* EnqueueObjGfxCommand */

void func_ov025_0209d610(void)
{
    Ov008MenuContext *pCtx;
    char *pText;

    pCtx = func_ov025_02084afc();
    pCtx->nLabelTimer++;
    if (pCtx->nLabelTimer > LABEL_CYCLE_FRAMES) {
        pCtx->nLabelTimer = 0;
        pCtx->nLabelIndex = func_ov025_0209bf18(pCtx->nListId, (u16)pCtx->nSelection, pCtx->nLabelIndex);
    }
    func_0203011c(pCtx->labelField, 0, 2, 0x100, 0x10);
    pText = func_ov025_02089894(pCtx->varRecords, pCtx->nLabelIndex);
    func_ov025_0209c2a0(pCtx->labelField, pText, LABEL_MAX_WIDTH);
    func_ov025_0209cce8(pText, LABEL_X, LABEL_Y, LABEL_STYLE, LABEL_COLOUR, 1);
    func_020300f8(pCtx->labelField);
}
