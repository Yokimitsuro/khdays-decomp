/* Copy up to two (index, value) pairs from an object into a subitem table via func_02032634:
 * indices sit at obj+0x14, values at obj+0x34 (or +0x3c when param_3 is set). A pair is applied
 * only when the object is present and neither the index nor the value is -1.
 *
 * NON-MATCHING (equivalent). Semantics and the short-circuit conditional-compare chain are right.
 * Residue is a loop-strength-reduction heuristic: the ROM keeps the counter i live and scales it
 * inline (obj + i<<2, +0x14 as a load displacement), holding only obj and base; mwcc 139 strength-
 * reduces to running induction pointers (or, with array indexing, holds a precomputed obj+0x14
 * base) and pushes extra callee-saved registers. Tried induction/array-index/held-base/merged-
 * condition spellings; none suppress the reduction. */
extern void func_02032634(int target, int index, unsigned int value);

void func_ov008_02054d3c(int target, int obj, int param_3) {
    int base;
    int index = obj;
    int i;
    if (param_3 != 0) base = obj + 0x3c;
    else base = obj + 0x34;
    for (i = 0; i < 2; i++) {
        unsigned int value = *(unsigned int *)(base + i * 4);
        if (obj != 0 && (index = *(int *)(obj + i * 4 + 0x14)) != -1 && value != 0xffffffff) {
            func_02032634(target, index, value);
        }
    }
}
