/* NONMATCHING: 32/32 bytes, pure instruction scheduling. mwcc DOES emit the interworking tail
 * call correctly (ldr r12,[pool] ; bx r12 -- func_0202fa20 is THUMB), it just places the ldr two
 * instructions later than the ROM, which hoists it between the first and second store and
 * therefore needs r2 (not r1) for the constant 1. Same semantics, same size, same instruction
 * count.
 *
 * func_ov024_020835d8 -- MobiClip: open a render pass on the stream object.
 * Clears the mode and cursor fields, marks the pass open at +0x50 (func_ov024_02083ccc closes
 * it), then tail-calls the renderer's own begin. */
extern void func_0202fa20(int p);

void func_ov024_020835d8(int p) {
    *(int *)(p + 0x6c) = 0;
    *(int *)(p + 0x5c) = 0;
    *(int *)(p + 0x50) = 1;
    func_0202fa20(p);
}
