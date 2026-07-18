/* NONMATCHING -- 48/48 B, ONE register left (the second temp: ROM r3, mwcc r0).
 *
 * IMPROVED 2026-07-18 with the parameter-reuse lens (see codegen-cracks.md): the ROM's
 * THIRD temp lives in r1, which is `param_2`'s register, dead after its own store. Writing
 * `param_2 = *(int *)(&data + 4);` for that one fixes it.
 *
 * What is left: the ROM reuses r3 for the SECOND temp (the same register as the first),
 * while mwcc grabs r0 -- param_1's register, which dies first. Tried: an explicit `int t`
 * reused across all three (that swaps ip<->r3 for the data pointer, worse), an explicit
 * `int *p` reused (same), and the reused-temp + param_2 combination (no change).
 */
extern int data_ov008_02090f04;

void func_ov008_02051168(int param_1, int param_2, int param_3) {
    *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x9740) = param_1;
    *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x9744) = param_2;
    param_2 = *(int *)((char *)&data_ov008_02090f04 + 4);
    *(int *)(param_2 + 0x9748) = param_3;
}
