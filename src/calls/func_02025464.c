/*
 * Obj_RelocateSections - fix up a freshly-loaded object's eight section tables, converting the
 * stored relative offsets into absolute pointers. param_1 is the object ('KAPH'-tagged); param_2
 * enables the per-entry dispatch for section 7. Idempotent: the relocated flag at +4 guards re-runs.
 *
 * For each of the 8 sections (offset slot at param_1[iVar4+2]): a -1 slot means "no section" and is
 * cleared to 0; otherwise the slot's relative offset is turned into an absolute pointer
 * (base + offset), and each of its `count` (first word) entries has its embedded pointer relocated
 * the same way. When param_2 is set and this is section 7 of a 'KAPH' object, each relocated entry
 * pointer is also handed to func_02025138. Finally the relocated flag is bumped.
 *
 * ARM. Matching notes (all needed together): the object is modelled as a struct with the section
 * slots as `sections[8]` at +8 so `state->sections[iVar4]` compiles to one callee-saved per-
 * iteration base `add rBase, state, iVar4, lsl#2; [rBase, #8]` (a plain `param_1[iVar4+2]` array
 * expression splits the base between a scratch reg and a recomputed index; a cached `int *sec`
 * strength-reduces to an advancing pointer); the inner walk is a `while (i < count)` (not
 * `if (count) do..while`) so the entry guard is the loop's unsigned `bls`, not an `== 0` `beq`; the
 * relocation is written as pointer arithmetic `(int)((char *)state + offset)` so the base is the
 * add's Rn (a plain `(int)state + offset` canonicalises the loaded offset as Rn instead); and the
 * empty-slot case is `if (slot != -1) {..} else {slot = 0;}` so the clear is the branch tail, not a
 * predicated moveq/streq.
 */

typedef struct {
    int tag;
    int relocated;
    int sections[8];
} RelocState;

extern void func_02025138(int entry);

void func_02025464(int *param_1, int param_2)
{
    RelocState *state = (RelocState *)param_1;
    int iVar4;

    if (state->relocated != 0) {
        return;
    }
    iVar4 = 0;
    do {
        if (state->sections[iVar4] != -1) {
            unsigned uVar5;
            state->sections[iVar4] = (int)((char *)state + state->sections[iVar4]);
            uVar5 = 0;
            while (uVar5 < *(unsigned *)state->sections[iVar4]) {
                ((int *)state->sections[iVar4])[uVar5 + 1] =
                    (int)((char *)state + ((int *)state->sections[iVar4])[uVar5 + 1]);
                if (param_2 != 0 && state->tag == 0x4850414b && iVar4 == 7) {
                    func_02025138(((int *)state->sections[iVar4])[uVar5 + 1]);
                }
                uVar5 = uVar5 + 1;
            }
        } else {
            state->sections[iVar4] = 0;
        }
        iVar4 = iVar4 + 1;
    } while (iVar4 < 8);
    state->relocated = state->relocated + 1;
}
