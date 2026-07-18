/* NONMATCHING -- 32/32 B, one register pair. The ROM keeps `p` in r1 across the
 * `+= 0x2000` and puts the constant 10 in r0 (the parameter's register, dead after the
 * store); mwcc moves `p` into r0 and the constant into r1.
 *
 * IMPROVED 2026-07-18 (was a size mismatch): `arg0 = arg0 + 0x2000;` -- the original
 * OVERWRITES ITS OWN PARAMETER rather than using a second local. Same crack that matched
 * func_020169f8 and its 4 siblings; here it fixes the size but not the last pair. */
void func_ov022_0209be44(int arg0) {
    char *p = (char *)(arg0 + 0xc20);
    arg0 = arg0 + 0x2000;
    *(int *)(arg0 + 0xc20) = 0;
    p += 0x2000;
    p[4] = 10;
}
