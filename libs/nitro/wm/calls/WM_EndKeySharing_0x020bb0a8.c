/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of the byte-identical interworking veneers
 * that differ only in the single pooled target.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This one
 * tail-calls func_ov091_020bb810. Trust the bytes, not the name. */
extern void *func_ov091_020bb810();

void *WM_EndKeySharing_0x020bb0a8() {
    return func_ov091_020bb810();
}
