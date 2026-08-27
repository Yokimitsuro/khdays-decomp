/*
 * Draws one player's stroke on the map panel for this frame.
 *
 * A point whose stamp is zero ends the stroke and clears the slot's active
 * mark. A point carrying the stamp the slot already stored is a repeat, which
 * redraws from the stored position; anything else starts or continues a stroke
 * from the incoming point and marks the slot active.
 *
 * Above mode two the stroke is a single stamp rather than a line, and its shape
 * comes from two per-mode lookups. Otherwise a line is drawn from the previous
 * point to the new one, in white when the mode is one and in the slot's own pen
 * colour otherwise, thin or thick according to the slot's own flag.
 *
 * Every coordinate is clamped to the panel's origin and then biased by it.
 *
 * Five things here are load-bearing rather than style.
 *
 * The context pointer is declared before the slot entry pointer. That is what
 * puts the context in the first callee-saved register and the entry in the
 * second; declaring them the other way round swaps the two everywhere.
 *
 * The stamp test is written as an exclusive-or against zero. That is what emits
 * the equality-test form rather than a compare.
 *
 * Each coordinate is put into its own variable immediately after its own clamp,
 * rather than being written out at the call. That is what interleaves the
 * clamps with their subtractions instead of batching every subtraction at the
 * end.
 *
 * The pen is masked once, by landing in a byte variable, rather than being cast
 * inside the conditional and again on the way out of it, which masks twice.
 *
 * The step is declared inside the block that uses it. At function scope it
 * falls to the temporary pool and takes a high register; declared in its block
 * it takes the first callee-saved register the context vacates, and everything
 * downstream follows. The repeat arm declares it too even though it returns
 * without reading it: that declaration is what holds the allocation in place.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002PenTable {
    u32 aPens[4];
} Ov002PenTable;

typedef struct Ov002SlotContext {
    char pad000[4];
    int nSlot;
    char pad008[0x10];
    int aActive[4];
    int bFlag;
} Ov002SlotContext;

typedef struct Ov002SlotEntry {
    int nValue;
    int bThick;
    int nMode;
    u16 nLastX;
    u16 nLastY;
    u16 nLastStamp;
    char pad012[2];
} Ov002SlotEntry;

extern Ov002SlotEntry data_ov002_0207f9a0[];
extern Ov002SlotContext *data_ov002_0207f99c;
extern const Ov002PenTable data_ov002_0207e434;

extern u16 func_02030788(void);
extern int OS_IsThreadAvailable_0x0206373c(void);
extern int func_ov002_02067044(int nStep);
extern int func_ov002_02067068(int nStep);
extern void func_ov002_02066634(int hCanvas, u16 nX, u16 nY, u8 nPen, int a, int b);
extern void func_ov002_0206648c(int hCanvas, u16 nX, u16 nY, u16 nX2, u16 nY2, u8 nPen,
                     int nWidth);

void func_ov002_020659f0(int nSlot, const u16 *pPoint)
{
    Ov002SlotContext *pCtx;
    Ov002SlotEntry *pEntry;
    Ov002PenTable pens;
    int hCanvas;
    int nMode;
    u16 nX;
    u16 nY;
    u16 nX2;
    u16 nY2;
    u16 nDx1;
    u16 nDy1;
    u16 nDx2;
    u16 nDy2;
    u8 nPen;

    pEntry = &data_ov002_0207f9a0[nSlot];
    pCtx = data_ov002_0207f99c;
    pens = data_ov002_0207e434;

    func_02030788();
    hCanvas = OS_IsThreadAvailable_0x0206373c();
    if (hCanvas == 0) {
        return;
    }

    if (pPoint[2] == 0) {
        goto clear;
    }

    if ((pPoint[2] ^ pEntry->nLastStamp) != 0) {
        nX = pPoint[0];
        nY = pPoint[1];
        pCtx->aActive[nSlot] = 1;
        nMode = pEntry->nMode;
        if (nMode >= 2) {
            int nStep = nMode - 2;
            if (nX <= 0x18) {
                nX = 0x18;
            }
            nX2 = (u16)(nX - 0x18);
            if (nY <= 0x20) {
                nY = 0x20;
            }
            func_ov002_02066634(OS_IsThreadAvailable_0x0206373c(), nX2, (u16)(nY - 0x20),
                    pens.aPens[nSlot], func_ov002_02067044(nStep),
                    func_ov002_02067068(nStep));
            return;
        }
    } else {
        nMode = pEntry->nMode;
        if (nMode >= 2) {
            int nStep = nMode - 2;
            return;
        }
        nX = pEntry->nLastX;
        nY = pEntry->nLastY;
    }

    if (pCtx->aActive[nSlot] != 0) {
        if (nX <= 0x18) {
            nX = 0x18;
        }
        nDx1 = (u16)(nX - 0x18);
        nX2 = pPoint[0];
        if (nY <= 0x20) {
            nY = 0x20;
        }
        if (nX2 <= 0x18) {
            nX2 = 0x18;
        }
        nY2 = pPoint[1];
        nDy1 = (u16)(nY - 0x20);
        nDx2 = (u16)(nX2 - 0x18);
        if (nY2 <= 0x20) {
            nY2 = 0x20;
        }
        nDy2 = (u16)(nY2 - 0x20);
        nPen = nMode == 1 ? 0xff : pens.aPens[nSlot];
        func_ov002_0206648c(hCanvas, nDx1, nDy1, nDx2, nDy2, nPen,
                 pEntry->bThick == 0 ? 1 : 5);
    }
    return;

clear:
    pCtx->aActive[nSlot] = 0;
}
