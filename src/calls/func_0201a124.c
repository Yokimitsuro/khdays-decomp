/* * Was parked as an "*obj re-read (no-CSE) tie, 1 instruction short of byte-exact". Two things
 * were wrong (2026-07-17):
 *   - func_0201e144 takes THREE args and func_0201a124 itself takes THREE params -- the ROM never
 *     touches r2, so the incoming r2 IS forwarded as the 3rd argument.
 *   - the re-read is reachable with a PARTIAL volatile. The old write-up said: "Forcing the
 *     re-read with a `volatile` lvalue makes the field/tail-call reads BOTH reload (3 loads ->
 *     too long) and does not reproduce the original's 'reload once, then reuse' shape." That is
 *     true if you mark every read volatile. Mark ONLY the null test: the volatile read cannot be
 *     CSE'd with anything, while the two plain reads after the branch still CSE with each other.
 *     Two loads, "reload once then reuse", exactly as the ROM. See codegen-cracks.md.
 *
 * If (*obj != 0) and the byte field at (*obj)+0x2c is not 2, invokes func_0201e144 on
 * (*obj)+0x1c with arg1 shifted left by 8.
 */
extern void func_0201e144(void *p, int x, int y);

void func_0201a124(void *obj, int arg1, int arg2) {
    if (*(char *volatile *)obj != 0 && *(unsigned char *)(*(char **)obj + 0x2c) != 2) {
        func_0201e144(*(char **)obj + 0x1c, arg1 << 8, arg2);
    }
}
