/* Page-scroll tick for the ov009 menu: eases each of the three pages towards its
 * target position and re-places the eight background cells of every page.
 *
 * Third instance of the same source function as Ov008/Ov025_TickPageScroll and
 * Ov000_TickPageScroll -- see src/overlays/scenes/ov008_camp_menu/Ov008_TickPageScroll.c for the
 * codegen note that unlocks all of them (the two aPageTarget reads are independent
 * scheduling knobs: .x through a `volatile int *` local, .y plain).
 *
 * Two things differ from the ov008 twin and both are visible in the ROM:
 *   - nActiveState takes seven dense values here, so mwcc builds a jump table
 *     (`cmp #6` + `addls pc,pc,r1,lsl #2`) instead of a compare chain; cases 0 and 6
 *     reset, cases 1 and 4 snap to the page origin, the rest fall through;
 *   - the fallback inside the loop tests BOTH reset states (`cmp r0,#0` +
 *     `cmpne r0,#6`), mirroring the outer switch. Testing only state 0 -- which is
 *     what the ov008 twin does, because there case 0 stands alone -- leaves the
 *     function exactly one instruction short at 816 B and is otherwise identical.
 *
 * The tail also carries a fallback the twins lack: a negative nPageIndex selects
 * nFallbackPage instead (`cmp r1,#0` + `ldrlt r1,[r4,#4]`).
 */

typedef struct Ov009Pair { int x; int y; } Ov009Pair;
typedef struct Ov009PairCur { int x; int y; } Ov009PairCur;

typedef struct Ov009PageCtx {
    int nPageIndex;
    int nFallbackPage;
    int nActiveState;
    unsigned char pad_000c[0x6c - 0xc];
    Ov009Pair aCellOffset[3][8];
    Ov009Pair aPageTarget[3];
    Ov009PairCur aPageCurrent[3];
} Ov009PageCtx;

extern const int data_ov009_020560a8[3][8];

extern int   Ov009_GetCtxBlock9500(void);
extern int   Ov009_GetContext(void);
extern int Ov009_TryApplyPageStep(void *pCtx, int tag, Ov009Pair step);
extern int   Ov009_FindEntryById(int obj, int id);
extern Ov009Pair *Ov009_ApplyFirstValidSlot(int obj, int entry);
extern void  Ov009_ReleaseTwoSlotsEx(int obj, int entry, Ov009Pair *pos);
extern void  Ov009_SaveMenu_DrawSummaries(Ov009PageCtx *ctx);
extern void  Ov009_TickSlotTween(Ov009PageCtx *ctx);
extern void  Ov009_CallSelectionHandler(int obj, int flag);
extern void  EnqueueObjGfxCommand(int addr);
extern void  Ov009_TickSelectionWidget(int handle);

static volatile unsigned int *const g_pBg1Scroll = (volatile unsigned int *)0x04000018;

void Ov009_TickPageScroll(Ov009PageCtx *ctx)
{
    int i;
    unsigned int j;
    int handle;
    int obj;
    Ov009Pair pos;
    Ov009Pair mv = { 0, 0 };
    Ov009Pair cur;
    int move;
    int entry;
    int oy;
    int ox;
    Ov009Pair *p;

    handle = Ov009_GetCtxBlock9500();
    obj = Ov009_GetContext();

    switch (ctx->nActiveState) {
    case 0:
    case 6:
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
        if (Ov009_TryApplyPageStep(ctx, i, mv) == 0) {
            if (ctx->nActiveState == 0 || ctx->nActiveState == 6) {
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
            entry = Ov009_FindEntryById(obj, data_ov009_020560a8[i][j]);
            Ov009_ApplyFirstValidSlot(obj, entry);
            pos.y = oy + ctx->aCellOffset[i][j].y;
            pos.x = ox + ctx->aCellOffset[i][j].x;
            Ov009_ReleaseTwoSlotsEx(obj, entry, &pos);
        }
    }
    Ov009_SaveMenu_DrawSummaries(ctx);
    Ov009_TickSlotTween(ctx);
    Ov009_CallSelectionHandler(obj, 0);
    {
        int pg = ctx->nPageIndex;
        if (pg < 0) {
            pg = ctx->nFallbackPage;
        }
        entry = Ov009_FindEntryById(obj, pg + 1);
    }
    p = Ov009_ApplyFirstValidSlot(obj, entry);
    *g_pBg1Scroll = ((-(p->x >> 12)) & 0x1ff)
                  | (((-(p->y >> 12)) << 16) & (0x1ff << 16));
    EnqueueObjGfxCommand((int)ctx + 0x1e0);
    Ov009_TickSelectionWidget(handle);
}
