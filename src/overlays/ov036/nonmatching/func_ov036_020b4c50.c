/* EQUIVALENT BUT NOT BYTE-EXACT -- 4 bytes, 2026-07-18.
 *
 * Residue: the ROM emits `mov r5, #0` (i = 0) BEFORE `mov r8, r0` (the this_ copy);
 * mwcc emits the parameter copy first. Everything else -- register assignment included
 * (r5=i, r6=off, r7=a, r8=this_, r4=base), the `mov r6, r5` zero-copy, the loop, the
 * tail call -- is identical. It is the emission ORDER of two independent movs.
 *
 * Ruled out (all measured with tools/bytedist.py):
 *   for-init `i = 0, off = 0` with base declared first ......... 4  (best, this file)
 *   decls reordered so i/off precede base ..................... 14
 *   do/while instead of for, decls reordered .................. 14
 *   `int *base;` declared, assigned AFTER `int i = 0, off = 0;`  4
 *   base initialised inside the for-init, after i ............. 4
 *   `off = i = 0;` as a statement before the loop ............. 4
 *   struct-typed base (`Blk *base; base->rows`) ............... 4
 *   do/while with i/off initialised at declaration ........... 10
 *   `*(int *)(this_ + 0x2644)` at the use site (no hoist) .. size +4
 *
 * Checklist done: arity of func_ov022_0209145c confirmed = 2 from the matched call sites
 * in ov031_020b3610 / ov050_020b5e10 (which unroll the same 3 iterations by hand), so this
 * is NOT the dropped-trailing-argument trap. Mode is ARM (symbols.txt).
 *
 * The matched sibling func_ov036_020b4c94 has the SAME loop and matches with base declared
 * first -- but it has no second parameter, so it never has two copies to schedule. That is
 * the whole difference, and it is why the sibling's form does not transfer.
 *
 * Blocks a 4-member family (ov036/ov055/ov075/ov092). */

extern void func_ov022_0209145c();
extern void func_ov036_020b4c94(int);

void func_ov036_020b4c50(int this_, int a) {
    int *base = (int *)(this_ + 0x2000);
    int i, off;
    for (i = 0, off = 0; i < 3; i++, off += 0x30) {
        func_ov022_0209145c(base[0x191] + off, a);
    }
    func_ov036_020b4c94(this_);
}
