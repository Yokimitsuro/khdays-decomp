extern char *data_ov002_0207f620;
extern void func_ov002_0205cebc(void);
extern void func_ov002_0205cc44(void);
extern int func_ov002_0205a4ec(void);
extern int func_ov002_0205a3f0(int *out, int slot);
extern void func_ov002_0205bff4(int kind, int flag);
extern void func_ov002_0205c87c(int a);

/* Steps the cursor back one entry and, if the entry resolves to kind 3, plays the
 * move sound and opens it. */
void func_ov002_0205e3e4(void) {
    char *self = *(char **)&data_ov002_0207f620;
    int out;
    int n;
    func_ov002_0205cebc();
    func_ov002_0205cc44();
    n = func_ov002_0205a4ec();
    if (n >= 1 && (unsigned char)self[4] >= n) {
        self[4] = (char)(n - 1);
    }
    if (func_ov002_0205a3f0(&out, (unsigned char)self[1]) == 3) {
        func_ov002_0205bff4((unsigned char)self[0], (unsigned char)self[4] % 6);
        func_ov002_0205c87c(out);
    }
}

/* PARK -- 2 bytes, and the note this replaces was WRONG about the semantics.
 *
 * Original park (2026-07-19): "2 bytes, instruction for instruction identical; the ROM loads the
 * pool word into r2 and mwcc into r0. The 'ROM skips the lowest free register' class. Tried:
 * declaration as initialiser / as statement, 3 declaration orders, the global as char** with an
 * index. All give r0. Do not re-grind."
 *
 * That register residue is real and still unsolved. But the C it was measured against was WRONG,
 * and `tools/audit_arity.py` is what surfaced it: func_ov002_0205bff4 was declared with ONE
 * parameter here while every other call site in the tree passes TWO.
 *
 * The missing argument is the REMAINDER of the divide on the line above. func_02020400 is
 * _s32_div_f: quotient in r0, remainder in r1. The old C called it and threw the result away,
 * which is never what that helper is for -- the ROM's `bl func_020235d0`-style sequence here is
 *     ldrb r0,[r4,#4] ; movs r1,#6 ; bl _s32_div_f ; ldrb r0,[r4] ; bl 0205bff4
 * and nothing writes r1 between the divide and the call. So the second argument is
 * `self[4] % 6`, and writing it that way reproduces the divide, the remainder and the argument
 * setup exactly. That whole block now matches; the residue is ONLY the two bytes at offset 4.
 *
 * Additionally ruled out this session: 1, 2 and 3 unused leading parameters (the theory being that
 * live parameters at entry would push the pool load off r0). mwcc drops them; all still give r0.
 *
 * So: the semantics below are now correct and the search space is two bytes wide. Anyone
 * re-attacking this should go at the pool-register choice alone and can trust everything else.
 */
