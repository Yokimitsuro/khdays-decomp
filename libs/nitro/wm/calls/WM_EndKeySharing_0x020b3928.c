/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of the byte-identical interworking veneers
 * that differ only in the single pooled target.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This one
 * tail-calls func_ov036_020b3d40. Trust the bytes, not the name. */
extern void *func_ov036_020b3d40();

void *WM_EndKeySharing_0x020b3928() {
    return func_ov036_020b3d40();
}
