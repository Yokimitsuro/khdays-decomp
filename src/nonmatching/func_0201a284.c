/* NONMATCHING — 1-register coloring tie (byte-structurally identical otherwise).
 *
 * Every instruction matches the original in opcode, operand shape and order EXCEPT
 * the register chosen for the discarded null-check temp: the original loads *obj
 * into r3 (the register it pushed only for stack alignment), while mwcc loads it
 * into r1. All other bytes — including the deliberate re-read of *obj for the field
 * access — are identical. Tried: inline vs cached deref, `volatile` on the field
 * lvalue (needed to reproduce the re-read; see below), a named temp, and both-reads
 * volatile. mwcc -O4 consistently colors the dead null-check temp r1; unsteerable.
 *
 * A second subtlety this documents: the original does NOT CSE the two reads of *obj
 * (null check + field base) — it re-loads. mwcc CSEs them into one load unless the
 * second read goes through a volatile lvalue. So the byte-exact-shaped C would be
 *   if (*(char **)obj == 0) return 0;
 *   func_02008158(*(unsigned char *)(*(char *volatile *)obj + 0x3c));
 *   return 1;
 * which lands 1 register off (r1 vs r3). The clean, non-volatile form below is the
 * intended semantics; the asm_stub keeps the build byte-exact.
 *
 * Guards on *obj != 0, then invokes func_02008158 with the unsigned byte field at
 * (*obj)+0x3c; returns 1 (or 0 if *obj is null).
 */
extern void func_02008158(int x);

int func_0201a284(void *obj) {
    char *p = *(char **)obj;
    if (p == 0) {
        return 0;
    }
    func_02008158(*(unsigned char *)(p + 0x3c));
    return 1;
}
