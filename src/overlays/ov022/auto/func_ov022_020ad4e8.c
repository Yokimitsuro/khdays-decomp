/* Clamp a wrapped 16-bit angle delta toward the per-object limit at +0x4b0. A negative request
 * is rejected outright; a request already at the current angle (+0x488) is returned unchanged.
 * Otherwise the wrapped distance is folded to its absolute value, and if it exceeds the limit the
 * angle only advances by the limit -- unless the object is flagged at +0x24 bit 2, its 64-bit
 * flags at +0x464 have bit 29 clear, and the delta is over 0x7000, in which case the full request
 * is granted (a deliberate snap for large turns).
 *
 * The old note called this "predicate-vs-branch ... equivalent; left uncarved". It was four
 * ordinary source bugs, and the size was already right for two of them:
 *   - the wrapped delta and its absolute value are SIGNED. With `unsigned int` the two later
 *     tests come out `movhi`/`rsbhi` where the ROM has `movgt`/`rsbgt`;
 *   - the absolute value is a real if/else. Written as `ad = d; if (0x8000 < d) ad = ...;` mwcc
 *     predicates the whole block (`rsbhi/lslhi/lsrhi`) and needs two extra callee-saved
 *     registers; `if (0x8000 < d) { ad = ...; } else { ad = d; }` gives the ROM's
 *     `movle` + `ble` out-of-line block;
 *   - the 64-bit flag word must be addressed through a `char *`. `*(long long *)(arg0 + 0x464)`
 *     makes mwcc split the base for the high half (`add r2,r0,#0x64` + `[r2,#0x404]`, +4 bytes)
 *     even though both 0x464 and 0x468 are encodable; `*(long long *)((char *)arg0 + 0x464)`
 *     emits the two direct loads the ROM has;
 *   - declaration order then decides ip vs r3 for the base and the delta. */
unsigned int func_ov022_020ad4e8(int arg0, unsigned int arg1) {
    int d;
    int ad;
    unsigned int base = *(unsigned int *)(arg0 + 0x488);
    int lim;
    if ((int)arg1 < 0) return 0xffffffff;
    if (arg1 == base) return base;
    d = arg1 - base & 0xffff;
    if (0x8000 < d) {
        ad = 0x10000 - d & 0xffff;
    } else {
        ad = d;
    }
    lim = *(int *)(arg0 + 0x4b0);
    if (ad <= lim) return arg1;
    if ((*(unsigned int *)(arg0 + 0x24) & 4) != 0 &&
        (*(long long *)((char *)arg0 + 0x464) & 0x20000000) == 0 && 0x7000 < ad) {
        return arg1;
    }
    if (0x8000 < d) lim = -lim;
    return base + lim & 0xffff;
}
