/* func_ov206_020ccd68 -- retune the owner's four rig channels, then hand on to the next step.
 * Does nothing while the owner is in state 3 or 4 (+0x310). Otherwise channels 0, 1, 2 and 4 are
 * each set to mode 2 -- note channel 3 is deliberately skipped -- and the action from the
 * caller's +0x20 is dispatched through func_0203c634 with func_ov206_020ccdf4 as the
 * continuation.
 *
 * NONMATCHING: 140/140 bytes, byte-exact through 0x73 (all four retunes and the guard). The only
 * difference is the ORDER the final call's three arguments are set up: the ROM issues the two
 * memory ops first and the trivial register move last
 * (`ldrsb r1,[r5,#0x20] ; ldr r2,[pc] ; mov r0,r5`), where mwcc emits them in argument order
 * (`mov r0,r5 ; ldrsb r1 ; ldr r2`). Same instructions, same size -- pure scheduling.
 * Tried and rejected: hoisting the action into a local, and hoisting the callback into a local
 * too. Neither moves the schedule. Instruction-scheduling tie, see deferred-ties.md.
 *
 * ⚠ This BLOCKS a 4-member family (ov206/207/274/275) -- dedupprop will not propagate from a
 * nonmatching rep -- so it is worth a fresh attempt.
 *
 * Two things here ARE load-bearing and must be kept:
 * 1. `state` must be a local. Reading *(s8 *)(ctx[0] + 0x310) twice makes mwcc reload and re-split
 *    the base each time (+12 B).
 * 2. The guard is double-negated on purpose. Written as `state == 4 || state == 3`, mwcc
 *    range-reduces the contiguous pair to `sub r0,r0,#3 ; cmp r0,#1 ; popls`; the ROM keeps the
 *    `cmp #4 ; cmpne #3 ; popeq` cascade. This is the documented range-opt crack.
 */
extern void func_0203b9fc(int rig, int channel, int mode, int arg);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov206_020ccdf4(void);

void func_ov206_020ccd68(int self) {
    int *ctx;
    int state;

    ctx = *(int **)(self + 4);
    state = *(signed char *)(ctx[0] + 0x310);
    if (!(state != 4 && state != 3)) {
        return;
    }
    func_0203b9fc(ctx[1], 0, 2, 0);
    func_0203b9fc(ctx[1], 1, 2, 0);
    func_0203b9fc(ctx[1], 2, 2, 0);
    func_0203b9fc(ctx[1], 4, 2, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov206_020ccdf4);
}
