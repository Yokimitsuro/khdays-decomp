/* func_ov022_0209ea44 -- gate a battle actor against a filter list.
 * Rejects outright when the actor's +0x1ac flag 2 is set and the passed context's word at +8 has
 * bit 0 clear; then requires bit 0 of the hw60 low byte. With no list (arg1 == 0) the actor passes
 * through unchanged; otherwise the actor's id (+2) is searched in the 8-entry short list and a hit
 * clears the result.
 *
 * Three source shapes are load-bearing here and each was a separate blocker:
 *   - the +0x60 low-byte guard is a BITFIELD read (`unsigned short lo:8`), not a cast:
 *     `(unsigned char)x & 1` collapses to `ldrb; tst`, the bitfield keeps `ldrh; lsl#24; lsr#24; tst`;
 *   - the list element must be indexed as an ARRAY (`((short *)arg1)[i]`) to keep the ROM's
 *     `lsl r2,r3,#1 ; ldrsh r2,[r1,r2]` recompute; `*(short *)(arg1 + i*2)` strength-reduces to a
 *     walking pointer;
 *   - the last byte was the `cmp` operand order (ROM `cmp element, target`, mwcc `cmp target,
 *     element`). Swapping the operands in the source does NOT flip it -- what flips it is binding
 *     the ELEMENT to a named local inside the loop. Same rule as the ov002 finding: the cmp's
 *     operand order follows which side is a named local, not which side is written first. Seven
 *     earlier forms all varied the TARGET (its local, type and declaration position); the lever
 *     was on the other operand. */
struct Hw60 { unsigned short lo : 8; unsigned short hi : 8; };

int func_ov022_0209ea44(int arg0, int arg1, int arg2) {
    int i;
    int found;
    if ((*(unsigned short *)(arg0 + 0x1ac) & 2) != 0 && arg2 != 0 &&
        (*(unsigned int *)(arg2 + 8) & 1) == 0) {
        return 0;
    }
    if ((((struct Hw60 *)(arg0 + 0x60))->lo & 1) == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return arg0;
    }
    found = 0;
    i = 0;
    do {
        int v = ((short *)arg1)[i];
        if (v == (int)*(unsigned short *)(arg0 + 2)) {
            found = 1;
            break;
        }
        i = i + 1;
    } while (i < 8);
    if (found) arg0 = 0;
    return arg0;
}
