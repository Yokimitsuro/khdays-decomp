/* NONMATCHING — register-allocation strategy tie (caching vs recomputation).
 *
 * The logic and control flow match exactly, but the ROM RE-DERIVES the indexed
 * addresses (`param_1 + param_2*4`, `param_3 + param_2*4`, `param_1 + 0x20`) from
 * param_1/param_2 via the barrel shifter every time they are used, keeping the live
 * set inside {r4..r7} (6-register push). Every mwcc build we have instead CSEs those
 * address computations into extra callee-saved registers (r8/sb, 8-register push),
 * producing correct but shorter, differently-scheduled code (156 vs 168 bytes). This
 * is the same recompute-over-cache behaviour seen across the medium-complexity hot
 * worklist and is consistent with the retail ROM being built by a 3.0 build >=140
 * whose allocator we don't have.
 *
 * Proven unsteerable: swept all 27 checked-in mwccarm builds x {-O4,p/s / -O4 / -O3,p
 * / -O2 / -O1}; none byte-matches (the only builds that even reach 168 bytes are
 * mwcc 1.2 sp3/sp4, which differ in 125 of 168 bytes). Blob keeps the build byte-exact.
 *
 * For slot `param_2` of controller param_1, switch its bound resource to the one
 * selected by index `param_4` in the source table (param_3): if the current handle
 * differs, release it (func_02014dc4), record the new index, and — when param_4 >= 0 —
 * acquire the new handle (func_02014cd0) and reset its transform (scale +4 = 0x1000,
 * value = 0); a negative param_4 just clears the binding. */
extern void func_02014dc4(unsigned int *pool, int handle);
extern void func_02014cd0(char *pool, int handle);
void func_0202accc(int param_1, int param_2, int param_3, int param_4) {
    int cur;
    if (*(short *)(param_3 + param_2 * 2) == 0) return;
    cur = *(int *)(param_1 + param_2 * 4 + 0xc);
    if (cur != *(int *)(*(int *)(param_3 + param_2 * 4 + 0x10) + param_4 * 4)) {
        if (cur != 0) func_02014dc4((unsigned int *)(param_1 + 0x20), cur);
        *(short *)(param_1 + param_2 * 2 + 2) = (short)param_4;
        if (-1 < param_4) {
            int slot;
            cur = *(int *)(*(int *)(param_3 + param_2 * 4 + 0x10) + param_4 * 4);
            *(int *)(param_1 + param_2 * 4 + 0xc) = cur;
            func_02014cd0((char *)(param_1 + 0x20), cur);
            slot = param_1 + param_2 * 4;
            *(int *)(*(int *)(slot + 0xc) + 4) = 0x1000;
            **(int **)(slot + 0xc) = 0;
            return;
        }
        *(int *)(param_1 + param_2 * 4 + 0xc) = 0;
    }
}
