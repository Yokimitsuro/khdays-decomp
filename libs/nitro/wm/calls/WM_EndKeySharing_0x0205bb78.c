/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of the byte-identical interworking veneers
 * that differ only in the single pooled target.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This one
 * tail-calls func_0202f9ec. Trust the bytes, not the name. */
extern void *func_0202f9ec();

void *WM_EndKeySharing_0x0205bb78() {
    return func_0202f9ec();
}
