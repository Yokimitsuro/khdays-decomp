/* UNFINISHED -- but 112/112 and structurally identical.  ONE register pairing
 * differs.  ★ EIGHT FUNCTIONS RIDE ON THIS: ov131/132/133 and ov161..ov165 all
 * have the SAME THREE RELOCS, so the matched file is literally copied eight
 * times with only the function name changed.  Cracking it pays 8x.
 *
 * AI state tick: acquire the target, and once the gap between the two bodies
 * closes to within the state's threshold (+0x2d8), drop the owner into sub-state
 * 4 (+0x1c7) and hand the node back to the dispatcher.
 *     gap = FX_Sqrt(distSq) - (target->radius + owner->radius)   (radius @ +0x80)
 *
 * WHAT DIFFERS: ROM r4=node r5=state r6=owner r7=target;
 *               ours r5=node r4=state r7=owner r6=target.
 * Both pairs swapped, every instruction otherwise identical.
 *
 * TWO STEPS THAT DID WORK, and they are the reusable part:
 *  - 128 -> 116: give `owner` its own local.  The ROM uses FIVE callee-saved
 *    registers and takes its 4-byte frame slot out of the `push` (pushing r3)
 *    rather than a `sub sp`.  Fewer live locals => mwcc emits `sub sp, #4` and
 *    the prologue diverges.  Register PRESSURE is a source-level knob.
 *  - 116 -> 112: re-read `owner` into the SAME variable before the threshold
 *    test, so one load feeds both the `[+0x2d8]` compare and the `[+0x1c7]`
 *    store.  Written as two separate `state[0]` reads, mwcc reloads and pays 4
 *    bytes.
 *
 * RULED OUT: all 24 declaration orders of the four locals, plus the same 24 with
 * `state` assigned in a statement instead of its declaration.  48 compiles.
 */
extern int *func_ov107_020cab14(int *owner, int *distSq);
extern int FX_Sqrt(int x);
extern void func_0203c634(int *node, int index, int value);

void func_ov131_020cd220(int *node) {
    int *state = (int *)node[1];
    int *owner;
    int *target;
    int gap;

    target = func_ov107_020cab14(*(int **)state, &gap);
    state[2] = (int)target;
    if (target == 0) {
        return;
    }
    owner = *(int **)state;
    gap = FX_Sqrt(gap) - (target[0x80 / 4] + owner[0x80 / 4]);
    owner = *(int **)state;
    if (gap > owner[0x2d8 / 4]) {
        return;
    }
    *((unsigned char *)owner + 0x1c7) = 4;
    func_0203c634(node, ((signed char *)node)[0x20], 0);
}
