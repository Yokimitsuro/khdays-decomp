/* NONMATCHING — *obj re-read (no-CSE) tie, 1 instruction short of byte-exact.
 *
 * The original loads *obj for the null check, RE-LOADS *obj for the field access
 * (0x2c), and reuses that second load for the tail-call base (0x1c) — two loads of
 * *obj total. mwcc CSEs the null-check and field reads into a SINGLE load, coming
 * out 4 bytes (one ldr) short. Forcing the re-read with a `volatile` lvalue makes
 * the field/tail-call reads BOTH reload (3 loads → too long) and does not reproduce
 * the original's "reload once, then reuse" shape. This is the same re-read-vs-CSE
 * class as the wcscpy/strcat main helpers (see DECOMP_WORKFLOW deferred list). The
 * asm_stub keeps the build byte-exact.
 *
 * If (*obj != 0) and the byte field at (*obj)+0x2c is not 2, invokes
 * func_0201e144 on (*obj)+0x1c with arg1 shifted left by 8.
 */
extern void func_0201e144(void *p, int x);

void func_0201a124(void *obj, int arg1) {
    char *p = *(char **)obj;
    if (p != 0 && *(unsigned char *)(p + 0x2c) != 2) {
        func_0201e144(p + 0x1c, arg1 << 8);
    }
}
