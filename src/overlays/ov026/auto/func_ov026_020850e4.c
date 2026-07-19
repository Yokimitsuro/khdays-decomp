/* Panel alpha: full unless the entry exists, is not in state 1, and is not in state 2
 * either. `plain` is initialised from `opaque` on purpose -- that copy is the ROM's
 * `mov r2, r1`. */
int func_ov026_020850e4(int *obj) {
    int opaque = 1;
    int plain;
    int *entry = (int *)obj[3];
    plain = opaque;
    if (entry != 0 && entry[5] != 1) {
        plain = 0;
    }
    if (plain == 0) {
        if (entry[6] != 2) {
            opaque = 0;
        }
    }
    return opaque != 0 ? 0xff : 0x63;
}
