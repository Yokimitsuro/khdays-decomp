/* func_ov024_020859d4 -- MobiClip: decode one frame into the ring and advance the six plane
 * cursors. Bails out while the read position (+0x9c) is still past the write position (+0xa0).
 * A 0x8000 tag on the current chunk sets the "extended" flag (+0xa4) and adds 4 to the bitstream
 * skip; the N3 magic ('N','3' at +8/+9) adds that skip again. The decoded plane (block +0x3b4) is
 * published into the ring at +0x64 indexed by cursor 0, both scratch words are cleared, and each
 * of the six cursors at +0xac wraps at the ring length (+0xa8).
 *
 * Parked as the strength-reduction tie with three spellings measured and rejected. The one that
 * works is the fourth: index the WHOLE object and fold the field offset into the index --
 * `((int *)ctx)[i + 0x2b]`, where 0xac / 4 = 0x2b. That is what keeps the ROM's
 * `add r3, ctx, i lsl #2 ; ldr r1,[r3,#0xac]`; `((int *)(ctx + 0xac))[i]` hoists the base instead,
 * and the two byte-offset forms become running pointers.
 */

int func_ov024_020859d4(int ctx) {
    int extra;
    int i;

    if ((unsigned int)*(int *)(ctx + 0x9c) > (unsigned int)*(int *)(ctx + 0xa0)) {
        return 0;
    }

    if ((*(unsigned short *)**(int **)(ctx + 0x34) & 0x8000) != 0) {
        *(int *)(ctx + 0xa4) = 1;
        extra = 4;
    } else {
        extra = 0;
        *(int *)(ctx + 0xa4) = 0;
    }

    **(int **)(ctx + 0x34) += (*(int (**)(int))(ctx + 0x38))(*(int *)(ctx + 0x34));

    if (*(signed char *)(ctx + 8) == 0x4e && *(signed char *)(ctx + 9) == 0x33) {
        **(int **)(ctx + 0x34) += extra;
    }

    *(int *)(*(int *)(ctx + 0x64) + *(int *)(ctx + 0xac) * 4) =
        *(int *)(*(int *)(ctx + 0x34) + 0x3b4);
    *(int *)(ctx + 0xcc) = 0;
    *(int *)(ctx + 0xd0) = 0;

    for (i = 0; i < 6; i++) {
        ((int *)ctx)[i + 0x2b] = ((int *)ctx)[i + 0x2b] + 1;
        if (*(int *)(ctx + 0xa8) == ((int *)ctx)[i + 0x2b]) {
            ((int *)ctx)[i + 0x2b] = 0;
        }
    }

    *(int *)(ctx + 0xa0) = *(int *)(ctx + 0xa0) + 1;
    return 1;
}
