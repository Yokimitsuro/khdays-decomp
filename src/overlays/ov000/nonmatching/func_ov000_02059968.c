/* func_ov000_02059968 -- draw a 1px-inset framed box, ov000.
 * NONMATCHING: scheduling tie. The retail build coalesces the two stack args into
 * one `stm sp,{...}` and holds a5 in a callee-saved reg across both calls; our mwcc
 * emits two separate `str`s and reloads a5 (+3 instr). Logic is exact. For the port.
 *
 * Emits the inner rectangle (inset by 1 on each side) then the outer rectangle
 * through the primitive func_020301c8. */
extern void func_020301c8(int, int, int, int, int, int);
void func_ov000_02059968(int a0, int a1, int a2, int a3, int a4, int a5) {
    func_020301c8(a0, a2 + 1, a3 + 1, a4 - 1, a5, a1);
    func_020301c8(a0, a2, a3, a4, a5, a1);
}
