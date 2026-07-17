/* * Two things were wrong, and the old header blamed the compiler for both:
 * "the ROM fuses the sub/scene null checks into conditional loads + a conditional early-return
 * (ldreq/cmpeq/popeq / ldrne/cmpne/beq) that a structural transcription over-expands (+24B)."
 *  - func_ov008_02058df0 takes TWO args, not four (the ROM sets only r0/r1).
 *  - the guards are just two plain `&&` chains. The old C juggled a `scene` variable through
 *    three separate ifs to "transcribe the structure"; writing the conditions the obvious way
 *    (`sub == 0 && rec->0x90 == 0` / `sub != 0 && rec->0x90 != 0`) produces the ROM's conditional
 *    loads and early-return by itself. mwcc if-converts short-circuit chains on its own -- it does
 *    not need help, and helping it is what cost the 24 bytes.
 * This function also takes NO parameters; it had four. (2026-07-17)
 */
/* func_ov008_020597c4 -- confirm the highlighted main-menu item, ov008.
 * Looks up the active menu record (func_ov008_02050cd4); its two targets are a sub-menu
 * (rec+0x8c) and a scene (rec+0x90). When only the scene target is set, tears the menu down
 * (02050e2c/020511c8/02050fe0/02051010) and either fires the transition (when story flag 0x35bd
 * is clear: prime 0x1e-frame fade, post the event, request state 4) or replays it
 * (func_ov008_02050970(1,-1)). When a sub-menu target is set, descends into it
 * (func_ov008_02058df0). Either way commits the input latch (func_02033b78(0,1)). */
extern int  func_ov008_02050cd4(void);
extern void func_ov008_02058df0(int rec, int a);
extern void func_ov008_02050e2c(int a);
extern void func_ov008_020511c8(int a);
extern void func_ov008_02050fe0(int a);
extern void func_ov008_02051010(int a);
extern int  func_02023588(int flag);
extern void func_ov008_02051168(int a, int b, int c);
extern void func_020235a8(int flag);
extern void func_ov008_02050a08(int a);
extern void func_ov008_02050970(int a, int b);
extern void func_02033b78(int a, int b);

void func_ov008_020597c4(void) {
    int rec = func_ov008_02050cd4();
    int sub = *(int *)(rec + 0x8c);

    if (sub == 0 && *(int *)(rec + 0x90) == 0) {
        return;
    }
    if (sub != 0 && *(int *)(rec + 0x90) != 0) {
        func_ov008_02058df0(rec, 1);
    } else {
        func_ov008_02050e2c(0);
        func_ov008_020511c8(0);
        func_ov008_02050fe0(1);
        func_ov008_02051010(*(int *)(rec + 0x90));
        if (func_02023588(0x35bd) == 0) {
            func_ov008_02051168(0x1e, 1, 1);
            func_020235a8(0x35bd);
            func_ov008_02050a08(4);
        } else {
            func_ov008_02050970(1, -1);
        }
    }
    func_02033b78(0, 1);
}
