/*
 * Applies one command to the session timers.
 *
 * The low six bits pick the command; for the two lap commands the rest index
 * which lap. Starting clears the run and marks it running, unless the timers
 * are locked. Ticking adds the delta to the run and the total, to the split
 * while it is armed, and to each armed lap. Stopping does the same tick and
 * then settles the flags. The remaining four arm and clear the split and the
 * laps.
 *
 * Two things here are load-bearing rather than style.
 *
 * Stopping does not carry the split forward - the tick does, the stop does not,
 * and writing them the same costs six instructions the original does not have.
 *
 * Each flag edit is its own compound assignment on the field. Folded into one
 * expression the compiler merges the masks into a single instruction; written
 * separately it keeps one per mask and still loads and stores only once, which
 * is what the original does.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov002TickCtx {
    int nFlags;
    int nLastMs;
    int nElapsed;
    int nTotal;
    int nRun;
    int nSplit;
    int aLaps[2];
} Ov002TickCtx;

extern Ov002TickCtx *data_ov002_0207fa08;

void func_ov002_0206f788(int nKind, int nDelta)
{
    Ov002TickCtx *pCtx;
    int k;

    pCtx = data_ov002_0207fa08;
    switch (nKind & 0x3f) {
    case 0:
        if ((pCtx->nFlags & 0x80) != 0) {
            return;
        }
        pCtx->nRun = 0;
        pCtx->nFlags &= ~8;
        pCtx->nFlags &= ~1;
        pCtx->nFlags |= 2;
        break;

    case 1:
        pCtx->nRun += nDelta;
        pCtx->nTotal += nDelta;
        if ((pCtx->nFlags & 0x10) > 0) {
            pCtx->nSplit += nDelta;
        }
        for (k = 0; k < 2; k++) {
            if ((pCtx->nFlags & (0x20 << k)) > 0) {
                pCtx->aLaps[k] += nDelta;
            }
        }
        break;

    case 2:
        pCtx->nRun += nDelta;
        pCtx->nTotal += nDelta;
        for (k = 0; k < 2; k++) {
            if ((pCtx->nFlags & (0x20 << k)) > 0) {
                pCtx->aLaps[k] += nDelta;
            }
        }
        pCtx->nFlags |= 9;
        pCtx->nFlags &= ~2;
        pCtx->nFlags &= ~0x10;
        pCtx->nFlags &= ~0x80;
        break;

    case 3:
        pCtx->nSplit = 0;
        pCtx->nFlags |= 0x10;
        break;

    case 4:
        pCtx->nFlags &= ~0x10;
        break;

    case 5:
        pCtx->aLaps[nKind >> 6] = 0;
        pCtx->nFlags |= 0x20 << (nKind >> 6);
        break;

    case 6:
        pCtx->nFlags &= ~(0x20 << (nKind >> 6));
        break;
    }
}
