/* Count how many of the 3 x 0x28 grid entries starting at +0x19c4 point at an object
 * whose +0x14 field equals param_2. The count is kept in a byte, so it wraps at 256.
 *
 * TWO things, and the first one retires a class that was written off as unreachable:
 *   - the entry is read as `((int *)param_1)[i + 0x671]`, with the 0x19c4 byte offset
 *     FOLDED INTO THE INDEX (0x19c4/4 = 0x671). Written the natural way,
 *     `*(int *)(param_1 + i * 4 + 0x19c4)`, mwcc strength-reduces the inner loop to a
 *     running pointer, which costs an extra callee-saved register and grows the push
 *     set -- exactly the "loop strength-reduction" residue that several ov008 parks
 *     were filed under. The ROM recomputes `param_1 + i*4` every iteration, and the
 *     index form is what stops mwcc inventing the second induction variable.
 *   - the declaration order (row, i, count) colours r4/ip/lr; every other order leaves
 *     the same instructions with the registers permuted. */
int func_ov025_02090ca8(int param_1, int param_2) {
    int row;
    int i;
    unsigned char count = 0;

    for (row = 0; row < 3; row++) {
        for (i = 0; i < 0x28; i++) {
            int p = ((int *)param_1)[i + 0x671];
            if (p != 0 && param_2 == *(int *)(p + 0x14)) {
                count = (unsigned char)(count + 1);
            }
        }
        param_1 += 0xa0;
    }
    return count;
}
