/* BootTask_Construct: constructor of g_BootTaskClassDesc (run by RunClassConstructor).
 * Inits subsystems, then selects the first scene from the persisted state word @0x027ffc20:
 * 0 (fresh boot) -> Scene 1 (boot/logo); -2 -> Scene 1; else -> Scene 12. The scene request
 * is latched by func_02020a78 (StoreGlobalPairAt10). Returns the boot task's initial
 * per-frame state fn (func_02020978), stored by the caller into obj+0x14. */
extern void func_0201ea6c(void);
extern void func_020333c8(int a);
extern void func_02033500(int a);
extern void func_02020988(void);
extern void func_02020a78();
extern int func_02020978(void);

void *func_02020928(void) {
    int state;
    func_0201ea6c();
    func_020333c8(0);
    func_02033500(0);
    func_02020988();
    state = *(int *)0x027ffc20;
    if (state == 0) goto a;
    if (state == -2) goto c;
    goto d;
a:
    func_02020a78(1, 0);
    goto end;
c:
    func_02020a78(1, state);
    goto end;
d:
    func_02020a78(0xc, state);
end:
    return (void *)func_02020978;
}

/* PARK -- 4 bytes: the SECOND branch pair is inverted, and that is the only residue.
 *
 *   ROM   cmp r1,#0 / beq a ... cmp r1,r0 / beq c / b d
 *   mwcc  cmp r1,#0 / beq a ... cmp r1,r0 / bne d / b c
 *
 * The first test comes out right in every form tried; only the last if+goto pair gets
 * merged and inverted. Both encodings are the same length, so this is a choice mwcc makes,
 * not a size problem. Ruled out (all fail identically at 0x24):
 *   1. the goto chain below;               4. `if (state == -2) goto c; else goto d;`
 *   2. `if (...) { goto c; } else { goto d; }`   5. `if (state != 0) { ... } goto a;`
 *   3. a full if / else-if / else chain;
 * and a `switch (state)`, which is worse -- mwcc orders the compare chain NUMERICALLY, so
 * it tests -2 before 0 regardless of the order the cases are written in. (That is worth
 * knowing on its own: the "case source order picks the fall-through" crack applies to which
 * body is inline, NOT to the order of the comparisons.)
 *
 * NOT an arity problem, despite tools/audit_arity.py flagging it: func_02020a78 does take two
 * arguments (11 call sites in the tree agree), but r1 ALREADY holds `state` at both of the
 * one-argument call sites, so passing it explicitly and omitting it produce byte-identical
 * code. The calls are written with two arguments here because that matches the tree and is
 * almost certainly the original -- it just cannot be proven from this function's codegen.
 * A useful reminder that an arity flag is a lead, not a diagnosis.
 */
