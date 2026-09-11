/* Tail-call thunk: `ldr ip,[pc] ; bx ip` -- one of 172 byte-identical veneers differing only in
 * the single pooled target. Proven shape (families.md's veneer vein); 83 siblings already match.
 *
 * The name is misattributed: the SDK identifier matched a SHAPE, not a function. This is called
 * WM_EndKeySharing_0x0208d758 but tail-calls func_ov022_0208b848 (Ov022_VeneerTo_Ov022_LaunchSlotPart in Ghidra). It belongs to ov022,
 * not NitroSDK; retain the historical linkage symbol until a coordinated symbol rename. */
extern void *func_ov022_0208b848();

void *WM_EndKeySharing_0x0208d758() {
    return func_ov022_0208b848();
}
