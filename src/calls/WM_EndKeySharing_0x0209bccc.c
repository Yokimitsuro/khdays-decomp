/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of 172 byte-identical veneers differing only in
 * the single pooled target. Proven shape (families.md's veneer vein); 83 siblings already match.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This is called
 * WM_EndKeySharing_0x0209bccc but tail-calls func_ov025_02084afc. Trust the bytes, not the name. */
extern void *func_ov025_02084afc();

void *WM_EndKeySharing_0x0209bccc() {
    return func_ov025_02084afc();
}
