/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of the byte-identical interworking veneers
 * that differ only in the single pooled target.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This one
 * tail-calls func_ov107_020c6980. Trust the bytes, not the name. */
extern void *func_ov107_020c6980();

void *WM_EndKeySharing_ov169_0x020cc37c() {
    return func_ov107_020c6980();
}
