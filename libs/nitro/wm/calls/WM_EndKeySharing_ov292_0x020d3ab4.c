/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of 172 byte-identical interworking
 * veneers differing only in the single pooled target.
 *
 * The WM_EndKeySharing name is a SHAPE match from the symbol index, not a real
 * identification: the 172 functions carrying it tail-call 76 different targets.
 * Read the reloc, never the name. This file previously named the wrong target --
 * the four remaining parked veneers had their targets shuffled between them, which
 * is why they were byte-identical after masking and still failed the reloc check. */
extern void *func_ov107_020c6980();

void *WM_EndKeySharing_ov292_0x020d3ab4() {
    return func_ov107_020c6980();
}
