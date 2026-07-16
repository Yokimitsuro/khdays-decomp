/* func_ov023_02082bdc -- open a source and park the handle in a single global.
 * Opens through func_02023930 with the descriptor at data_ov023_0208a004 and the caller's
 * argument, storing the handle in data_ov023_0208a000 -- one live source at a time, not
 * per-instance state.
 *
 * PROVENANCE: byte-identical twin of func_ov024_02083238 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * ov023 is NOT MobiClip -- it is a separate subsystem (221 funcs, heavy func_02021980 /
 * OS_SPrintf use). Only the code SHAPE is shared with the rep; the MobiClip framing that
 * came with the twin source has been removed rather than guessed at.
 */
extern int func_02023930(void *desc, int arg);
extern int data_ov023_0208a004;
extern int data_ov023_0208a000;

void func_ov023_02082bdc(int arg) {
    data_ov023_0208a000 = func_02023930(&data_ov023_0208a004, arg);
}
