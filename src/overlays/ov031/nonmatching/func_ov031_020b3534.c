/* func_ov031_020b3534 (x4 family: ov050/070/088) - NON-MATCHING, 220/220 bytes, one insn off.
 * State-transition dispatch (param_2 0x2e / {0x2f,0x30}).
 *
 * SOLVED 2026-07-17 -- point (1) of the old note (the +1-instr size gap): it is a SWITCH, not an
 *   if-chain. The `cmp;cmpne;beq` dead-compare head is a switch fingerprint (codegen-cracks.md
 *   "dead compare chain / switch fingerprint"). case 0x2e has its own body; 0x2f/0x30 share one.
 *   Writing it as the switch below brings the size to exact 220 and collapses the diff to ONE
 *   scheduler decision. Also confirmed: func_ov022_020a4490 takes 3 args (tree consensus, 52 sites);
 *   the ROM's r3=this+0x2000 at the call is the store base left over, not a 4th arg (4-arg spelling
 *   is byte-identical here, so arity is not the lever).
 *
 * THE REMAINING GAP (diff @0x4, one scheduler slot-fill I could not source-force):
 *   The ROM fills the cmp->beq slot with `add r1,r5,#0x2c` -- the LOW half of case 0x2e's
 *   `this+0x2c2c` arg, split off and hoisted before the dispatch, completed with `add r1,r1,#0x2c00`
 *   in the body. That single hoist cascades: it occupies r1, so `this` must be homed first
 *   (`mov r5,r0` before `mov r4,r1`), and the guard load lands in r2 giving `cmp r4,r2` instead of
 *   `cmp r1,r4`. All three "diffs" are one root. mwcc will not schedule that partial add up.
 *   RULED OUT (all leave @0x4, or worse): switch as written; full-hoist `int *reinit=this+0x2c2c`
 *   before the switch (224, over); `(char*)this + 0x2c2c` pointer typing; the struct-field two-writer
 *   trick from codegen-cracks.md row 446 does not apply -- that KILLS a wrong hoist; here the ROM
 *   hoists and mwcc won't, the opposite direction. Attack only the slot-fill.
 * asm stub stays byte-exact via dsd. */
extern void func_ov031_020b39d4(int a, int b);
extern void func_ov022_020a4490(int a, int b, int c);
extern void func_ov031_020b3a20(int a, int b);
extern void func_ov022_020a384c(int a, int b);

void func_ov031_020b3534(int this, int param_2, int param_3, int param_4) {
    switch (param_2) {
    case 0x2e:
        if (*(int *)(this + 0x6bc) != param_2)
            func_ov031_020b39d4(this, this + 0x2c2c);
        break;
    case 0x2f:
    case 0x30:
        if (*(int *)(this + 0x6bc) != param_2) {
            if (param_2 == 0x2f) {
                *(int *)(this + 0x2c2c) = 0;
                *(int *)(this + 0x2c34) = 0x9000;
                func_ov022_020a4490(this, 0xcb, 2);
                func_ov031_020b3a20(this + 0x2d50, 0);
            } else {
                *(int *)(this + 0x2c2c) = 1;
                *(int *)(this + 0x2c34) = 0x12000;
                func_ov022_020a4490(this, 0xcb, 3);
                func_ov031_020b3a20(this + 0x2c38, 0x9000);
                func_ov031_020b3a20(this + 0x2d50, 0x9000);
            }
        }
        break;
    }
    func_ov022_020a384c(this, param_2);
}
