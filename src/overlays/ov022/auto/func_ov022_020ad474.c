/*
 * Merge the pending flag pair into the live one and clear it.
 *
 * Resets the 64-bit field at +0x464, sets it to 0x100 when bit 4 of the field at +0 is on,
 * then ORs in whatever the pending field at +0x46c holds and clears that.
 *
 * The park called the ROM's `and r1, r1, #0` a "dead flag term" and blamed a build-time
 * 0-valued macro.  Every one of the paired words here is a 64-BIT FIELD -- [0x119]/[0x11a]
 * is one, [0x11b]/[0x11c] is another -- and the zero operand is just the untouched half.
 * Written that way the whole function matches with no tricks.
 */
void func_ov022_020ad474(unsigned int *arg0) {
    *(long long *)&arg0[0x119] = 0;
    if ((*(long long *)arg0 & 0x10) != 0) {
        *(long long *)&arg0[0x119] = 0x100;
    }
    if (*(long long *)&arg0[0x11b] != 0) {
        *(long long *)&arg0[0x119] |= *(long long *)&arg0[0x11b];
        *(long long *)&arg0[0x11b] = 0;
    }
}
