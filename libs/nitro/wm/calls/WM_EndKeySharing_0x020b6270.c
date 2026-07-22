/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of the byte-identical interworking veneers
 * that differ only in the single pooled target.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This one
 * tail-calls func_ov065_020b637c. Trust the bytes, not the name. */
extern void *func_ov065_020b637c();

void *WM_EndKeySharing_0x020b6270() {
    return func_ov065_020b637c();
}
