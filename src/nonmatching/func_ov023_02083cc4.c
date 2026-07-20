/* NONMATCHING -- 104/104 bytes, instruction for instruction identical, and the
 * ONLY residue is that the compiler-generated 7-byte copy loop swaps its two
 * pointer registers: the ROM keeps the source in r2 and the destination in r3,
 * mwcc does the reverse. Everything else -- the 'S'/'D' dispatch, the two
 * single-character appends, the trailing ".p2" -- is byte-exact.
 *
 * The semantics are settled, so this is purely a codegen question. The strings
 * were read out of the ROM: data_ov023_0208a0a4 = "ev/EV_" (7 bytes with the
 * terminator, which is what the copy length is), 0208a0ac = "S",
 * 0208a0b0 = "DP", 0208a0b4 = ".p2", and 0208a0c0 holds the assembled example
 * "ev/EV_DP.p2". func_0201fa3c is strcat, func_0201fa6c is strncat.
 *
 * Ruled out on 2026-07-20, all four at the same residue or worse:
 *   1. *(Str7 *)path = data_...       -- 104 B, the r2/r3 swap (this file)
 *   2. const Str7 *src = &data_...; *(Str7 *)path = *src;   -- same swap
 *   3. a union { char path[0x40]; Str7 head; }, so the assignment has no cast
 *      at all                                                -- same swap
 *   4. an explicit do { *d++ = *s++; } while (--n) with the source pointer
 *      declared first                                        -- 108 B, worse
 * memcpy(path, ..., 7) is 96 B: mwcc unrolls the builtin, so the ROM's counted
 * loop really is a struct copy and form 1 is the right shape.
 *
 * UNEXPLORED AXIS, and the one to attack next: what decides the operand order
 * of mwcc's inline struct copy. Declaration order does not reach it (the union
 * form has a single local). Worth grepping the matched tree for another
 * function containing a counted byte-copy loop with source in the LOWER
 * register and reading its source form -- per SKILL.md that search beats
 * further compile experiments. Not build-swept: the C is not yet proven
 * correct enough for a sweep to mean anything. */
typedef struct { char s[7]; } Str7;

extern const Str7 data_ov023_0208a0a4;
extern const char data_ov023_0208a0ac[];
extern const char data_ov023_0208a0b0[];
extern const char data_ov023_0208a0b4[];

extern char *func_0201fa3c(char *dst, const char *src);
extern char *func_0201fa6c(char *dst, const char *src, int n);

char *func_ov023_02083cc4(char *obj) {
    char path[0x40];

    *(Str7 *)path = data_ov023_0208a0a4;

    if (obj[2] == 0x53) {
        func_0201fa3c(path, data_ov023_0208a0ac);
    } else if (obj[2] == 0x44) {
        func_0201fa3c(path, data_ov023_0208a0b0);
    } else {
        func_0201fa6c(path, obj + 4, 1);
        func_0201fa6c(path, obj + 5, 1);
    }

    func_0201fa3c(path, data_ov023_0208a0b4);
    return path;
}
