/*
 * Is this entity in a state that counts as "engaged"?
 *
 * States 2 through 10 always do; anything else defers to bit 16 of the 64-bit flag field at
 * +0x464 of the block hanging off +0x328.
 *
 * THREE LEVERS, and the first two are catalogue entries that were already written down when
 * this file was parked -- it just predates them:
 *  - the flag test is a 64-BIT AND.  The ROM's `and r1, r1, #0x10000` on the low word and
 *    `and r0, r0, #0` on the word above, with the `cmp` / `cmpeq` pair, is one
 *    `*(long long *)p & 0x10000`.  Reading it as a 32-bit test leaves the function 20 bytes
 *    short, which is what the original park recorded as a jump-table merging problem.
 *  - the result is a VARIABLE initialised to 0, not a return from each arm.  The ROM's
 *    `mov r2, #0` before the jump table and `mov r0, r2` at the end are that variable; with
 *    direct returns mwcc merges the identical bodies and the table collapses.
 *  - the block pointer must go through a LOCAL.  Written inline as
 *    `*(long long *)(*(int *)(arg0 + 0x328) + 0x464)` mwcc keeps the pointer in one register
 *    and computes a second base for the high half (`add r0, r1, #0x64` then `[r0, #0x404]`),
 *    4 bytes over; through a local it uses one base with both offsets, as the ROM does.
 *
 * The park's own diagnosis -- "mwcc merges the identical returns where the original lays a
 * separate jump-table block per case" -- described the symptom of the missing 64-bit read
 * rather than a cause.  The jump table was never the problem.
 */
int func_ov022_02095450(int arg0) {
    int ret = 0;

    switch (*(int *)(arg0 + 4)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        ret = 1;
        break;
    default:
        {
            char *p = *(char **)(arg0 + 0x328);
            if ((*(long long *)(p + 0x464) & 0x10000) != 0) {
                ret = 1;
            }
        }
        break;
    }
    return ret;
}
