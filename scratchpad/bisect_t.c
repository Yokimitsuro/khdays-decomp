/* Page-scroll tick for the ov000 title/menu stack: eases each of the four selection
 * pages towards its target position and re-places the eight background cells of every
 * page, then feeds the resulting origin back into the scroll setters.
 *
 * aPageCurrent[i] is the page's resting position, aPageTarget[i] the position actually
 * drawn; each frame the drawn position closes a quarter of the gap and snaps once the
 * step falls below 0x800 (1/8 px in 1.19.12 fixed point). The page whose index equals
 * nPageIndex is offset by +0x8000, and the extra-entry case nudges it a further 0x8000.
 * A cell id of 0 means "no cell in that slot" and is skipped.
 *
 * This is the same source function as Ov008/Ov025_TickPageScroll (see
 * src/overlays/ov008/calls/func_ov008_02068e68.c) with four pages instead of three and
 * the context reached through a pool global rather than a parameter.
 *
 * CODEGEN NOTE -- two independent orderings had to be got right, and both look like
 * scheduling ties until you stop varying them together:
 *
 *  1. The cur[] re-reads. Written plainly mwcc keeps cur[0]/cur[1] in registers where
 *     the ROM re-reads both from the frame. Reading them through a volatile cast --
 *     while leaving the OBJECT unqualified -- restores the re-reads; qualifying the
 *     object instead costs extra instructions and loses the register colouring.
 *  2. The fallback branch. `cur[0] = -0xf0000;` must precede the mv.x computation:
 *     the ROM materialises the constant for the negation first (r2) and the sum
 *     second (r1), and computing the sum first swaps that pair. With the store first
 *     and the addend written inline the whole function is byte-exact.
 *
 * The twin needed one further distinction that this one does not: there the two
 * aPageTarget reads had to be spelled DIFFERENTLY (.x through a `volatile int *`
 * local, .y plain). Here both are plain. Worth knowing that the two reads are
 * separate knobs even when they happen to want the same spelling.
 */

typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov000Pair {
    int x;
    int y;
} Ov000Pair;

typedef struct Ov000PairCur {
    volatile int x;
    volatile int y;
} Ov000PairCur;

typedef struct Ov000LoadPageContext {
    u8 pad_0000[0x4acc];
    u8 bExtraEntryActive;
    u8 pad_4acd[1];
    u8 bSelectedPage;
    u8 pad_4acf[1];
    int nActiveState;
    u8 pad_4ad4[0x4b08 - 0x4ad4];
    int nPageIndex;
    u8 pad_4b0c[0x4b74 - 0x4b0c];
    Ov000Pair aCellOffset[4][8];
    u8 pad_4c74_pre[0];
    Ov000Pair aPageTarget[4];
    u8 pad_4c94_pre[0];
    Ov000PairCur aPageCurrent[4];
} Ov000LoadPageContext;

typedef struct Ov000LoadPageContextB {
    u8 pad_0000[0x4c];
    u8 aSelectionObject[1];
} Ov000LoadPageContextB;

typedef struct Ov000ScrollWork {
    int mag[2];
    Ov000Pair mv;
} Ov000ScrollWork;

extern const int data_ov000_0205a7ac[4][8];
extern Ov000LoadPageContext *data_ov000_0205ac24;

extern int  func_ov000_02051980(int page, Ov000Pair step);
extern int  func_ov000_02055b48(u8 *obj, int id);
extern void func_ov000_02055bfc(u8 *obj, int entry, Ov000Pair *pos);
extern void func_ov000_0205157c(void);
extern int  func_ov000_0205578c(u8 *obj, int arg);
extern Ov000Pair *func_ov000_02055bc4(u8 *obj, int entry);
extern void func_ov000_02051648(int y, int x);
extern void func_ov000_020512b8(u32 x, u32 y);
extern void func_ov000_020564f4(void *object);

extern int ov000_Classify(int *pOut, int nMode);

void func_ov000_02050ec4(int nA, int nB)
{
    Ov000LoadPageContext *ctx = data_ov000_0205ac24;
    int i;
    u32 j;
    int cur[2];
    Ov000ScrollWork w;
    int move;
    int entry;
    int nCol;

    switch (ov000_Classify(&nCol, ctx->nActiveState)) {
    case 0:
    case 2:
    case 7:
        for (i = 0; i < 4; i++) {
            data_ov000_0205ac24->aPageCurrent[i].y = 0;
        }
        break;
    case 1:
        break;
    case 3:
    case 4:
    case 5:
    case 6:
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
        case 3:
            ctx->aPageCurrent[ctx->nPageIndex].y = -0x34000;
            break;
        }
        {
            Ov000LoadPageContext *c2 = data_ov000_0205ac24;
            if (c2->bExtraEntryActive != 0 && c2->nPageIndex < 3) {
                c2->aPageCurrent[c2->nPageIndex].y += 0x8000;
            }
        }
        break;
    }

    for (i = 0; i < 4; i++) {
        Ov000LoadPageContext *c3;
        move = 1;
        c3 = data_ov000_0205ac24;
        {
            int cx = c3->aPageCurrent[i].x;
            int cy = c3->aPageCurrent[i].y;
            int pi = c3->nPageIndex;
            int c0;
            cur[0] = cx;
            cur[1] = cy;
            if (i == pi) {
                cur[0] = cx + 0x8000;
            }
            w.mv.x = (data_ov000_0205ac24->aPageTarget[i].x - (*(volatile int *)&cur[0])) / 4;
        }
        w.mv.y = (data_ov000_0205ac24->aPageTarget[i].y - (*(volatile int *)&cur[1])) / 4;
        if (func_ov000_02051980(i, w.mv) == 0) {
            Ov000LoadPageContext *c4 = data_ov000_0205ac24;
            int st = c4->nActiveState;
            if (st == 0 || st == 2 || st == 7) {
                if (i != c4->bSelectedPage) {
                    cur[0] = -0xf0000;
                    w.mv.x = (c4->aPageTarget[i].x + 0xf0000) / 4;
                }
            } else {
                move = 0;
            }
        }
        w.mag[0] = w.mv.x;
        w.mag[1] = w.mv.y;
        if (w.mag[0] < 0) {
            w.mag[0] *= -1;
        }
        if (w.mag[1] < 0) {
            w.mag[1] *= -1;
        }
        if (w.mag[0] < 0x800) {
            data_ov000_0205ac24->aPageTarget[i].x = (*(volatile int *)&cur[0]);
        } else {
            data_ov000_0205ac24->aPageTarget[i].x =
                data_ov000_0205ac24->aPageTarget[i].x - w.mv.x;
        }
        if (move != 0) {
            if (w.mag[1] < 0x800) {
                data_ov000_0205ac24->aPageTarget[i].y = (*(volatile int *)&cur[1]);
            } else {
                data_ov000_0205ac24->aPageTarget[i].y =
                    data_ov000_0205ac24->aPageTarget[i].y - w.mv.y;
            }
        }
        {
            Ov000LoadPageContext *c5 = data_ov000_0205ac24;
            u32 by, bx;
            j = 0;
            by = c5->aPageTarget[i].y & ~0xfff;
            bx = c5->aPageTarget[i].x & ~0xfff;
            for (; j < 8; j++) {
                int id = data_ov000_0205a7ac[i][j];
                if (id != 0) {
                    entry = func_ov000_02055b48(
                        ((Ov000LoadPageContextB *)ctx)->aSelectionObject, id);
                    w.mv.y = by + data_ov000_0205ac24->aCellOffset[i][j].y;
                    w.mv.x = bx + data_ov000_0205ac24->aCellOffset[i][j].x;
                    func_ov000_02055bfc(
                        ((Ov000LoadPageContextB *)ctx)->aSelectionObject, entry, &w.mv);
                }
            }
        }
    }

    func_ov000_0205157c();
    func_ov000_0205578c(((Ov000LoadPageContextB *)ctx)->aSelectionObject, 0);
    entry = func_ov000_02055b48(((Ov000LoadPageContextB *)ctx)->aSelectionObject,
                                data_ov000_0205ac24->nPageIndex + 1);
    {
        Ov000Pair *p = func_ov000_02055bc4(
            ((Ov000LoadPageContextB *)ctx)->aSelectionObject, entry);
        int px = p->x;
        int py = p->y;
        int x12, y12;
        w.mv.x = px;
        w.mv.y = py;
        x12 = w.mv.x >> 12;
        y12 = w.mv.y >> 12;
        func_ov000_02051648(py, px);
        func_ov000_020512b8(-x12, -y12);
        func_ov000_020564f4(ctx);
    }
}
