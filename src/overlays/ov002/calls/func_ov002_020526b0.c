/*
 * Ov002_StepSurfaceReveal - advance the surface's row-by-row reveal one frame.
 *
 * The first frame starts the reveal: the state goes to 1 and the row count to
 * one row. Every frame after that adds one more row. The rows are repainted,
 * and while the count has not yet reached half the span - rounded up, so an odd
 * span gets its centre row - the reveal reports itself unfinished. Once it has,
 * the tilemap block is filled in behind it, but only on the run that started
 * from state 1 and only when the owner has a map, and the surface is parked in
 * state 3.
 *
 * ARM. Returns non-zero on the frame the reveal completes.
 */

extern void func_ov002_020524ec(int *pCtx);   /* repaint the rows */
extern void func_ov002_02052650(int *pCtx);   /* fill the 15x15 tilemap block */

int func_ov002_020526b0(int *pCtx)
{
    if (pCtx[0] == 0) {
        pCtx[0] = 1;
        pCtx[1] = 1;
    } else {
        pCtx[1] = pCtx[1] + 1;
    }

    func_ov002_020524ec(pCtx);

    if (pCtx[1] >= (pCtx[9] + 1) / 2) {
        if (pCtx[0] == 1 && pCtx[0xf] != 0) {
            func_ov002_02052650(pCtx);
        }
        pCtx[0] = 3;
        return 1;
    }
    return 0;
}
