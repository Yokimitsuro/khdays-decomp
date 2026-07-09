/* NONMATCHING: register-coloring tie. Structurally identical to the original
 * (same opcodes: two base adds, the int store, an in-place pointer +0x2000,
 * then the byte store) but mwcc colors the final pointer-update add and the
 * immediate #0xa into r0/r1 swapped vs the original:
 *   orig: add r1,r1,#0x2000 ; mov r0,#0xa ; strb r0,[r1,#4]
 *   mwcc: add r0,r1,#0x2000 ; mov r1,#0xa ; strb r1,[r0,#4]
 * Cracks tried: pointer split, p+=0x2000, value-first local, direct
 * double-add expression (collapses to a single base). Kept as asm in the
 * delink so the ROM stays byte-exact. */
void func_ov022_0209be44(int arg0) {
    char *p = (char *)(arg0 + 0xc20);
    *(int *)(arg0 + 0x2c20) = 0;
    p += 0x2000;
    p[4] = 10;
}
