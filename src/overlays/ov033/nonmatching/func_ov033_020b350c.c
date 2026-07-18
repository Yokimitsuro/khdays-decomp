/* EQUIVALENT BUT NOT BYTE-EXACT -- 8 bytes (two instructions), 2026-07-18.
 *
 * Residue: argument-setup EMISSION ORDER for the 4-arg call. The ROM builds r3 (the
 * `*(int *)(self + 0x20) + 4` argument) and THEN loads the pool address into r0:
 *      ldr r2, [r5, #0x20] / ldrb r1, [r5, #9] / add r3, r2, #4 / ldr r0, [pc, #0x24] / mov r2, #0
 * mwcc always emits the pool load first. Everything else in the function -- all 22 other
 * instructions, every register -- is already identical.
 *
 * Ruled out (tools/bytedist.py):
 *   the plain form, `(int)&data_...` inline in the call ........ 8
 *   `extern int data_...[];` passed without `&` ................ 8
 *   the address hoisted into a local just before the call ...... 8
 *   the r3 argument hoisted into a local before the call ....... 8
 *   both non-constant arguments hoisted into locals ............ 8
 *
 * ★ CORPUS EVIDENCE (this is the interesting part): `tools/find_insn.py --seq 'add r3, \w+, #\w+'
 * 'ldr r0, \[pc'` returns **0 hits across the whole matched tree**. In ~12,900 byte-exact
 * functions mwcc has never once been made to emit a pool load after an argument add. That is not
 * a search that failed to match -- the first attempt DID fail that way (I asked for add/ldr/bl
 * consecutive, and the ROM has a `mov r2, #0` in between, so it could not have hit); this is the
 * corrected two-instruction search.
 *
 * So the ordering is very likely not reachable by reshuffling this call at all, and the ROM form
 * probably comes from a construct we do not use here (an inline helper returning the table, or a
 * macro). Worth revisiting if such a helper turns up in a sibling overlay -- not worth more
 * permutations of this call site.
 *
 * Blocks a 4-member family. Mode is ARM. Arity confirmed 4 (all four registers are live at the
 * bl, so this is not the dropped-trailing-argument trap). */

extern void func_ov022_020b15b0(int a, int b);
extern int func_ov022_020b14a4(int a, int b, int c, int d);
extern void func_ov022_020b1cec(int a, int b);
extern int data_ov033_020b4b3c;

void func_ov033_020b350c(int self) {
    char *blk = (char *)(self + 0x2f8 + 0x2000);
    *(unsigned char *)(blk + 0x334) = 0;
    func_ov022_020b15b0(*(unsigned char *)(self + 9), 1);
    *(int *)(blk + 0x340) = func_ov022_020b14a4((int)&data_ov033_020b4b3c,
                                                *(unsigned char *)(self + 9), 0,
                                                *(int *)(self + 0x20) + 4);
    func_ov022_020b1cec(self + 0xda0, 0xca);
    *(unsigned char *)(blk + 0x334) |= 9;
}
