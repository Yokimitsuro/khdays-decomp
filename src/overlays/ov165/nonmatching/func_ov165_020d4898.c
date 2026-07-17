/* NONMATCHING -- 72/72 B, 16/16 instructions, ONE register: the ROM loads the
 * out-param into r1 (`ldr r1,[sp,#8]` then `str r4,[r1]`), mwcc into r0. Nothing else
 * differs at all.
 *
 * FIXED 2026-07-17: every file in this vein declared `void *entry = 0;`. The ROM does
 * NOT initialise the out-param -- the `mov r1,#0` and `str r1,[sp,#8]` that costs are
 * simply not there. Dropping the initialiser takes the whole vein from 80 B (8 over) to
 * 72/72. The house form is in the matched c5c0 templates under ov114/ov115 calls.
 *
 * THIS IS THE PROJECT'S BEST MINIMAL REPRODUCER for the "identical stream, one
 * caller-saved register" class (ov000_020552b4, ov181_020ce664, ov206_020cd464 and
 * ov185_020d11f4 are the same shape at 184-716 B). Sixteen instructions, so whatever
 * cracks it will be unambiguous. Worth 24 functions.
 *
 * RULED OUT -- every one lands on the identical r0. Do not repeat; use
 * tools/build_sweep.py:
 *   - ALL 27 mwcc builds. Twenty of them (2.0/base through 3.0_patch4, AND the entire
 *     dsi line, which is years apart) produce byte-identical output at "2 off". Twenty
 *     compiler generations agreeing with each other and disagreeing with the ROM is not
 *     a build problem.
 *   - 44 flag combinations: -O0 -O1 -O2 -O3 -O4, each plain and with ,p and ,s, plus
 *     -Otime and -Ospace, crossed with -inline off, on, "on,noauto" and all.
 *   - -lang c99 and -lang c. (c89, cplus and c++ do not compile.)
 *   - 13 source spellings: void vs int prototype for func_0203c5c0; `entry[0]` vs
 *     `*entry`; entry typed as pointer-to-void, to int, to int-pointer, to char-pointer;
 *     the parameter as int vs pointer; an unused `int rc =` to try to keep r0 busy;
 *     a volatile entry; an intermediate `void **pe`; explicit casts on args 4, 5 and 6;
 *     and an `int *e = entry;` temp.
 *
 * ALL 24 instances in the ROM use r1 -- there is no variant, so it is not noise. The
 * compiler and the ROM are each 100% self-consistent and disagree with each other. The
 * source must differ in some way not yet imagined; every mechanical lever is spent. */
extern void func_0203c5c0();
extern void func_ov165_020d4928(void);
extern void func_ov165_020d49a8(void);

void func_ov165_020d4898(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0xc, func_ov165_020d4928, func_ov165_020d49a8, &entry);
    *entry = this_;
}
