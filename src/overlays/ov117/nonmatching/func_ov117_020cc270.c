/* NONMATCHING -- 224 vs 228 B, ONE instruction: the ROM saves the `mode` parameter into a
 * callee-saved register at the top (`mov r6, r1`) even though mwcc can keep it in r1 -- the
 * else branch is reached with no intervening call, so mwcc sees no need. Everything else,
 * including all five call arities, matches.
 *
 * Head of a 5-member family (228 B).
 *
 * SOLVED here -- do NOT rediscover (all read off the disassembly, all wrong in Ghidra):
 *  - func_0203be68 takes 3, func_0203be9c takes 3, func_0203babc takes 4, func_0203b9fc
 *    takes 4, and func_0203c7ac takes 2 (Ghidra shows 4 for the last).
 *  - the else branch passes `(short)mode` sign-extended, recomputed at BOTH call sites.
 *
 * Ruled out, measured with bytedist.py: a `short m` local inside the else (-4, same), a short
 * parameter in the signature (-16), caching *(int *)(self+0x384) in a local (right size but
 * 64 differing bytes), and computing `(short)mode` before the if (-20). */
extern int  func_0203be68();
extern void func_0203be9c();
extern void func_0203babc();
extern void func_0203b9fc();
extern void func_ov117_020cc1c8(int self);
extern void func_0203c7ac(int a, int b);

void func_ov117_020cc270(int self, int mode, int arg) {
    if (mode == 3) {
        func_0203be9c(*(int *)(self + 0x384), 0, func_0203be68(*(int *)(self + 0x384), 0, 0));
        func_0203babc(*(int *)(self + 0x384), 0, 0, arg);
        func_0203be9c(*(int *)(self + 0x384), 3, func_0203be68(*(int *)(self + 0x384), 3, 0));
        func_0203babc(*(int *)(self + 0x384), 3, 0, arg);
    } else {
        func_0203b9fc(*(int *)(self + 0x384), 0, (short)mode, arg);
        func_0203b9fc(*(int *)(self + 0x384), 3, (short)mode, arg);
    }
    if (*(int *)(self + 0x390) != 0 && *(signed char *)(self + 0x1c6) != 7) {
        func_ov117_020cc1c8(self);
    }
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
