/* NON-MATCHING: one-instruction address-decomposition tie on the reaction-state store.
 *
 * Reaction enter (gated on node[2]->byte0 == 0): pick a random hold time in
 * [pActor->0x224 .. pActor->0x228] into node[0xb], promote reaction state from -1 to 2, then
 * re-arm the slot with no handler. node=*(ReactionAiNode**)(self+4); *node=pActor.
 *
 * Everything matches except the `if (state == -1) state = 2;` block, which is +1 instruction.
 * The read must use ldrsb, whose 8-bit offset cannot reach 0x1c7, so it splits to
 * `add rN,pActor,#0x100 ; ldrsb rN,[rN,#0xc7]`. The retail compiler keeps pActor in its own
 * register and writes the byte with the direct 12-bit STRB offset: `strb r,[pActor,#0x1c7]`.
 * Our mwcc instead reuses the split for the store, emitting an extra
 * `add rN,pActor,#0xc7 ; strb r,[rN,#0x100]`. (The same mwcc DOES use a direct `strb [.,#0x1c7]`
 * when the byte is written WITHOUT a paired ldrsb read of the same field -- see the sibling
 * ov256_020cf68c, which matches -- so this is specific to the read+conditional-write pairing.)
 * Caching pActor, reloading it inside the if, and reading into an int temp all leave the extra
 * add. Size differs by 4, so a build_sweep would be meaningless. A retail-scheduler / addressing
 * difference, not a source defect.
 */

extern int func_02023eb4(int bound);
extern int func_0203c634(int self, int idx, void *handler);

void func_ov253_020d0938(int self) {
    int *node = *(int **)(self + 4);
    int min, delta;
    if (*(unsigned char *)node[2] != 0) {
        return;
    }
    min = *(int *)(*node + 0x224);
    delta = *(int *)(*node + 0x228) - min;
    if (delta < 0) {
        delta = -delta;
    }
    node[0xb] = min + func_02023eb4(delta + 1);
    if (*(signed char *)(*node + 0x1c7) == -1) {
        *(unsigned char *)(*node + 0x1c7) = 2;
    }
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
