/* func_ov186_020d1af8 -- head of a 5-member family (228 B). Re-arm the object's two sub-item
 * slots (0 and 3): in mode 3 rebuild each one from func_0203be68's fresh handle, otherwise set
 * both directly to `mode`. Then, if the object has a parent (+0x390) and its kind byte (+0x1c6)
 * is not 7, run the ov117 refresh, and finally re-register the object.
 *
 * Read off the disassembly (all wrong in Ghidra): func_0203be68 takes 3, func_0203be9c takes 3,
 * func_0203babc takes 4, func_0203b9fc takes 4, func_0203c7ac takes 2.
 *
 * The single instruction that kept this parked (`mov r6, r1` at the top, i.e. 4 bytes short) was
 * NOT "mwcc has no reason to save mode". It is the SIGN EXTENSION: written as `(short)mode` at
 * both call sites, mwcc common-subexpressions the cast into one callee-saved register and never
 * needs `mode` itself afterwards; the ROM keeps the full int in r6 and re-does `lsl #16 / asr #16`
 * at each site. Declaring the callee's third parameter `short` and passing plain `mode` puts the
 * conversion in the argument-passing sequence instead of in an expression, so it is emitted twice
 * and `mode` stays live across the first call. A cast you write twice can still be CSEd; a
 * PROTOTYPE conversion cannot. */
extern int  func_0203be68();
extern void func_0203be9c();
extern void func_0203babc();
extern void func_0203b9fc(int a, int b, short c, int d);
extern void func_ov186_020d1a50(int self);
extern void func_0203c7ac(int a, int b);

void func_ov186_020d1af8(int self, int mode, int arg) {
    if (mode == 3) {
        func_0203be9c(*(int *)(self + 0x384), 0, func_0203be68(*(int *)(self + 0x384), 0, 0));
        func_0203babc(*(int *)(self + 0x384), 0, 0, arg);
        func_0203be9c(*(int *)(self + 0x384), 3, func_0203be68(*(int *)(self + 0x384), 3, 0));
        func_0203babc(*(int *)(self + 0x384), 3, 0, arg);
    } else {
        func_0203b9fc(*(int *)(self + 0x384), 0, mode, arg);
        func_0203b9fc(*(int *)(self + 0x384), 3, mode, arg);
    }
    if (*(int *)(self + 0x390) != 0 && *(signed char *)(self + 0x1c6) != 7) {
        func_ov186_020d1a50(self);
    }
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
