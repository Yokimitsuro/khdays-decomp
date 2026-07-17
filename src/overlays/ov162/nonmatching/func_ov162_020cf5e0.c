/*
 * func_ov162_020cf5e0 -- UNFINISHED. 112/112 bytes, 28/28 instructions.
 * x8 family (worth 8) -- the best ratio in the SDK-vein census, which is exactly why it is
 * annoying to leave. The C is semantically complete and the instruction SHAPE is exact.
 *
 * WHAT IT DOES: re-acquire the target (020cab14, which returns the squared distance through an
 * out-param); none -> return. Take FX_Sqrt of that squared distance, subtract both radii
 * (target+0x80 and owner+0x80); if the remaining gap is within the owner's reach (owner+0x2d8),
 * fire state 4 and advance.
 *
 * THE GAP: a 3-register rename, nothing else. The ROM allocates state=r5, owner=r6, target=r7;
 * this C gets state=r6, target=r5, owner=r7. Same 28 instructions, same order, same everything
 * but the register numbers. This is the register-CHOICE residue class (deferred-ties.md).
 *
 * The interesting part, for that class: the ROM assigns owner -- whose live range starts LAST
 * (owner = *state, after the target==0 test) -- to r6, a LOWER register than target (r7), whose
 * range starts earlier (the first call's return). So "earliest live range wins the low register"
 * (the ov029 mechanism) does NOT hold here: owner starts last and still gets the lower number.
 * If there is a rule, it is length- or use-count-based, not start-order -- owner has the shortest
 * range and the fewest uses. Recorded as a second data point for whoever cracks the class.
 *
 * RULED OUT:
 *  - declaration order: all 6 permutations of (state's locals) byte-identical, diff pinned at 0x9.
 *  - inlining owner as `*state` at both uses: 128 (reloads from memory -- the local is needed).
 *  - inlining target as `state[2]`: 132 (same).
 *  - the out-param initialised from a param_4 (Ghidra shows `local_18 = param_4`): +4 bytes, so
 *    the param does not exist -- Ghidra invented it from the uninitialised stack slot.
 *  - operand order of the (target+0x80 + owner+0x80) sum: no effect.
 * Arity checked: 020cab14 takes (obj, int *out) -- the `add r1,sp,#0` is &distsq, and the callee
 * writes the squared distance there; FX_Sqrt(int). Both confirmed against the tree.
 *
 * NEXT STEP: none at the source level found. It belongs to the register-CHOICE class; the lever,
 * if any, is whatever makes mwcc prefer r5 for state over r6. Do not spend more single-function
 * effort -- but it is worth 8, so it is a prime candidate the day the class is understood.
 */
extern int func_ov107_020cab14(int obj, int *out);
extern int FX_Sqrt(int x);
extern void func_0203c634(int self, int idx, int cb);

void func_ov162_020cf5e0(int self) {
    int *state = *(int **)(self + 4);
    int owner;
    int target;
    int distsq;

    target = func_ov107_020cab14(*state, &distsq);
    state[2] = target;
    if (target == 0) {
        return;
    }
    owner = *state;
    distsq = FX_Sqrt(distsq) - (*(int *)(target + 0x80) + *(int *)(owner + 0x80));
    if (distsq > *(int *)(*state + 0x2d8)) {
        return;
    }
    *(char *)(*state + 0x1c7) = 4;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
