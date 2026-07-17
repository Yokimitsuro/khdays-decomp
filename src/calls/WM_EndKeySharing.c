/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of 172 byte-identical veneers differing only in
 * the single pooled target. Proven shape (families.md's veneer vein); 83 siblings already match.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This is called
 * WM_EndKeySharing but tail-calls func_02025aac. Trust the bytes, not the name. */
extern void *func_02025aac();

void *WM_EndKeySharing() {
    return func_02025aac();
}
