/* func_ov008_0206e320 -- Ov008_SetPairSelection (240 B, 11 relocs).
 * Sets the enable flags of a pair of menu widgets (ids in arg1[0], arg1[1]) according to the sign
 * of the mode argument, and returns a code for which state was applied:
 *   mode == 0 : both widgets disabled (flag 0 in a 2-iteration loop over arg1)      -> returns 0
 *   mode  < 0 : arg1[0] disabled, arg1[1] enabled                                   -> returns 2
 *   mode  > 0 : arg1[0] enabled,  arg1[1] disabled                                  -> returns 1
 * The leading widget context (arg0, a `this` pointer) is unused by this method. The zeroed
 * two-word scratch is preserved as declared in the original (it reserves the slot but is never
 * read here); volatile keeps mwcc from eliding the dead initialisation. */
typedef unsigned char u8;

extern void *func_ov008_02050c64(void);
extern void *func_ov008_02054788(void *wctx, int id);
extern void  func_ov008_02054ba4(void *wctx, void *w, int flag);

int func_ov008_0206e320(int arg0, int *arg1, int mode)
{
    volatile int scratch[2] = {0, 0};
    void *wctx;
    int i;

    wctx = func_ov008_02050c64();
    if (mode == 0) {
        for (i = 0; i < 2; i++) {
            func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, arg1[i]), 0);
        }
        return 0;
    }
    if (mode < 0) {
        func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, arg1[0]), 0);
        func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, arg1[1]), 1);
        return 2;
    }
    func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, arg1[0]), 1);
    func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, arg1[1]), 0);
    return 1;
}
