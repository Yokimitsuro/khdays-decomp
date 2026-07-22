/* NONMATCHING -- 160/160 bytes, same instruction stream, THREE callee-saved registers rotated:
 * the original has i=r7 and the sign-extended argument in r5, this has them the other way round
 * and the two zero copies follow.
 *
 * IMPROVED 2026-07-22, from "~8 bytes long with four extra pushes". The park blamed a
 * loop-invariant address hoist that could not be suppressed. It can:
 *   - reaching the fixed sub-addresses through a STRUCT (obj->anim, obj->tracks, obj->block)
 *     stops mwcc hoisting them into callee-saved registers, which is what cost the four pushes;
 *   - the argument is an `int` narrowed with `(short)` at the use, not a `short` parameter -- the
 *     ABI assumes a short parameter is already extended, so a short parameter emits no lsl/asr
 *     at all, while the cast is CSE'd into the single extension the original has;
 *   - the non-null arm has to be written FIRST so it is the fall-through, matching the `beq` to
 *     the far block;
 *   - the cleared slot and the third argument are both written from the counter (`= i` while it
 *     is still 0), which is the original's two `mov rN,r7`.
 *
 * What is left is a CLASS, not a property of this function: the original copies the object out
 * of r0 BEFORE sign-extending the argument, using the freed r0 as the shift temporary, while
 * mwcc shifts the parameter in place and copies the object afterwards. func_ov048_020b4050 and
 * func_ov022_0208a8bc have exactly the same residue. Ruled out here: every declaration order of
 * {i, m, clear, zarg}, the cast hoisted out of the loop, the cast written inline at both call
 * sites, and the cast as a statement inside the loop body for mwcc to hoist. Crack one and all
 * three fall.
 *
 * For each of the five track slots: when the rig has no shared block, bind the track to the
 * built-in block at +0x108; otherwise release any handle already in the slot, clear it, and bind
 * the track to the shared block. Either way the track is then zeroed. */
extern void func_02014dc4(void *tracks, int handle);
extern void func_0202accc(void *anim, unsigned short slot, void *block, int arg);
extern void func_01fff774(void *anim, unsigned short slot, int arg);

struct Ov022Rig {
    char _pad0[0x28];
    char anim[0x34 - 0x28];         /* +0x28 */
    int slots[5];                   /* +0x34 */
    char tracks[0x108 - 0x48];      /* +0x48 */
    char block[0x130 - 0x108];      /* +0x108 */
    int pShared;                    /* +0x130 */
};

void func_ov022_020914a0(struct Ov022Rig *obj, int arg1) {
    unsigned int i = 0;
    int m = (short)arg1;
    int clear = i;
    int zarg = i;
    do {
        if (obj->pShared != 0) {
            int slot = obj->slots[i];
            if (slot != 0) {
                func_02014dc4(obj->tracks, slot);
                obj->slots[i] = clear;
            }
            func_0202accc(obj->anim, i, (void *)obj->pShared, m);
        } else {
            func_0202accc(obj->anim, i, obj->block, m);
        }
        func_01fff774(obj->anim, i, zarg);
        i = i + 1;
    } while ((int)i < 5);
}
