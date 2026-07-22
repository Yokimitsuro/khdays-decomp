/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of the byte-identical interworking veneers
 * that differ only in the single pooled target.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This one
 * tail-calls func_ov075_020b8c20. Trust the bytes, not the name. */
extern void *func_ov075_020b8c20();

void *WM_EndKeySharing_0x020b8808() {
    return func_ov075_020b8c20();
}
