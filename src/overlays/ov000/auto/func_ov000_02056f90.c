/* Fold one record's contributions into the accumulator, scaled by the accumulator's
 * own factor at +0x20.
 *
 * This is the closer of the tally chain: OvNNN_TallySlots and OvNNN_TallyScaledSlots
 * both run it once they have walked their four slots.  It is a leaf, fully unrolled in
 * the ROM, and splits into two halves:
 *
 *  - seven SCALED contributions (`mla`), reading small signed fields out of the record
 *    at +0x2a..+0x30 and multiplying each by the factor before adding.  +0x2a is
 *    UNSIGNED (ldrb) while +0x2b..+0x2f are signed (ldrsb) and +0x30 is a full word --
 *    getting any of those widths or signs wrong changes the instruction, so they are
 *    load-bearing, not cosmetic.
 *  - thirteen UNSCALED word counters, record +0x54.. added onto accumulator +0xa4...
 *
 * The scaled group is emitted in the ROM's own field order, which is NOT ascending:
 * +0x2e is folded before +0x2d, and +0x30 before +0x2f.  That ordering is presumably
 * the source order and reproducing it is required.
 *
 * Note this makes the second parameter of the Tally* callers the ACCUMULATOR rather
 * than a plain parameter block -- it owns both the scale factor and these counters.
 */
void func_ov000_02056f90(char *acc, char *rec) {
    int scale = *(unsigned short *)(acc + 0x20);

    *(int *)(acc + 0x88) = *(int *)(acc + 0x88) + *(unsigned char *)(rec + 0x2a) * scale;
    *(int *)(acc + 0x8c) = *(int *)(acc + 0x8c) + *(signed char *)(rec + 0x2b) * scale;
    *(int *)(acc + 0x90) = *(int *)(acc + 0x90) + *(signed char *)(rec + 0x2c) * scale;
    *(int *)(acc + 0x94) = *(int *)(acc + 0x94) + *(signed char *)(rec + 0x2e) * scale;
    *(int *)(acc + 0x98) = *(int *)(acc + 0x98) + *(signed char *)(rec + 0x2d) * scale;
    *(int *)(acc + 0x9c) = *(int *)(acc + 0x9c) + *(int *)(rec + 0x30) * scale;
    *(int *)(acc + 0xa0) = *(int *)(acc + 0xa0) + *(signed char *)(rec + 0x2f) * scale;

    *(int *)(acc + 0xa4) = *(int *)(acc + 0xa4) + *(int *)(rec + 0x54);
    *(int *)(acc + 0xa8) = *(int *)(acc + 0xa8) + *(int *)(rec + 0x58);
    *(int *)(acc + 0xac) = *(int *)(acc + 0xac) + *(int *)(rec + 0x5c);
    *(int *)(acc + 0xb0) = *(int *)(acc + 0xb0) + *(int *)(rec + 0x60);
    *(int *)(acc + 0xb4) = *(int *)(acc + 0xb4) + *(int *)(rec + 0x64);
    *(int *)(acc + 0xb8) = *(int *)(acc + 0xb8) + *(int *)(rec + 0x68);
    *(int *)(acc + 0xbc) = *(int *)(acc + 0xbc) + *(int *)(rec + 0x6c);
    *(int *)(acc + 0xc0) = *(int *)(acc + 0xc0) + *(int *)(rec + 0x70);
    *(int *)(acc + 0xc4) = *(int *)(acc + 0xc4) + *(int *)(rec + 0x74);
    *(int *)(acc + 0xc8) = *(int *)(acc + 0xc8) + *(int *)(rec + 0x78);
    *(int *)(acc + 0xcc) = *(int *)(acc + 0xcc) + *(int *)(rec + 0x7c);
    *(int *)(acc + 0xd0) = *(int *)(acc + 0xd0) + *(int *)(rec + 0x80);
    *(int *)(acc + 0xd4) = *(int *)(acc + 0xd4) + *(int *)(rec + 0x84);
}
