/* NONMATCHING: down to a single `cmp` operand-order tie (previously 8 bytes short).
 * Two of the three stated blockers turned out to be reproducible:
 *   - the low-byte guard on the halfword at +0x60 is a BITFIELD read
 *     (`unsigned short lo:8`), not a cast -- `(unsigned char)x & 1` collapses to
 *     `ldrb; tst`, the bitfield keeps `ldrh; lsl#24; lsr#24; tst`;
 *   - the search loop keeps the original's `lsl r2,r3,#1; ldrsh r2,[r1,r2]`
 *     recompute once the element is indexed as an array (`((short *)arg1)[i]`);
 *     `*(short *)(arg1 + i*2)` strength-reduces to a walking pointer.
 * Also note the first guard is a plain word `& 1` (`tst r2,#1`), not a byte extract.
 * All that remains: the original emits `cmp r2, lr` (element, target) where mwcc
 * emits `cmp lr, r2`. Seven forms tried (operand order, target local, its type and
 * declaration position). Size-exact, single instruction differs. */
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
        if ((int)((short *)arg1)[i] == (int)*(unsigned short *)(arg0 + 2)) {
            found = 1;
            break;
        }
        i = i + 1;
    } while (i < 8);
    if (found) arg0 = 0;
    return arg0;
}
