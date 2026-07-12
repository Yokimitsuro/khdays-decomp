/* NONMATCHING — single-instruction value-materialization tie (80/80 bytes,
 * byte-structurally identical). The only divergence is how the constant 0 stored
 * into the word field is produced: the original reuses the loop counter register
 * (which is 0 at that point) via `mov r2, ip`, while mwcc materializes it fresh
 * with `mov r2, #0`. Every other byte matches, including the mvn-based 0xffff
 * halfword fills (written as -1) and the array-subscript addressing that avoids the
 * walking-pointer strength reduction. Tried: `i * 0` (folded to 0). Unsteerable CSE
 * choice; the raw blob keeps the build byte-exact.
 *
 * Reset the 5-entry work list at *(param_1+0x88): when param_2 is 0 default it to
 * *(param_1+0x88)+0xe0, publish at +0x8c, then clear two shorts (+2, +0xca) to
 * 0xffff and one word (+0xc) to 0 per entry.
 */
void func_0203b9ac(int param_1, int param_2) {
    int i = 0;

    if (param_2 == 0) {
        param_2 = *(int *)(param_1 + 0x88) + 0xe0;
    }
    *(int *)(param_1 + 0x8c) = param_2;

    do {
        ((short *)(*(int *)(param_1 + 0x88)))[i + 1] = -1;
        ((short *)(*(int *)(param_1 + 0x88)))[i + 0x65] = -1;
        ((int *)(*(int *)(param_1 + 0x88)))[i + 3] = 0;
        i = i + 1;
    } while (i < 5);
}
