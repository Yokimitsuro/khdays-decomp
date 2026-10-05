/* Page-scroll tick for the ov008 menu: eases each of the three pages towards its
 * target position and re-places the eight background cells of every page.
 *
 * aPageCurrent[i] holds the page's resting position and aPageTarget[i] the position
 * actually drawn; each frame the drawn position moves a quarter of the remaining
 * distance, snapping once the step falls below 0x800 (1/8 px in 1.12.19 fixed point).
 * The page whose index equals nPageIndex is offset by +0x8000 so the selected page
 * sits half a unit to the side. The final BG1 scroll write mirrors page 0's cell
 * origin into REG_BG1HOFS/VOFS.
 *
 * CODEGEN NOTE -- the two aPageTarget reads need DIFFERENT spellings, and that is
 * the whole difficulty of this function. Written the obvious way the body is 40
 * bytes short: mwcc keeps cur.x and cur.y in registers, while the ROM re-reads both
 * from the frame. Forcing the re-reads with a volatile access gets the size and the
 * instruction stream right but leaves one adjacent pair transposed, and WHICH pair
 * depends on how each aPageTarget read is written:
 *
 *   both reads through a volatile pointer local  -> +0x0FC `str mv.x` and
 *                                                   +0x100 `ldr cur.y` swap
 *   both reads plain                             -> +0x0E0 `ldr target.x` and
 *                                                   +0x0E4 `ldr cur.x` swap
 *   .x through the pointer, .y plain             -> byte-exact
 *
 * The pointer local pins its load ahead of the following stack re-read; the plain
 * read lets mwcc schedule it after. One of each is what the original source had.
 * Reading the two symmetric halves of an expression with the same spelling is the
 * natural thing to write and it is what kept this function unmatched: the residue
 * moved between the two pairs instead of shrinking, which reads like an unbreakable
 * scheduling tie when it is really two independent knobs that were always tied
 * together.
 */

typedef struct Ov008Pair { int x; int y; } Ov008Pair;
typedef struct Ov008PairCur { int x; int y; } Ov008PairCur;

typedef struct Ov008PageCtx {
    int nPageIndex;
    int nActiveState;
    unsigned char pad_0008[0x68 - 8];
    Ov008Pair aCellOffset[3][8];
    unsigned char pad_0128_pre[0x128 - 0x68 - 3 * 8 * 8];
    Ov008Pair aPageTarget[3];
    Ov008PairCur aPageCurrent[3];
} Ov008PageCtx;

extern const int data_ov008_0208f588[3][8];

extern int   Ov008_GetCtxBlock9500(void);
extern int   Ov008_GetContext(void);
extern int Ov008_TryApplyPageStep(void *pCtx, int tag, Ov008Pair step);
extern int   Ov008_FindEntryById(int obj, int id);
extern Ov008Pair *Ov008_GetEntryPos(int obj, int entry);
extern void  Ov008_SetEntryPos(int obj, int entry, Ov008Pair *pos);
extern void  Ov008_DrawSaveSlotTexts(Ov008PageCtx *ctx);
extern void  Ov008_TickTitleFade(Ov008PageCtx *ctx);
extern void  Ov008_CallSelectionHandler(int obj, int flag);
extern void  EnqueueObjGfxCommand(int addr);
extern void  Ov008_TickSelectionWidget(int handle);

static volatile unsigned int *const g_pBg1Scroll = (volatile unsigned int *)0x04000018;

void Ov008_TickPageScroll(Ov008PageCtx *ctx)
{
    int i;
    unsigned int j;
    int handle;
    int obj;
    Ov008Pair pos;
    Ov008Pair mv = { 0, 0 };
    Ov008Pair cur;
    int move;
    int entry;
    int oy;
    int ox;
    Ov008Pair *p;

    handle = Ov008_GetCtxBlock9500();
    obj = Ov008_GetContext();

    switch (ctx->nActiveState) {
    case 0:
        for (i = 0; i < 3; i++) {
            ctx->aPageCurrent[i].y = 0;
        }
        break;
    case 1:
    case 4:
        switch (ctx->nPageIndex) {
        case 0:
            ctx->aPageCurrent[ctx->nPageIndex].y = 0x24000;
            break;
        case 1:
            ctx->aPageCurrent[ctx->nPageIndex].y = 0;
            break;
        case 2:
            ctx->aPageCurrent[ctx->nPageIndex].y = -0x24000;
            break;
        }
        break;
    }

    for (i = 0; i < 3; i++) {
        int cx = ctx->aPageCurrent[i].x;
        int cy = ctx->aPageCurrent[i].y;
        int pi = ctx->nPageIndex;
        int c1;
        move = 1;
        cur.x = cx;
        cur.y = cy;
        if (i == pi) {
            cur.x = cx + 0x8000;
        }
        {   volatile int *vx = &ctx->aPageTarget[i].x;
            mv.x = (*vx - (*(volatile int *)&cur.x)) / 4; }
        c1 = (*(volatile int *)&cur.y);
        mv.y = (ctx->aPageTarget[i].y - c1) / 4;
        if (Ov008_TryApplyPageStep(ctx, i, mv) == 0) {
            if (ctx->nActiveState == 0) {
                if (i != 0) {
                    cur.x = 0x100000;
                    mv.x = (ctx->aPageTarget[i].x - 0x100000) / 4;
                }
            } else {
                move = 0;
            }
        }
        if ((mv.x < 0 ? -mv.x : mv.x) < 0x800) {
            ctx->aPageTarget[i].x = (*(volatile int *)&cur.x);
        } else {
            ctx->aPageTarget[i].x -= mv.x;
        }
        if (move != 0) {
            if ((mv.y < 0 ? -mv.y : mv.y) < 0x800) {
                ctx->aPageTarget[i].y = (*(volatile int *)&cur.y);
            } else {
                ctx->aPageTarget[i].y -= mv.y;
            }
        }
        j = 0;
        oy = ctx->aPageTarget[i].y & -0x1000;
        ox = ctx->aPageTarget[i].x & -0x1000;
        for (; j < 8; j++) {
            entry = Ov008_FindEntryById(obj, data_ov008_0208f588[i][j]);
            Ov008_GetEntryPos(obj, entry);
            pos.y = oy + ctx->aCellOffset[i][j].y;
            pos.x = ox + ctx->aCellOffset[i][j].x;
            Ov008_SetEntryPos(obj, entry, &pos);
        }
    }
    Ov008_DrawSaveSlotTexts(ctx);
    Ov008_TickTitleFade(ctx);
    Ov008_CallSelectionHandler(obj, 0);
    entry = Ov008_FindEntryById(obj, ctx->nPageIndex + 1);
    p = Ov008_GetEntryPos(obj, entry);
    *g_pBg1Scroll = ((-(p->x >> 12)) & 0x1ff)
                  | (((-(p->y >> 12)) << 16) & (0x1ff << 16));
    EnqueueObjGfxCommand((int)ctx + 0x1dc);
    Ov008_TickSelectionWidget(handle);
}
